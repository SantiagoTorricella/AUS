-- =============================================
-- AUS - Trabajo Práctico Integrador 
-- Bases de Datos 2025
-- Sellart Lucas y Torricella Santiago
-- Sistema de Transporte Argentina
-- =============================================

CREATE DATABASE IF NOT EXISTS sistematransporteargentina;
USE sistematransporteargentina;

-- =============================================
-- DEFINICIÓN DE TABLAS
-- =============================================

create table Cliente (
	Id int not null AUTO_INCREMENT,
	Nombre varchar(50) not NULL,
	Apellido varchar(50) not NULL,
	Fecha_nac DATE not null,
	Tipo_documento varchar(10) not null,
	Numero_documento varchar(20) not null,
	primary key (Id),
	unique (Tipo_documento, Numero_documento)
);

create table Empresa (
	Id int not null AUTO_INCREMENT,
	Nombre varchar(30) not null,
	primary key (Id)
);

create table Provincia (
	Id int not null AUTO_INCREMENT,
	Nombre varchar(30) not null,
	primary key (Id)
);

create table Ciudad (
	Id int not null AUTO_INCREMENT,
	Nombre varchar(30) not NULL,
	Id_provincia int not NULL,
	primary key (Id),
	foreign key (Id_provincia) references Provincia(Id)
);

create table Paradas (
	Id int not null AUTO_INCREMENT,
	Id_ciudad int not null,
	Nombre VARCHAR(50) not NULL,
	primary key (Id),
	foreign key (Id_ciudad) references Ciudad(Id)
);

create table Colectivo (
	Id int not null AUTO_INCREMENT,
	Id_empresa int not null,
	primary key (Id),
	foreign key (Id_empresa) references Empresa(Id) 
);

create table Asiento (
	Id int not null AUTO_INCREMENT,
	Numero int not null,
	Tipo varchar(30) not null,
	Planta int not null,		-- 1 (planta baja), 2 (planta alta)
	Precio decimal (8,2) not null,
	Estado varchar(20) not null,
	Id_colectivo int not null,
	primary key (Id),
	foreign key (Id_colectivo) references Colectivo(Id),
	UNIQUE KEY UQ_Asiento_Colectivo_Numero (Id_colectivo, Numero)
);

create table Viaje (
	Id int not null AUTO_INCREMENT,
	Id_colectivo int not null,
	Fecha_salida DATE not null,
	Horario_salida TIME not null,
	Duracion TIME not null,
	primary key (Id),
	foreign key (Id_colectivo) references Colectivo(Id)
);

CREATE TABLE Viaje_Parada (
    Id_viaje int not null,
    Id_parada int not null,
    Orden INT NOT NULL,
    Distancia_acumulada DECIMAL(6,2) not null,

    PRIMARY KEY (Id_viaje, Id_parada),
    FOREIGN KEY (Id_viaje) REFERENCES Viaje(Id),
    FOREIGN KEY (Id_parada) REFERENCES Paradas(Id)
);

create table Pasaje (
	Id int not null AUTO_INCREMENT,
	Id_cliente int not null,
	Id_viaje int not null,
	Id_asiento int not null,
	primary key (Id),
	foreign key (Id_cliente) references Cliente(Id),
	foreign key (Id_viaje) references Viaje(Id),
	foreign key (Id_asiento) references Asiento(Id),
	UNIQUE KEY UQ_Pasaje_Viaje_Asiento (Id_viaje, Id_asiento)
);


-- =============================================
-- CARGA DE DATOS
-- =============================================

insert into provincia (Id, Nombre)
values
(1,'Santa Fe'),
(2,'Buenos Aires'),
(3,'Cordoba'),
(4,'Misiones'),
(5,'Mendoza'),
(6,'San Luis'),
(7,'Tucuman'),
(8,'Entre Rios'),
(9,'Neuquen'),
(10,'Salta'),
(11,'La Pampa'),
(12,'Rio Negro'),
(13,'La Rioja'),
(14,'Santiago del Estero');


insert into ciudad (Id,Nombre,Id_provincia)
values
(1,'Rosario',1),
(2,'Venado Tuerto',1),
(3,'Rufino',1),

(4,'San Nicolas',2),
(5,'San Pedro',2),
(6,'Ciudad Autonoma Buenos Aires',2),

(7,'Villa María',3),
(8,'Villa Carlos Paz',3),
(9,'Cordoba',3),
(10,'Villa de las Rosas',3),
(11,'Villa Dolores',3),
(12,'Jesus Maria',3),

