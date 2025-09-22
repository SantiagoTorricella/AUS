{- 
1) Tipo [(Indice,Dato)] representa un mensaje
Type  Dato = <completar>
Type  Indice = <completar>
Type  Paquete =  <completar>
<completar>  Mensaje =  [Paquete]


a)  UltimPaq  toma  f  y  Mensaje  xs  devuelve Paquete correspondiente en el primero  o  último      
lugar en el orden del mensaje comp.  dependiendo que funcion  f  se utilice  
Ej:  ultimoPaq ascend [(3,Mundo),(1,Hola),(4,!), (2, “ ”)] = (4, “! ”)
             UltPaq f < completar >                                                      =  < completar >
             UltPaq  f  (x : y :  xs)  |  f <completar >  <completar >           =  < completar >
                                               |  f otherwise < completar > =  < completar >
             ascendente   < completar >  < completar >   =  < completar >

c) Faltantes, solo con listas por comprensión, dado Mensaje  xs  ordenado ascendentemente devuelve [ Indice ] de los paquetes faltantes.  
    Faltantes [(1,”Hola”), (3,”Mundo”), (6,”!”] = [2,4,5].  Puede usar concat

b) En orden Asc usando foldr y map, dado un mensaje retorna si los paquetes estan ordenados ascendentemente o no.
    EnOrdenAsc xs  = let as = map  < completar >  xs  (retorna Indice) 
                                   ady = zip os (tail os)  (completar el comentario diciendo que hace)
                                   in foldr < completar > True ady
-}

type Dato = String
type Indice = Int
type Paquete = (Indice, Dato)
type Mensaje = [Paquete]

ultimoPaq :: (Paquete -> Paquete -> Bool) -> Mensaje -> Paquete
ultimoPaq _ [] = error "No se puede obtener el último paquete de un mensaje vacío"
ultimoPaq _ [x] = x
ultimoPaq f (x:y:xs) 
                    | f x y = ultimoPaq f (y:xs)
                    | otherwise = ultimoPaq f (x:xs)

ascendente :: Paquete -> Paquete -> Bool
ascendente (i1,_) (i2,_) = i1 < i2    

enOrdenAsc :: Mensaje -> Bool
enOrdenAsc xs = let os = map fst xs  -- Extrae los índices
                    ady = zip os (tail os)  -- Crea pares de índices adyacentes
                in foldr (\(a,b) acc -> a < b && acc) True ady

faltantes :: Mensaje -> [Indice]
faltantes xs = [i | i <- [1..maxIndex], i `notElem` indices]
  where 
    indices = [i | (i, _) <- xs]
    maxIndex = maximum indices

{-
2) Data  BST a  =  E  |   N  (BST a) a (BST a)
    Type msnTree = BST (Indice,Dato)
a) Suponga que los paquetes llegan (1,“Hola”), (s,”1” ),(6,”!”), (3,”Mundo”) ,(2,” “) ,(4,” “)  Escribir la    
    representacion del mensaje en el tipo  msnTree.
b) Definir mensaje msnTree , retorna Info completa que resulta de pegar datos en los paquetes en   
    orden. Ej: mensaje[(1,”Hola”),(3,”Mundo”),(2,” “)] = “Hola mundo”
-}

data  BST a  =  E | N  (BST a) a (BST a)

type MsnTree = BST (Indice,Dato)

arbolMensaje :: MsnTree
arbolMensaje = N
                
                (N
                 (N E (1,"hola") E)
                 (2,"") 
                 E
                )
                
                (3, "Mundo")
                
                (N
                 (N E (4,"") E)
                 (5,"`")
                 (N E (6,"!") E)
                )

mensaje E = ""
mensaje (N izq (_, d) der) = mensaje izq ++ d ++ mensaje der

{-
3) Dar el tipo de ruda  f g h = f(gh)(gh)
-}
{-
h : a
g se le aplica h entonces gh: a->b
f se le aplican las dos, asi que es de tipo b->b->c
-}

-- ruda :: (b -> b -> c) -> (a -> b) -> a -> c

{-
4) Para el tipo leftist heaps:
a – Que es una espina en un arbol? Que es el rango de una  leftist Heaps?
b – Invariante de Heaps y leftist Heaps
c – Consecuencias que tienen el/los invariantes de Ieftist Heaps
-}

{-
Espina: el camino mas corto desde la raiz hasta una hoja vacia
Rango leftist: Es la longitud de la espina

Invariante Heap: todo nodo es menor a todos los valores de sus hijos
Invariante LEFTISTL: el rango de cualq hijo izq es mayor igual que al de su hermano derecho

La espina derecha es corta, pq por el invariante la rama derecha es siempre la mas corta
No es un arbol perfectamente balanceado pero asegura que no se desequilibre mucho -> operaciones siguen siendo rapidas

-}