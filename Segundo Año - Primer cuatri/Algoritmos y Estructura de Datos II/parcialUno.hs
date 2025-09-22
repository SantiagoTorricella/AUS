-- Ejercicio 1 (a y b)

{-
a)isosceles :: Int ->Int ->Int->Bool
que dadas la longitud de los lados de un triangulo nos dice si es un triangulo isosceles.-
-}

isosceles :: Int -> Int -> Int -> Bool
isosceles a b c = (a == b) || (b == c) || (a == c)

{-  
collect :: [(k, v)] → toma un lista de pares (clave, valor) y asocia cada clave ´unica con todos
los valores con los que estaba apareada originalmente. Por ejemplo: collect
-}

collect :: [(k,v)] -> [(k,[v])]
collect [] = []
collect ((k,v):xs) = insertValue key val (collect xs)
    where
        insertValue key val [] = [(key,[val])]
        insertValue key val ((k,vs):resto)
            | key == k = (key,val:vs) : resto
            | otherwise = insertValue key val resto

-- Ejercicio 2  Definí por lista por compresion las funciones ( a y b )

{-
a. cambios :: [a] -> [Int] , que dada una lista, devuelve la lista de los ı́ndices en que la lista
cambia. Es decir, dada la lista s retorna la lista con los i tal que si != si+1
cambios [1, 1, 1, 3, 3, 1, 1] = [2, 4]
-}

cambios :: [a] -> [Int]
cambios xs = [i | i <- [0.. length xs - 2], xs !! i \= xs !! (i + 1) ]

{-
b. abundantes :: [Integer] que es la lista de todos los números abundantes. Un número natural
 n se denomina abundante si es menor que la suma de sus divisores propios. Por ejemplo, 12
 y 30 son abundantes pero 5 y 28 no lo son. Por ejemplo abundates = [12, 18, 20, 24, 30, 36, ...
-}
abundantes :: [Int]
abundantes  = [x | x <- [1..],x < sumaDivisores x]

sumaDivisores :: Int -> Int
sumaDivisores x = sum [ d | d <- [1..x-1], x `mod` d == 0]

-- Ejercicio 3 Dar al menos dos ejemplos de funciones con el siguiente tipo:**  
-- (Bool -> Int) -> (Int -> Bool)

ejercicio3A :: (Bool -> Int) -> (Int -> Bool)
ejercicio3A f = \x -> f True == x

ejercicio3B :: (Bool -> Int) -> (Int -> Bool)
ejercicio3B = \x -> x > f False

-- Ejercicio 4 | Dar el tipo de las siguientes funciones
foo p  = if p then (p ∧) else (p ∨)
foo :: Bool -> (Bool -> Bool)

{-
Ejercicio 5. Dado el tipo de datos de árboles binarios:
data Arb = E | H Int | N Arb Arb
y el tipo de datos de comandos, para navegar el árbol:
data Cmd = L | R
a) ¿Qué tipo tiene Hoja?
b) Definir la función parcial selec::[Cmd] → Arb → Arb, que selecciona el subárbol correspondiente.
Por ej:
                /\
select [L,R] ( /  \ ) = Hoja 4
              /\   5
             /  \
            3    4
La función selec es parcial, ya que no está definida para listas de comandos erróneas (como por
ejemplo, ir a la izquierda cuando nos encontramos en una hoja).
-}
data Arb = E | H Int | N Arb Arb

H :: Int -> Arb

selec :: [Cmd] -> Arb -> Arb
selec [] arb = arb  
selec (L:cs) (N izq _) = selec cs izq  
selec (R:cs) (N _ der) = selec cs der 