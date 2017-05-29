{-|
Module          : Main
Description     :: Módulo Haskell com funções que determinam a solução de um tabuleiro recebido.
Copyright       : Carlos Pereira <carloscdap@gmail.com>
	   	  Rafael Braga <rafael.braga.gc@gmail.com>

Conjunto de funções que, dado um tabuleiro simples ou complicado, determinam os comandos necessários para a sua resolução. Nota: estas funções determinam uma solução possível para a resolução de um dado tabuleiro, mas esta solução pode não ser a solução ótima. -}

module Main where

import Data.Char

{-| /LightsOff/ - coordenadas (x, y) de uma luz. -}

type LightsOff  = (Int, Int)

{-| /InitStatus/ - informações de um tabuleiro recebido (tabuleiro, altura do tabuleiro, posição inicial do robô, lista de luzes pertencentes ao tabuleiro). -}

type InitStatus = ([String], Int, String, [LightsOff])

{-| /Position/ - posição do robô com coordendas x, y e orientação. -}
 
type Position   = (Int, Int, Orientation)

{-| /Pos/ - posição (x, y) do robô. -}

type Pos        = (Int, Int)

{-| /Size/ - largura e altura do tabuleiro. -}

type Size       = (Int, Int)

{-| /Status/ - estado do tabuleiro, contém o tabuleiro, a posição onde o robô se encontra, a largura e a altura do tabuleiro, a lista de luzes, duas listas de soluções auxiliares inicializadas com o valor /'N/' e o tipo de tabuleiro: True se for complicado e False se for simples. -} 

type Status     = ([String], Position, Size, [LightsOff], [[Char]], [[Char]], Bool)

{-| /PCondition/ - parâmetros para determinar a solução de uma dada posição do robô para uma dada luz. -}

type PCondition = ([String], Pos, Pos, Size, [[Char]])

{-| /PCompare/ - valores para comparar se o robô pode mover-se para a posição seguinte, conforme a sua orientação. -}  

type PCompare   = (Int, Int, Int, Int)

{-| /SolveP/ - parâmetros para a obtenção dos comandos provenientes da movimentação do robô até uma luz. -}

type SolveP     = ([String], Position, Size, [[Char]], [LightsOff])

{-| /LightP/ - parâmetros para determinar se durante o movimento do robô até uma dada luz ele passa por outra luz. -}

type LightP     = ([String], Pos, Size, [LightsOff])

{-| /Orientation/ - orientações possíveis do robô. -}

data Orientation = N | E | S | O
	deriving (Enum, Eq)

-- funções principais

{-| 'main' recebe o /std input/ de um ficheiro. Devolve a mensagem resultante da função /process/. -}

main = do s <- getContents
	  putStrLn (process (lines s))

{-| 'process' faz o processamento do tabuleiro, das coordenadas iniciais do robot, das lâmpadas por acender e das dimensões do tabuleiro. Determina se o tabuleiro é simples ou complicado e cria a matriz auxiliar para determinar a solução do tabuleiro. Esta matriz é inicializada com o valor /'N/' e contem o mesmo tamanho que o tabuleiro. Caso o tabuleiro seja complicado determina-se a prioridade das luzes. De seguida procede-se à obtenção da solução. -}

process :: [String] -> String
process s = let (board, height, c, lights) = initStatus s
                (x, y, o) = getCoord (words (c)) 0
                width     = length (head board)
                bType     = isComplicated board
                sol       = createAuxMatrix board
            in if (bType) 
               then let lightsF = getFinalL (board, (x, y, o), (width, height), lights, sol, sol, bType)
	             in getSolution (board, (x, y, o), (width, height), lightsF, sol, sol, bType)
               else getSolution (board, (x, y, o), (width, height), lights, sol, sol, bType)

-- Funções de tratamento do tabuleiro

{-| 'initStatus' separa os dados recebidos. Devolve o tabuleiro, a sua altura, a posição inicial do robô e a a lista de luzes.

>>> ["aaA","abC","Aaa", "0 0 N"]
(["aaA","abC", "Aaa"], 3, "0 0 N", [(2,2), (2,1), (0, 0)])
-} 

initStatus :: [String] -> InitStatus
initStatus []    = ([], 0, [], [])
initStatus [p]   = ([], 0, p, [])
initStatus (h:t) = let (b, height, p, l) = initStatus t
                       lOff = map (\x -> (x, height)) (getLC h 0)
		     in ([h] ++ b, 1 + height, p, lOff ++ l)  

