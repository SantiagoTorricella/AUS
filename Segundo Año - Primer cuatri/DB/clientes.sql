-- Tabla CLIENTE
CREATE TABLE CLIENTE (
    id_cliente INT PRIMARY KEY AUTO_INCREMENT,
    nombre VARCHAR(100) NOT NULL,
    apellido VARCHAR(100) NOT NULL,
    tipo_doc VARCHAR(20) NOT NULL,
    nmro_doc VARCHAR(50) NOT NULL UNIQUE,
    fecha_nacimiento DATE NOT NULL
);