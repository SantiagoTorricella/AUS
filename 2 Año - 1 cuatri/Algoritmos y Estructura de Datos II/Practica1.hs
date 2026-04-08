-- Ejercicio 1

--  1.a: borrarUltimo que dada una lista borra el  ́ultimo elemento de la lista. No utilizar reverse, ni
--  tail.

borrarUltimo :: [a] -> [a]
borrarUltimo [] = [] -- Aseguro caso lista vacia
borrarUltimo (x:xs) = 
    if xs == [] 
    then [] 
    else x : borrarUltimo xs  

-- Otra forma de hacerlo

borrarUltimo :: [a] -> [a]
borrarUltimo [] = [] -- Aseguro caso lista vacia
borrarUltimo [x] = [] 
borrarUltimo (x:xs) = x : borrarUltimo xs

-- 1.b collect :: [(k, v)] → toma un lista de pares (clave, valor) y asocia cada clave  ́unica con todos
-- los valores con los que estaba apareada originalmente.

collect :: [(k,v)] -> [(k,[v])]
collect [] = []
collect ((k,v):xs) = 
    (k , v : mismos) : collect otros
    where
        mismos = [v' | (k',v') <- xs, k' == k]
        otros = [(k',v') | (k',v') <- xs , k'/=k]

-- 1.c serie que se comporta de la siguiente manera: serie [1, 2, 3] = [[ ], [1], [1, 2], [1, 2, 3]] 
-- Dar su tipo mas general.

serie :: [a] -> [[a]]
serie [] = [[]]
serie (x:xs) = serie xs : x

-- 1.d paresIguales :: Int → Int → Int → Int → Bool toma 4 numeros enteros y retorna True si de
--  dos en dos son iguales (en cualquier orden), en los demas casos retorna False. Por ejemplo:
--  paresIguales 3 1 1 2 = False paresIguales 3 1 3 1 = True paresIguales 3 3 1 1 = True
--  paresIguales 3 1 1 3 = True

paresIguales :: Int -> Int -> Int -> Int -> Bool
paresIguales a b c d =
    (a == b && c == d) ||
    (a == c && b == d) ||
    (a == d && b == c)

-- 1.e isosceles :: Int → Int → Int → Bool que dadas la longitud de los lados de un triangulo nos
-- dice si es un triangulo isosceles.

isosceles :: Int -> Int -> Int -> Bool
isosceles a b c =
    (a == b && a /= c) ||
    (a == c && a /= b) ||
    (b == c && b /= a)

-- 1.f ror que dada una lista xs y un entero n, tal que n =< lenght xs, rota los primeros n elementos
-- de xs a la derecha: ror 3 [1, 2, 3, 4, 5] = [4, 5, 1, 2, 3]. Definir una version recursiva de ror ,
-- sin usar drop, take ni tail.

rotarUno :: [a] -> [a]
rotarUno [] = []
rotarUno (x:xs) = xs ++ [x]

ror :: [a] -> [a]
ror 0 xs = xs
ror n xs = ror (n-1) (rotarUno xs)

-- 1.g g) upto :: Int → Int → [Int] que dado dos numeros enteros n y m devuelve la lista [n, n + 1, n +
-- 2, ..., m ] en caso que n 6 m y la lista [ ] en otro caso. No usar listas por comprensi ́on.

upto :: Int -> Int -> [Int]
upto n m =
    if n > m then []
    else if n == m then [m]
    else [n] ++ upto (n + 1) m

upto n m =
    if n > m then []
    else n : upto (n + 1) m

upto :: Int -> Int -> [Int]
upto n m = 
    | n > m     = []
    | otherwise = n : upto (n + 1) m    

-- h) eco que devuelve la cadena obtenida a partir de la cadena xs repitiendo cada elemento tantas
-- veces como indica su posicion. No usar listas por comprension.
-- Por ejemplo: eco "hola" = "hoolllaaaa"

appendear :: Char -> Int -> String
appendear _ 0 = []
appendear x n = x : appendear x (n - 1)

eco :: String -> String
eco xs = ecoAux xs 1

ecoAux :: String -> Int -> String
ecoAux [] _ = []
ecoAux (x:xs) pos =
    appendear x pos ++ ecoAux xs (pos + 1)