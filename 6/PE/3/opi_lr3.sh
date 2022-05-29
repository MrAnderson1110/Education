#!/usr/bin/env bash
set -Eeuo pipefail
trap cleanup SIGINT SIGTERM ERR EXIT
script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd -P)

####
## Служебные функции
# Проверить наличие прав root (в случаях, когда операция 
# должна выполняться под административными правами)
checkroot()
{
	if [ "$EUID" -ne 0 ]; then 
		echo "Error: This action requires root privileges."
	fi
}

# Получить ответ в стиле "Да"/"Нет"
getyesno()
{
	confirm=-1
	
	while (($confirm == -1)); do
		read -r -p "$1 (Y/N): " answer
		case $answer in
			[Yy]* ) confirm=1; break;;
			[Nn]* ) confirm=0; break;;
			* ) echo "Valid answers are Y or N.";;
		esac
	done
}

# Получить ответ (непустой)
getanswer()
{
	answer=''

	while [[ -z $answer ]]; do
		read -p "Enter the $1: " answer
		if [[ -z $answer ]]; then
			echo "No $1 entered"
		fi
	done
}

# 1. Установка PostgreSQL
install_psql()
{
	echo "PostgreSQL installation"
	echo "======================="

	#pg_status=$(dpkg-query -W --showformat='${Status}\n' postgresql | grep "install ok installed")
	local pg_status=`dpkg -s postgresql 2>/dev/null | grep Status`
	
	if [[ -z $pg_status ]]; then 
		echo "PostgreSQL not installed. Trying to install..."
		local isroot="$(checkroot)"
		if [[ -n $isroot ]]; then
			echo $isroot
			exit
		fi
		apt update && apt install postgresql
	else
		echo "PostgreSQL package already installed"
	fi
}

# 2. Конфигурирование pg_hba.conf
configure_access()
{
	hba_path="/etc/postgresql/9.6/main/pg_hba.conf"

	isroot="$(checkroot)"
	if [[ -n $isroot ]]; then
		echo $isroot
		exit
	fi
	
	echo "Adding an entry into pg_hba.conf"
	echo "================================"
	# /etc/postgresql/9.6/main/pg_hba.conf
	local noaddress=0
	local conn_selected=0
	local method_selected=0
	local conn=''
	local database=''
	local user=''
	local address=''
	local method=''
	
	while (($conn_selected == 0)); do
		read -p "1. Select connection type (local, host, hostssl, hostnossl): " conn
		case $conn in
			local) conn_selected=1; noaddress=1 ;;
			host) conn_selected=1 ;;
			hostssl) conn_selected=1 ;;
			hostnossl) conn_selected=1 ;;
			*) echo "Unknown connection type. Please try again" ;;
		esac
	done
	
	
	while [[ -z $database ]]; do
		read -p "2. Specify database(s) (or all, sameuser, samerole, replication): " database;
		if [[ -z $database ]]; then
			echo "No database entered"
		fi
	done
	
	
	while [[ -z $user ]]; do
		read -p "3. Select user (or all): " user;
		if [[ -z $user ]]; then
			echo "No user entered"
		fi
	done
	
	if (($noaddress != 0)); then
		while [[ -z $user ]]; do
			read -p "4. Select address: " address;
			if [[ -z $address ]]; then
				echo "No address entered"
			fi
		done
	fi
	
	while (($method_selected == 0)); do
		read -p "5. Select access method (trust, reject, md5, password, gss, sspi, ident, peer, pam, ldap, radius, cert): " method
		case $method in
			trust) method_selected=1 ;;
			reject) method_selected=1 ;;
			md5) method_selected=1 ;;
			password) method_selected=1 ;;
			gss) method_selected=1 ;;
			sspi) method_selected=1 ;;
			ident) method_selected=1 ;;
			peer) method_selected=1 ;;
			pam) method_selected=1 ;;
			ldap) method_selected=1 ;;
			radius) method_selected=1 ;;
			cert) method_selected=1 ;;
			*) echo "Unknown access method. Please try again" ;;
		esac
	done
	
	hba_line="$conn \t$database \t$user \t\t$address \t\t$method"
	
	echo "Resulting pg_hba.conf line:"
	echo $hba_line
	
	confirm=0
	
	while (($confirm == 0)); do
		read -r -p "Add the result into pg_hba.conf? (Y/N): " answer
		case $answer in
			[Yy]* ) confirm=1; break;;
			[Nn]* ) return;;
			* ) echo "Valid answers are Y or N.";;
		esac
	done
	
	if(($confirm==1)); then
		echo $hba_line >> $hba_path
		echo "Added entry to pg_hba.conf"
	fi;
}

