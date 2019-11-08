 CREATE TABLE lm_gate (id TIMESTAMP,name BINARY(32),modbus_tcp BOOL,modbus_rtu BOOL);
 CREATE TABLE lm_modbus_tcp (id TIMESTAMP,name BINARY(64),server_ip BINARY(32),server_port int,enable BOOL);
 CREATE TABLE lm_modbus_rtu (id TIMESTAMP,name BINARY(64),device BINARY(32),baud INT,parity TINYINT,data_bit INT,stop_bit INT,enable BOOL);
 