-- Ejercicio 1 b
collect :: [(k,v)] -> [(k,[v])]
collect [] = []
collect ((k,v):xs) = insertValue k v (collect xs)
    where
        insertValue key val [] = [(key,[val])];
        insterValye key val ((k,vs):rest)
            | key == k = (k, val:vs) : rest
            | otherwise = (k , vs) : insertValue key val rest




-- Ejercicio 1 d
import Data.List (nub)

paresIguales :: Int -> Int -> Int -> Int -> Bool
paresIguales a b c d = 
    let lista = [a,b,c,d] -- creo la lista
        duplicados = nub lista -- saco los duplicados
    in length duplicados == 2 && all(\x -> contar x lista == 2) duplicados -- comparo las longitudes

contar :: Eq a => a -> [a] -> Int
contar x [] = 0
contar x (y:ys)
    | x == y = 1 + contar x ys 
    | otherwise = contar x ys  

-- Ejercicio 1 e
isosceles :: Int -> Int -> Int -> Bool  
isosceles a b c = 
    (a == b && b /= c) ||
    (a == c && c /= b) ||
    (b == c && c /= a)

-- Ejercicio 1 f
ror :: Int -> [a] -> [a]
ror n xs =  
    let (ini, fin) =  separar n xs
    in fin ++ ini

separar :: Int -> [a] -> ([a], [a])
separar 0 xs = ([], xs)
separar _ [] = ([], [])
separar n (x:xs) =
    let (ini, fin) = separar (n-1) xs
    in (x:ini, fin)
        
-- Ejercicio 1 g




-- Practica 2