# 3. Cоздание базы данных и формирование ее бэкапа
createdb()
{
	local isroot="$(checkroot)"
	if [[ -n $isroot ]]; then
		echo $isroot
		exit
	fi

	echo "Database creation"
	echo "================="
	dbname=''
	
	while [[ -z $dbname ]]; do
		read -p "Enter the database name: " dbname
		if [[ -z $dbname ]]; then
			echo "No database entered"
		fi
	done
	
	sudo -u postgres psql -c "\"CREATE DATABASE $dbname;\""
}

backupdb()
{
	echo "Database backup"
	echo "==============="

	local dbname=''
	while [[ -z $dbname ]]; do
		read -p "Enter the database name: " dbname
		if [[ -z $dbname ]]; then
			echo "No database entered"
		fi
	done
	
	local backup_path=''
	while [[ -z $backup_path ]]; do
		read -p "Enter the filename to backup to: " backup_path
		if [[ -z $backup_path ]]; then
			echo "No filename entered"
		fi
	done
	
	sudo -u postgres pg_dump $dbname > $backup_path
}
# 4. Cоздание схем и таблиц по имени БД
createschema()
{
	local isroot="$(checkroot)"
	if [[ -n $isroot ]]; then
		echo $isroot
		exit
	fi

	echo "Schema creation"
	echo "================="
	dbname=''
	
	while [[ -z $dbname ]]; do
		read -p "Enter the database name: " dbname
		if [[ -z $dbname ]]; then
			echo "No database entered"
		fi
	done
	
	schema=''
	
	while [[ -z $schema ]]; do
		read -p "Enter the new schema name: " schema
		if [[ -z $schema ]]; then
			echo "No schema entered"
		fi
	done
	
	sudo -u postgres psql -d $dbname -c "\"CREATE SCHEMA $schema;\""
}
# 4.2. Cоздание таблиц должно предполагать задание столбцов и их типов данных
createtable()
{
	local isroot="$(checkroot)"
	if [[ -n $isroot ]]; then
		echo $isroot
		exit
	fi

	echo "Table creation"
	echo "=============="
	getanswer 'database name'; local dbname=$answer
	getanswer 'table name'; local table=$answer
	
	echo ""
	echo "Adding columns"
	echo "--------------"
	local query="CREATE TABLE $table (\n"

	local more_columns=1
	while (($more_columns == 1)); do
		getanswer "column name"
		local column_name=$answer
		getanswer "data type"
		local column_type=$answer
		getanswer "attribute(s)"
		local attributes=$answer
		
		local columnline="    $column_name $column_type $attributes"
	
		read -r -p "Add another column? (Y/N): " answer
		case $answer in
			[Yy]* ) more_columns=1; columnline=$columnline"," ;;
			[Nn]* ) more_columns=0 ;;
			* ) echo "Valid answers are Y or N.";;
		esac
		
		query=$query$columnline'\n'
	done
	
	query=$query");"
	
	echo -e "Resulting query:\n$query"
	
	getyesno "Execute query?"
	
	if (($confirm == 1)); then
		echo -e $query | sudo -u postgres psql -d $dbname
		#sudo -u postgres psql -d $dbname -c "\"$query\""
	fi
}
# 5. Cоздание роли и назначение прав
createrole()
{
	local isroot="$(checkroot)"
	if [[ -n $isroot ]]; then
		echo $isroot
		exit
	fi

	echo "Role creation"
	echo "============="

	getanswer "Role name"
	local rolename=$answer
	
	local pass=''
	read -s -p "Set the password (or none): " pass
	echo ""
	
	local pass_entered=0
	if [[ -n pass ]]; then 
		pass_entered=1
	fi

	getyesno "Is the role considered superuser?"
	local superuser=$confirm

	getyesno "Can this role create other roles?"
	local createrole=$confirm

	getyesno "Can this role create databases?"
	local createdb=$confirm

	getyesno "Does this role inherit privileges?"
	local inherit=$confirm
	
	getyesno "Can this role login?"
	local login=$confirm	

	query="CREATE ROLE $rolename"
	
	let argcount=$pass_entered+$superuser+$createdb+$createrole+$inherit+$login
	echo $argcount
	
	if (( $argcount > 0 )); then
		query=$query" WITH"
	fi
	
	if [[ -n $pass ]]; then
		query=$query" PASSWORD '$pass'"
	fi
		
	if (( $superuser == 1)); then
		query=$query" SUPERUSER"
	fi
		
	if (( $createrole == 1)); then
		query=$query" CREATEROLE"
	fi

	if (( $createdb == 1)); then
		query=$query" CREATEDB"
	fi
	
	if (( $inherit == 1)); then
		query=$query" INHERIT"
	fi
	
	if (( $login == 1)); then
		query=$query" LOGIN"
	fi
	
	echo -e "Resulting query:\n$query"
	getyesno "Execute query?"
	
	if (($confirm == 1)); then
		echo -e $query | sudo -u postgres psql -d $dbname
	fi
}
####

