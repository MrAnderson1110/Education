create database railroad;
\c railroad
create table if not exists trains (
	id int primary key,
	train_name varchar(100),
	train_time varchar(100)
);

insert into trains values 
(1, 'first train', '01:00'),
(2, 'second train', '02:00'),
(3, 'third train', '03:00'),
(4, 'fourth train', '04:00'),
(5, 'fifth train', '05:00'),
(6, 'sixth train', '06:00');

create user train_user with encrypted password 'user_pass';
create user train_root with encrypted password 'root_pass';
grant all privileges on database railroad to train_root;
grant select, insert, update, delete on trains to train_user;
grant connect on database railroad to train_user;