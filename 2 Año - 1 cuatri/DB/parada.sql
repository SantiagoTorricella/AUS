-- Tabla PARADA
CREATE TABLE PARADA (
    id_parada INT PRIMARY KEY AUTO_INCREMENT,
    id_viaje INT NOT NULL,
    ciudad_id INT NOT NULL,
    orden INT NOT NULL,
    distancia_acumulada_km DECIMAL(8,2) NOT NULL DEFAULT 0.00,
    
    -- Claves foráneas
    FOREIGN KEY (id_viaje) REFERENCES VIAJE(id_viaje),
    FOREIGN KEY (ciudad_id) REFERENCES CIUDAD(id_ciudad),
    
    -- Restricciones para integridad
    UNIQUE(id_viaje, orden), -- Cada viaje tiene un orden único para cada parada
    UNIQUE(id_viaje, ciudad_id), -- Una ciudad no puede aparecer dos veces en el mismo viaje
    CHECK (orden > 0), -- El orden debe ser positivo
    CHECK (distancia_acumulada_km >= 0) -- La distancia no puede ser negativa
);