(13,'Posadas',4),
(14,'Puerto Iguazu',4),
(15,'Montecarlo',4),

(16,'Mendoza',5),
(17,'San Rafael',5),
(18,'Godoy Cruz',5),

(19,'San Luis',6),
(20,'Villa Mercedes',6),
(21,'Merlo',6),

(22,'San Miguel de Tucuman',7),
(23,'Yerba Buena',7),
(24,'Tafi Viejo',7),

(25,'Parana',8),
(26,'Concordia',8),
(27,'Gualeguaychu',8),

(28,'Bariloche',9),
(29,'San Martin de los Andes',9),
(30,'Neuquen',9),

(31,'Cafayate',10),
(32,'Salta',10),
(33,'General Guemes',10),

(34,'Santa Rosa',11),

(35,'Villa Regina',12),

(36, 'Santa Elena',13),

(37,'Loreto',14),
(38,'Santiago del Estero',14);


insert into empresa (Id,Nombre)
values 
(1,'Chevalier'),
(2,'Flechabus'),
(3,'El Rosarino');


insert into cliente (Id,Nombre,Apellido,Fecha_nac,Tipo_documento,Numero_documento)
values
(1,'Lucas','Sellart','2000-08-15','DNI','42.327.986'),
(2,'Santiago','Torricella','2000-08-18','DNI','42.768.475'),
(3,'Maria','Gonzalez','1970-02-05','DNI','32.359.006'),
(4,'Camila','Perez','1996-10-23','DNI','38.144.057'),
(5,'Ricardo','Iorio','1962-06-25','DNI','16.040.052'),
(6,'Julian','Vega','2004-02-19','DNI','45.456.596'),
(7,'Ignacio','Gutierres','2000-02-10','DNI','40.578.926'),
(8,'Micaela','Lopez','1997-04-13','DNI','39.466.139'),
(9,'Carlos','Herrera','1950-12-08','DNI','20.404.500'),
(10,'Cristian','Baez','1977-05-28','DNI','26.428.773');


insert into colectivo (Id,Id_empresa)
values

-- colectivo Chevallier:
(1,1),

-- colectivo Flechabus:
(2,2),

-- colectivo El Rosarino:
(3,3);


insert into asiento (Id,Numero,Tipo,Planta,Precio,Estado,Id_colectivo)
values

-- asientos colectivo Id = 1 (Chevallier)

(1,5,'Cama',1,15000.00,'Ocupado',1),
(2,6,'Cama',1,15000.00,'Ocupado',1),
(3,14,'Semicama',2,9000.00,'Ocupado',1),
(4,17,'Semicama',2,9000.00,'Ocupado',1),

-- asientos colectivo Id = 2 (Flechabus)

(5,3,'Cama',1,17000.00,'Ocupado',2),
(6,6,'Cama',1,17000.00,'Ocupado',2),
(7,12,'Semicama',2,11000.00,'Ocupado',2),
(8,15,'Semicama',2,11000.00,'Ocupado',2),

-- asientos colectivo Id = 3 (El Rosarino)

(9,2,'Cama',1,12000.00,'Ocupado',3),
(10,4,'Cama',1,12000.00,'Ocupado',3),
(11,11,'Semicama',2,8500.00,'Ocupado',3),
(12,16,'Semicama',2,8500.00,'Ocupado',3);


insert into viaje (Id,Id_colectivo,Fecha_salida,Horario_salida,Duracion)
values
(1,1,'2025-08-10','06:00:00', '04:10:00'),			-- Viaje 1 (Rosario - Buenos Aires)

(2,2,'2023-10-01','09:00:00', '07:00:00'),			-- Viaje 2 (Rosario - Villa Carlos Paz)

(3,3,'2023-10-01','08:00:00','31:00:00'),			-- Viaje 3 (Rosario - Bariloche)

(4,2,'2023-10-01','10:00:00','19:25:00'),			-- Viaje 4 (Rosario - Mendoza)

(5,1,'2023-10-01','14:00:00','17:15:00');			-- Viaje 5 (Rosario - Salta)


INSERT INTO Paradas (Id, Id_ciudad, Nombre) 
VALUES
(1, 1, 'Rosario'),
(2, 4, 'San Nicolás'),
(3, 5, 'San Pedro'),
(4, 6, 'Buenos Aires'),

