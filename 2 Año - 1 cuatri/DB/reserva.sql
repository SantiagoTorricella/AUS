-- Tabla CLIENTECREATE TABLE CLIENTE (    id_cliente INT PRIMARY KEY AUTO_INCREMENT,    nombre VARCHAR(100) NOT NULL,    apellido VARCHAR(100) NOT NULL,    tipo_doc VARCHAR(20) NOT NULL,    nmro_doc VARCHAR(50) NOT NULL UNIQUE,    fecha_nacimiento DATE NOT NULL);

-- Tabla RESERVA
CREATE TABLE RESERVA (
    id_reserva INT PRIMARY KEY AUTO_INCREMENT,
    cliente_id INT NOT NULL,
    asiento_id INT NOT NULL,
    parada_origen_id INT NOT NULL,
    parada_destino_id INT NOT NULL,
    fecha_reserva DATETIME DEFAULT CURRENT_TIMESTAMP,
    
    -- Claves foráneas
    FOREIGN KEY (cliente_id) REFERENCES CLIENTE(id_cliente),
    FOREIGN KEY (asiento_id) REFERENCES ASIENTO(id_asiento),
    FOREIGN KEY (parada_origen_id) REFERENCES PARADA(id_parada),
    FOREIGN KEY (parada_destino_id) REFERENCES PARADA(id_parada),
    
    -- Restricción para asegurar que origen y destino sean diferentes
    CHECK (parada_origen_id != parada_destino_id)
);