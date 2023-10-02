data Vertice = Vertice {nombre::Int} deriving (Eq)

instance Show (Vertice) where show (Vertice n) = show (n)

data Arista = Arista {orig::Vertice, dest::Vertice, peso::Int} deriving Eq

instance Show (Arista) where show (Arista orig dest peso) = "("++(show orig)++"->"++(show dest)++","++(show peso)++")"

--getOrig (Arista o d ) = o

--getDest (Arista o d) = d

v1 = Vertice   1 
v2 = Vertice   2     
v3 = Vertice   3 
v4 = Vertice   4 
v5 = Vertice   5 

a1 = Arista v1 v2 5
a2 = Arista v1 v3 2
a3 = Arista v1 v4 3
a4 = Arista v2 v5 1
a5 = Arista v3 v2 2 
a6 = Arista v4 v2 1 
a7 = Arista v4 v3 4
a8 = Arista v4 v5 7

verticesprueba = [v1,v2,v3,v4,v5]

aristasprueba = [a1,a2,a3,a4,a5,a6,a7,a8]

data Grafo = Grafo {vertices::[Vertice], aristas::[Arista]} deriving Show

grafoprueba = Grafo verticesprueba aristasprueba

at:: [a] -> Int -> a
at xs i = xs !! (i-1)

type VC = [Vertice]

type VNC = [Vertice]

type Peso = Int

type Pacu = [Peso]

type Prev = [Vertice]

type Aristas = [Arista] 

vercono v = filter (\x->x==v) verticesprueba

vernocono v = filter (\x->x/=v) verticesprueba 

data Dijkstra = Dij {a::Aristas, vc::VC, vnc::VNC, pacu::Pacu, prev::Prev} deriving Show

oo = 100


verticenulo = Vertice 0

costo::Aristas -> Vertice -> Vertice -> Peso
costo as o d = if (filtrado == []) then oo else (peso $ head $ filtrado)
   where filtrado = filter (\a->(orig a == o && dest a == d)) as

--peso $ head $ ( filter (\a->(orig a == o && dest a == d)) as)

previnicial v = map (\x->if (x==v) then v else verticenulo) verticesprueba

acuinicial a v = map (\x->if (x==v) then 0 else (costo a v x)) verticesprueba

cambiarnth:: a -> Int -> [a] -> [a]
cambiarnth a n [] = []
cambiarnth a 0 (x:xs) = a:xs
cambiarnth a n (x:xs) = x:(cambiarnth a (n-1) xs)

generarinicial :: Vertice -> Dijkstra
generarinicial v = Dij (aristasprueba) (vercono v) (vernocono v) (acuinicial (aristasprueba) v) (previnicial v)

getpeso:: Pacu -> Vertice -> Peso
getpeso p v = at p (nombre v) 


actpeso::(Pacu , Prev) -> Aristas ->(Pacu,Prev)
actpeso (p, pr) [] = (p,pr)
actpeso (p, pr) (a:as) = actpeso (nuevocos,nuevopre)   as
   where cambiar  = cambiarnth (costonuevo) (nombre (dest a)-1) p
         cambiarpre = cambiarnth (dest a) (nombre (orig a)-1) pr
         costonuevo = (peso a) + getpeso p (orig a)
         nuevocos  = if ((costonuevo) < getpeso p (dest a)) then cambiar else p 
         nuevopre  = if ((costonuevo) < getpeso p (dest a)) then cambiarpre else pr 


iteracion::Dijkstra -> Dijkstra
iteracion d = Dij (a d) (nuevocon d) (nuevonocono d) (nuevoacu d) (nuevoprev d)
     where next = foldl (\x y->if ((getpeso (pacu d) x) < (getpeso (pacu d) y)) then x else y) (head $ vnc d) (vnc d) 
           nuevocon d = (next):(vc d) 
           nuevonocono d = filter (/=next ) (vnc d)
           acandidata = filter (\x-> orig x == next) (a d)
           avalidas   = filter (\x-> dest x `elem` (vnc d)) acandidata
           resul      = actpeso (pacu d,prev d) avalidas
           nuevoacu d = fst resul 
           nuevoprev d = snd resul  

caminocorto :: Dijkstra -> Dijkstra
caminocorto d  
  | vnc d  == [] = d
  | otherwise = caminocorto $ iteracion d

--caminocorto (Dij a c [] ac pr) = Dij a c [] ac pr
--caminocorto (Dij a c nc ac pr) = 