(5, 1, 'Rosario'),
(6, 7, 'Villa María'),
(7, 9, 'Córdoba'),
(8, 8, 'Villa Carlos Paz'),

(9, 1, 'Rosario'),
(10, 2, 'Venado Tuerto'),
(11, 3, 'Rufino'),
(12, 34, 'Santa Rosa'),
(13, 35, 'Villa Regina'),
(14, 30, 'Neuquén'),
(15, 28, 'Bariloche'),

(16, 1, 'Rosario'),
(17, 7, 'Villa María'),
(18, 10, 'Villa de las Rosas'),
(19, 11, 'Villa Dolores'),
(20, 21, 'Merlo'),
(21, 19, 'San Luis'),
(22, 16, 'Mendoza'),

(23, 1, 'Rosario'),
(24, 7, 'Villa María'),
(25, 9, 'Córdoba'),
(26, 12, 'Jesus María'),
(27, 36, 'Santa Elena'),
(28, 37, 'Loreto'),
(29, 38, 'Santiago del Estero'),
(30, 22, 'San Miguel de Tucumán'),
(31, 33, 'General Guemes'),
(32, 32, 'Salta');


INSERT INTO Viaje_Parada (Id_viaje, Id_parada, Orden, Distancia_acumulada) 
VALUES
(1, 1, 1, 0.00),      	-- Rosario
(1, 2, 2, 80.00),     	-- San Nicolás
(1, 3, 3, 150.50),     	-- San Pedro
(1, 4, 4, 310.50);     	-- Ciudad Autónoma de Buenos Aires

-- Paradas del Viaje 2
INSERT INTO Viaje_Parada (Id_viaje, Id_parada, Orden, Distancia_acumulada) 
VALUES
(2, 5, 1, 0.00),       -- Rosario
(2, 6, 2, 250.00),     -- Villa María
(2, 7, 3, 400.00),     -- Córdoba
(2, 8, 4, 480.00);     -- Villa Carlos Paz

-- Paradas del Viaje 3
INSERT INTO Viaje_Parada (Id_viaje, Id_parada, Orden, Distancia_acumulada) 
VALUES
(3, 9, 1, 0.00),       	-- Rosario
(3, 10, 2, 170.00),     -- Venado Tuerto
(3, 11, 3, 270.00),     -- Rufino
(3, 12, 4, 670.00),     -- Santa Rosa
(3, 13, 5, 1100.00),    -- Villa Regina
(3, 14, 6, 1200.00),    -- Neuquén
(3, 15, 7, 1600.00);    -- Bariloche

-- Paradas del Viaje 4
INSERT INTO Viaje_Parada (Id_viaje, Id_parada, Orden, Distancia_acumulada) 
VALUES
(4, 16, 1, 0.00),      -- Rosario
(4, 17, 2, 250.00),    -- Villa María
(4, 18, 3, 560.00),    -- Villa de las Rosas
(4, 19, 4, 620.00),    -- Villa Dolores
(4, 20, 5, 700.00),    -- Merlo
(4, 21, 6, 890.00),    -- San Luis
(4, 22, 7, 1100.00);   -- Mendoza

-- Paradas del Viaje 5
INSERT INTO Viaje_Parada (Id_viaje, Id_parada, Orden, Distancia_acumulada) 
VALUES
(5, 23, 1, 0.00),        -- Rosario
(5, 24, 2, 250.00),      -- Villa María
(5, 25, 3, 400.00),      -- Córdoba
(5, 26, 4, 460.00),      -- Jesús María
(5, 27, 5, 1100.00),     -- Santa Elena
(5, 28, 6, 1700.00),     -- Loreto
(5, 29, 7, 1760.00),     -- Santiago del Estero
(5, 30, 8, 1900.00),     -- San Miguel de Tucumán
(5, 31, 9, 2100.00),     -- General Güemes
(5, 32, 10, 2150.00);    -- Salta



insert into pasaje (Id,Id_cliente,Id_viaje,Id_asiento)
values
(1,1,1,1),			-- Cliente Id = 1
(2,2,1,3),			-- Cliente Id = 2
(3,3,2,4),			-- Cliente Id = 3
(4,4,2,5),			-- Cliente Id = 4
(5,5,3,6),			-- Cliente Id = 5
(6,6,3,8),			-- Cliente Id = 6
(7,7,4,10),			-- Cliente Id = 7
(8,8,4,12),			-- Cliente Id = 8
(9,9,5,13),			-- Cliente Id = 9
(10,10,5,14);		-- Cliente Id = 10







