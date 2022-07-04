c99 c_mysql.c -o cmysql `mysql_config --cflags --libs`
Base de datos:
create database mysql_c;

Tablas:
create table informacion(id INT PRIMARY KEY AUTO_INCREMENT, nombre VARCHAR(255) email VARCHAR(255));