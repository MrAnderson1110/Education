# #!/bin/bash

# RED='\033[1;31m'
# BLUE='\033[1;34m'
# GREEN='\33[0;32m'
# CLEARC='\033[0m'

# usage() {
#     cat << EOF
#     Usage: $(basename "${BASH_SOURCE[0]}") command [args]

#     Available commands:
#     -h --help - Print this help
#     -i --install - Install all requeried packages
#     -c --configure - Configure apache2
#     -a --all - Install and configure apache2
# EOF
#     exit
# }

# parce

# clear
# printf "Start script from ${GREEN}${PWD}${CLEARC}\n"
# sudo apt udpate
# yes | sudo apt install apache2
# clear

#!/bin/bash

RED='\033[1;31m'
BLUE='\033[1;34m'
GREEN='\33[0;32m'
CLEARC='\033[0m'

usage() {
    cat << EOF
    Usage: $(basename "${BASH_SOURCE[0]}") command [args]

    Available commands:
    -h --help - Print this help
    -i --install - Install and configure all requeried packages
    -l --link - make symlinks for site files
    -d --link-dir - make symlinks for dir of site files
EOF
    exit
}

print_ln() {    
    case ${1} in
    Critical) 
        ln_color=${RED} ;;
    Success) 
        ln_color=${GREEN} ;;
    Info) 
        ln_color=${BLUE} ;;
    Default) 
        ln_color=${CLEARC} ;;
    esac

    printf "${ln_color}${2}${CLEARC}\n" 
}

make_link_dir() {
	if [ ! -h /var/www/${1} ]; then
        sudo rm -rf /var/www/${1}
    else 
        sudo rm /var/www/${1}
    fi
    
    sudo ln -s -r ${1} /var/www/

    sudo chown -R ${USER}:${USER} /var/www/${1}
    sudo chmod -R 755 /var/www/${1}
}

install() {
    sudo apt update
    yes Y | sudo apt purge apache2
    yes Y | sudo apt install apache2 postgresql postgresql-contrib libpqxx-4.0v5 libpqxx-dev libcgicc3 libcgicc-dev
    sudo a2dissite 000-default.conf
    sudo a2enmod cgi

    read -p "Enter .conf file name: " choice
    sudo rm -rf /etc/apache2/site-available/${choice}
    rm -rf ${choice}
    touch ${choice}

    printf "
<VirtualHost *:80>
    DocumentRoot \"/var/www/html\"
    <Directory /var/www/html>
        AllowOverride None
        Options FollowSymLinks
        Options +ExecCGI
        AddHandler cgi-script .cgi
    </Directory>
</VirtualHost>
    " >> ${choice}

    sudo cp -rf ${choice} /etc/apache2/sites-available/${choice}
    rm -rf ${choice}
    sudo a2ensite ${choice}

    sudo chown -R ${USER}:${USER} /var/www/html
    sudo chmod -R 755 /var/www/html
    
    cp -rf /etc/apache2/apache2.conf .
    sudo printf "
<Directory /var/www/html>
    AllowOverride None
    Options FollowSymLinks
    Options +ExecCGI
    AddHandler cgi-script .cgi
</Directory>
    " >> apache2.conf

    sudo cp -rf apache2.conf /etc/apache2/apache2.conf
    rm -rf apache2.conf
    sudo systemctl reload apache2.service
    print_ln Success "Web-server install and configure success"

    read -p "Do you want to add symbolic links? (y/N):"	ans
	case $ans in
		[Yy]* ) confirm=1 ;;
		[Nn]* | *) return;;
		* ) echo "Valid answers are Y or N.";;
	esac
    
	if(($confirm==1)); then
        read -p "Enter folder to link: " folder
        make_link_dir ${folder}
	fi;

    exit
}

parse_params() {
    params=''
    while [[ $# -gt 0 ]]; do
        case $1 in
        -h | --help) 
            usage ;;
	    -i | --install) 
            install ;;
        -d | --link-dir)
            make_link_dir ${2};;
        -* | --* | -?*)
            print_ln Critical "Invalid command"
            usage
            break ;;
        esac
        shift
    done
    return 0
}

argc=${$#}
parse_params "$@"

if (( $argc <= 1 )); then
	echo "argc="$argc
	usage
fi