{-| 'getLC' devolve as coordenadas x das luzes presentes numa dada linha do tabuleiro.

>>> "aaAaB" 
[2, 4]
-}

getLC :: String -> Int -> [Int]
getLC [] _                = []
getLC (h:t) c | isUpper h = c : (getLC t (c + 1))
	       | otherwise = getLC t (c + 1)

{-| 'getCoord' converte uma lista de /String/ com o formato adequado para uma /Position/ do robô.

>>> ["0","0,"N"]
(0, 0, N)
-}

getCoord :: [String] -> Int -> Position
getCoord [o] _   = (0, 0, toOrientation (head o))
getCoord (h:t) c = let (x, y, o) = getCoord t (c + 1)
		     in case c of 
                            0 -> ((read(h) :: Int) + x, y, o)
                            1 -> (x, (read(h) :: Int) + y, o)

{-| 'isComplicated' determina se um tabuleiro é complicado ou não.

>>> ["aaa","aaB"]
False

>>> ["ccc","cDc"]
False

>>> ["aabC","aaaa"]
True
-}

isComplicated :: [String] -> Bool
isComplicated board = let ac         = ((board !! 0) !! 0)
                          (min, max) = getInfo board (toLower ac, toLower ac)
                      in if ((ord (toLower max)) - (ord (toLower min)) > 1)
                         then True
                         else False

{-| 'getInfo' percorre o tabuleiro. Para cada linha determina o seu máximo e mínimo. Atualiza o máximo e mínimo a cada linha do tabuleiro. -}

getInfo :: [String] -> (Char, Char) -> (Char, Char)
getInfo [] x             = x
getInfo (h:t) (min, max) = let (l, g) = getMinMax h (min, max)
                           in getInfo t (l, g) 

{-| 'getMinMax' obtém a altura máxima e a altura mínima de uma linha do tabuleiro. Converte estes valores para minúsculas. 

>>> "aaBcD"
('a', 'd')
-}

getMinMax :: String -> (Char, Char) -> (Char, Char)
getMinMax [] x             = x
getMinMax (h:t) (min, max) = let (l, g) = getMinMax t (min, max)
                             in if ((toLower h) < min)
                                then (toLower h, g)
                                else if ((toLower h) > g)
                                     then (l, toLower h)
                                     else (l, g)

{-| 'createAuxMatrix' cria a matriz auxiliar para a resolução do tabuleiro. A matrix criada tem o mesmo tamanho que o tabuleiro e é inicializada com o valor /'N'/ (este caráter assinala uma posição que o robô ainda não visitou.

>>> ["aaA","abc"]
["nnn","nnn"]
-}

createAuxMatrix :: [String] -> [[Char]]
createAuxMatrix []    = []
createAuxMatrix (h:t) = (foldr (\x ac -> 'N' : ac) [] h) : (createAuxMatrix t)

{-| 'toOrientation' converte um caráter para orientação. -}
                         
toOrientation :: Char -> Orientation
toOrientation 'N' = N
toOrientation 'E' = E
toOrientation 'S' = S
toOrientation 'O' = O

-- Funções de obtenção de solução

{-| 'getSolution' obtém a solução do tabuleiro. A função termina quando todas as luzes estão acessas, ou caso não existam luzes. Determina a solução para cada luz presente no tabuleiro. As coordenadas do robô são atualizadas quando este acende uma luz (passam a ser as coordenadas da luz). Conforme o tabuleiro seja complicado (ou não), é executada a solução complicada ou fácil. -}

getSolution :: Status -> String
getSolution (_, _, _, [], _, _, _)                      = []
getSolution (b, (x, y, o), s, ((xF, yF):t), sol, p, tp) = 
       if (tp) 
       then let strC = solve (b, (x, y, o), s, (fst (complicatedPath (b, (x, y), (xF, yF), s, sol) p)), t)
            in auxSolution (b, (x, y, o), s, ((xF, yF):t), sol, p, tp) strC
       else let strE = solve (b, (x, y, o), s, (easyPath (b, (x, y), (xF, yF), s, sol)), t)
            in auxSolution (b, (x, y, o), s, ((xF, yF):t), sol, p, tp) strE

{-| 'auxSolution' é uma função auxiliar que atualiza a orientação do robô e a lista de luzes. -}

auxSolution :: Status -> String -> String
auxSolution (b, (x, y, o), s, ((xF, yF):t), sol, p, tp) str =
       let oF = calcOrientation str o
           lF = updateList str t (x, y, o)
       in str ++ (getSolution (b, (xF, yF, oF), s, lF, sol, p, tp))  


{-| 'calcOrientation' atualiza a orientação do robô conforme os comandos recebidos da solução de uma luz. -}

calcOrientation :: String -> Orientation -> Orientation
calcOrientation [] o                = o
calcOrientation (h:t) o | h == 'D'  = calcOrientation t (right o)
                        | h == 'E'  = calcOrientation t (left o)
                        | otherwise = calcOrientation t o


{-| 'change' muda a posição (x, y) do robô conforme a sua orientação. -}

change :: Orientation -> (Int, Int)
change N = (0, 1)
change E = (1, 0)
change S = (0, -1)
change O = (-1, 0)


{-| 'updateList' função para a atualização da lista de luzes. Ao deslocar-se para uma luz, o robô pode passar por cima de outra luz. Quando isto acontece, o robô acende também essa luz. Esta função serve para tratar estes casos, removendo essa ou essas luzes acesas pelo caminho da lista de luzes. -}

updateList :: String -> [LightsOff] -> Position -> [LightsOff]
updateList [] l _            = l
updateList (h:t) l (x, y, o) = let lF = filter (\a -> a /= (x, y)) l
                               in case h of
                                      'L' -> updateList t lF (x, y, o)
                                      'D' -> updateList t lF (x, y, right o)
                                      'E' -> updateList t lF (x, y, left o)
                                      _   -> let (j, i) = change o
                                             in updateList t lF (x + j, y + i, o)


{-| 'solve' traduz a lista de soluções para comandos do robô. -}

solve :: SolveP -> String
solve (b, (x, y, o), (w, h), s, l) =
       case ((s !! (h - 1 - y)) !! x) of
           'T' -> "L"
           'U' -> (checkLight (b, (x, y), (w, h), l)) ++ (rotation o N) ++ (advance b (x, y) (x, y + 1) (w, h)) ++ (solve (b, (x, y + 1, N), (w, h), s, l))
           'R' -> (checkLight (b, (x, y), (w, h), l)) ++ (rotation o E) ++ (advance b (x, y) (x + 1, y) (w, h)) ++ (solve (b, (x + 1, y, E), (w, h), s, l))
           'D' -> (checkLight (b, (x, y), (w, h), l)) ++ (rotation o S) ++ (advance b (x, y) (x, y - 1) (w, h)) ++ (solve (b, (x, y - 1, S), (w, h), s, l))
           'L' -> (checkLight (b, (x, y), (w, h), l)) ++ (rotation o O) ++ (advance b (x, y) (x - 1, y) (w, h)) ++ (solve (b, (x - 1, y, O), (w, h), s, l)) 



{-| 'advance' é uma função auxiliar que determina se o robô anda ou salta, quando este avança uma posição no tabuleiro. -}

advance :: [String] -> Pos -> Pos -> Size -> String
advance b (x, y) (xF, yF) (w, h) | (toLower ((b !! (h - 1 - yF)) !! xF)) == (toLower ((b !! (h - 1 - y)) !! x)) = "A"
                                 | otherwise                                                                    = "S"  


{-| 'checkLight' determina se uma dada posição do tabuleiro é uma lâmpada e se esta está desligada. Caso isto aconteça é devolvido o comando "L". -}

checkLight :: LightP -> String
checkLight (b, (x, y), (w, h), l) = if (elem (x, y) l)
                                    then if (isUpper ((b !! (h - y - 1)) !! x))
                                         then "L"
                                         else []
                                    else []	        


{-| 'rotation' recebe a orientação do robô e a orientação para onde o robô deve estar. Se as orientações coincidirem é devolvida uma lista vazia. Caso contrário, são calculados os comandos para chegar à rotação pretendida. -}       

rotation :: Orientation -> Orientation -> String
rotation o d | o == d    = []
             | otherwise = (rotate o d)


{-| 'rotate' faz com que o robô rode à esquerda e à direita x vezes até chegar à rotação pretendida. Depois disto, devolve o menor número de comandos (menor número de rotações). -}

rotate :: Orientation -> Orientation -> String
rotate o d = let left  = rotateLeft o d
                 right = rotateRight o d
             in if ((length left) < (length right))
                then left
                else right


{-| 'rotateLeft' faz com que o robô rode à esquerda até ele chegar à rotação pretendida. -}

rotateLeft :: Orientation -> Orientation -> String
rotateLeft o d | o == d    = []  
               | otherwise = "E" ++ (rotateLeft (left o) d)


{-| 'rotateRight' faz com que o robô rode à direita até ele chegar à rotação pretendida. -}

rotateRight :: Orientation -> Orientation -> String
rotateRight o d | o == d    = [] 
                | otherwise = "D" ++ (rotateRight (right o) d)


{-| 'left' faz o robô rodar à esquerda.

>>> O 
S
-}

left :: Orientation -> Orientation
left x = toEnum (mod ((fromEnum x) + 3) 4)


{-| 'right' faz o robô rodar à direita.

>>> O 
N
-}

right :: Orientation -> Orientation
right x = toEnum (mod ((fromEnum x) + 1) 4)


{-| 'updateMatrix' atualiza uma dada posição da matriz de soluções por um certo valor. -}

updateMatrix :: [[Char]] -> Pos -> Char -> [[Char]]
updateMatrix [] _ _                     = []
updateMatrix (h:t) (x, y) v | y == 0    = (updateRow h x v) : (updateMatrix t (x, y - 1) v)
                            | otherwise = h : (updateMatrix t (x, y - 1) v)


{-| 'updateRow' atualiza a posição de uma linha da matriz de soluções por um certo valor. -}

updateRow :: [Char] -> Int -> Char -> [Char]
updateRow [] _ _                = []
updateRow (h:t) x v | x == 0    = v : (updateRow t (x - 1) v)
                    | otherwise = h : (updateRow t (x - 1) v)  


{-| 'isValid' testa se a matriz de soluções tem uma solução. Se todos os seus valores forem '/N/' é sinal que o robô não se consguiu mover, não sendo esta a solução válida. -}

isValid :: [[Char]] -> Bool
isValid []                                   = False
isValid (h:t) | not (all (\x -> x == 'N') h) = True
              | otherwise                    = isValid t

{- Funções para a resolução do tabuleiro. Para o caso simples é usada uma matriz de de soluções. Para o caso complicado é usada adicionalmente uma matriz auxliar que contém os caminhos qua o robô já percorreu.

A matriz de soluções pode ter os seguintes valores possíveis:
	'N' -> posição desconhecida. Posição à qual o robô não acedeu ou não consegue aceder.
	'T' -> Terminal. Posição da luz onde se pretende chegar.
	'U' -> Up. Mostra que o robô desloca-se para norte.
	'D' -> Down. Mostra que o robô desloca-se para sul.
 	'L' -> Left. Mostra que o robô desloca-se para oeste.
	'R' -> Right. Mostra que o robô desloca-se para este.

A matriz auxiliar pode ter os seguintes valores possíveis:
	'N' -> posição desconhecida. O robô ainda não esteve nesta posição.
	'A' -> posição já visitada pelo robô.

-}

-- Funções de tabuleiros simples

{-| 'easyPath' resolve o movimento do robô até uma luz, em tabuleiros fáceis. Como nos tabuleiros fáceis a altura dos níveis difere no máximo em uma unidade, não é necessário preocupar-se com os casos de o robô ficar preso num certo local ou não poder avançar para um certo local. Basta apenas deslocar-se para a mesma linha e para a mesma coluna onde a luz se encontra. -}

easyPath :: PCondition -> [[Char]]
easyPath (b, (x, y), (xF, yF), (w, h), sol) =
       if ((x, y) == (xF, yF))
       then updateMatrix sol (x, h - y - 1) 'T'
       else if (y < yF)
            then easyPath (b, (x, y + 1), (xF, yF), (w, h), updateMatrix sol (x, h - 1 - y) 'U')
            else if (y > yF)
                 then easyPath (b, (x, y - 1), (xF, yF), (w, h), updateMatrix sol (x, h - 1 - y) 'D')
                 else if (x < xF)
                      then easyPath (b, (x + 1, y), (xF, yF), (w, h), updateMatrix sol (x, h - 1 - y) 'R')
                      else easyPath (b, (x - 1, y), (xF, yF), (w, h), updateMatrix sol (x, h - 1 - y) 'L')

-- Funções de tabuleiros complicados

{-| 'getFinalL' devolve a lista de luzes apagadas ordenada de acordo com a prioridade de cada luz. Ao fazer-se isto consegue-se resolver tabuleiros mais complicados em que seja necessário acender certas luzes antes das outras ou deixar certas luzes para último lugar. Para isto usou-se o algoritmo /quicksort/ para obter a lista de luzes que devem ser acesas primeiro e a lista de luzes que devem ser acesas em último lugar e ordenar cada uma delas. Testa-se se da cabeça da lista de luzes se pode ou não mover para cada uma das luzes da cauda da lista de luzes. Se não se conseguir mover, é sinal que essas luzes devem ser acesas primeiro. Caso se consiga acender, essas luzes devem ser deixadas para último lugar. -}

getFinalL :: Status -> [LightsOff]
getFinalL (_, _, _, [], _, _, _)        = []
getFinalL (b, c, s, (h:t), sol, p, tp)  = let lI = filter (\x -> (isValid (fst (complicatedPath (b, x, h, s, sol) p)))) t
                                              lF = filter (\x -> (not (isValid (fst (complicatedPath (b, x, h, s, sol) p))))) t
                                          in (getFinalL (b, c, s, lI, sol, p, tp)) ++ [h] ++ (getFinalL (b, c, s, lF, sol, p, tp))                                  

{-| 'complicatedPath' é a função que resolve os tabuleiros complicados. Esta função usa um algoritmo recursivo para encontrar a solução. Começa por testar se a posição onde se encontra é favorável. Se a posição for favorável, a função termina, devolvendo a solução. Caso contrário, testa se esta posição já foi visitada. Caso já tenha sido visitada é sinal que o robô estava a tentar mover-se em quadrado, não sendo esta a solução. Caso isto não aconteça, testa-se cada uma das direções, tendo a seguinte ordem: cima, direita, baixo, esquerda. O robô testa cada uma destas direções em sequência. Caso numa direção a solução não seja ótima o robô volta para trás e testa outra direção, marcando as posições onde esteve na lista auxiliar. Caso o robô chegue à posição desejada, a lista com a solução é atualizada com as direções que o robô percorreu, terminando a função. No pior caso possível, esta função percorre todo o tabuleiro. -}

complicatedPath :: PCondition -> [[Char]] -> ([[Char]], [[Char]])
complicatedPath (b, (x, y), pF, (w, h), sol) p =
       if ((x, y) == pF)
       then (updateMatrix sol (x, h - 1 - y) 'T', p)
       else if (((p !! (h - y - 1)) !! x) == 'A')
            then (sol, p)
            else let actual    = updateMatrix p (x, h - 1 - y) 'A'
                     (sUp, up) = cCondition (b, (x, y), pF, (w, h), sol) actual (y, (h - 1), 1, 0)
                 in if (isValid sUp)
                    then (updateMatrix sUp (x, h - 1 - y) 'U', up)
                    else let (sR, ri) = cCondition (b, (x, y), pF, (w, h), sol) up (x, (w - 1), 0, 1)
                         in if (isValid sR)
                            then (updateMatrix sR (x, h - y - 1) 'R', ri)
                            else let (sD, dw) = cCondition (b, (x, y), pF, (w, h), sol) ri (y, 0, -1, 0)
                                 in if (isValid sD)
                                    then (updateMatrix sD (x, h - y - 1) 'D', dw)
                                    else let (sL, le) = cCondition (b, (x, y), pF, (w, h), sol) dw (x, 0, 0, -1)
                                 in if (isValid sL)
                                    then (updateMatrix sL (x, h - y - 1) 'L', le)
                                    else (sol, le)                                    

{-| 'cCondition' é uma função auxiliar da função 'complicatedPath' que serve para a redução desta. A função recebe adicionalmente como parâmetros as coordendas x ou y e verifica se o robô pode ou não avançar para a posição seguinte conforme a sua direção. -}

cCondition :: PCondition -> [[Char]] -> PCompare -> ([[Char]], [[Char]])
cCondition (b, (x, y), pF, (w, h), sol) p (k, z, i, j) =
	if (k /= z && ((ord (toLower ((b !! (h - 1 - (y + i))) !! (x + j)))) - (ord (toLower ((b !! (h - 1 - y)) !! x)))) < 2)
       then complicatedPath (b, (x + j, y + i), pF, (w, h), sol) p
       else (sol, p) 