usage() {
  cat <<EOF
  Usage: $(basename "${BASH_SOURCE[0]}") [-h] [-v] [-f] -p param_value arg1 [arg2...]
  Script description here.
  Available options:
  -h, --help - Print this help and exit
  -i, --install - Install PostgreSQL
  -a, --access - Configure access options (pg_hba.conf)
  -b, --backup - Backup database
  -cr, --createdb - Create Database
  -s, --createschema - Create Schema
  -t, --createtable) - Create Table (and define rows)
  -r, --createrole - Create Role (and define options)
EOF
 exit
}

cleanup() {
  trap - SIGINT SIGTERM ERR EXIT
  # script cleanup here
}

setup_colors() {
  if [[ -t 2 ]] && [[ -z "${NO_COLOR-}" ]] && [[ "${TERM-}" != "dumb" ]]; then
     NOFORMAT='\033[0m' RED='\033[0;31m' GREEN='\033[0;32m' ORANGE='\033[0;33m' BLUE='\033[0;34m' PURPLE='\033[0;35m' CYAN='\033[0;36m' YELLOW='\033[1;33m'
  else
     NOFORMAT='' RED='' GREEN='' ORANGE='' BLUE='' PURPLE='' CYAN='' YELLOW=''
  fi
}

msg() {
  echo >&2 -e "${1-}"
}

die() {
  local msg=$1
  local code=${2-1} # default exit status 1
  msg "$msg"
  exit "$code"
}

setmsg() {
  msg "${CYAN}Message!${NOFORMAT}"
}

parse_params() {
  # default values of variables set from params
  flag=0
  param=''
  while :; do
    case "${1-}" in
    -h | --help) usage ;;
    --no-color) NO_COLOR=1 ;;
	-i | --install) install_psql ;;
	-a | --access) configure_access ;;
	-b | --backup) backupdb ;;
	-cr | --createdb) createdb ;;
	-s | --createschema) createschema ;;
	-t | --createtable) createtable ;;
	-r | --createrole) createrole ;;
    -c | --color) setmsg
    param="${2-}"
    shift
    ;;
    -?*) die "Unknown option: $1" ;;
    *) break ;;
    esac
    shift
  done
  args=("$@")
  return 0
}

argc=${$#}
setup_colors
parse_params "$@"

# script logic here
if (( $argc <= 1 )); then
	echo "argc="$argc
	usage
fi
