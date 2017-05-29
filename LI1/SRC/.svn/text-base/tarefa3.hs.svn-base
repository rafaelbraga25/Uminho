{-|
Module          : Main
Description     :: Módulo Haskell com funções que calculam a posição final do /robot/ do jogo /Lightbot/, após a execução de todas as instruções. 
Copyright       : Carlos Pereira <carloscdap@gmail.com>
	   	  Rafael Braga <rafael.braga.gc@gmail.com>

Conjunto de funções que determinam a posição final do /robot/ após a execução dos comandos. Caso alguma lâmpada se acenda durante este processo, apresentam-se as coordenadas do /robot/ nesse momento. Começa-se por executar os comandos até ao fim ou  até todas as lâmpadas estarem acesas. Caso seja o segundo caso, é apresentado a mensagem /FIM/ e o número de comandos válidos até aquele momento. Caso se chegue ao fim das instruções e mesmo assim existem lâmpadas por acender, é apresentada a mensagem /INCOMPLETO/. Se chegarmos ao fim das instruções e todas as lâmpadas estiverem acesas, é apresentado a mensagem /FIM/ e o número de comandos válidos. -}

module Main where

import Data.Char

{- | /State/ é o tipo de variável que contém o estado do /robot/. -}

type State       = ([String], Coord, Char, Size)

{- | /TabInfo/ é o tipo de variável que contém as informações do tabuleiro. -}

type TabInfo     = ([String], Int, String, String, [LightsOff])

{- | /CommandInfo/ é o tipo de variável que contém as informações necessárias
     para executar um comando -}

type CommandInfo = ([String], String, Size, Coord, [LightsOff], Int)

{- | /Size/ é o tipo de variável das dimensões da matriz (altura e largura). -}

type Size        = (Int, Int)


{- | /Coord/ é o tipo de variável das coordenadas do /robot/. -}

type Coord       = (Int, Int, Char)


{- | /LightsOff/ é o tipo de variável das coordenadas das lâmpadas por acender. -}

type LightsOff = (Int, Int)


{- | 'main' Recebe o /std input/ de um ficheiro. Devolve a mensagem resultante da função /process/.

>>>"aaa\nbbb\nCcc\n0 0 N\nASDDSLDE"
"0 0\nFIM 4"

>>>aaa\nbbb\nCcc\n0 0 N\nASDDSDE"
"INCOMPLETO"
-}

main = do input <- getContents
	  putStrLn (process (lines (input)))


{- | 'process' faz o processamento do tabuleiro, das coordenadas iniciais do /robot/, das instruções, das lâmpadas por acender e das dimensões do tabuleiro. Depois invoca a função que executa os comandos. -}
process :: [String] -> String
process str = let (tab, height, coord, com, lg) = separateTab str 
	          co    = getCoords (words coord)
		  width = length (head tab)
	       in exCommands (tab, com, (width, height), co, lg, 0)


{- | 'exCommands' faz a execução dos comandos e apresenta (quando todas as lâmpadas estão acesas ou quando não existem mais instruções) a mensagem /FIM/ e número de comandos válidos ou /INCOMPLETO/. -}

exCommands :: CommandInfo -> String
exCommands (_, _, _, _, [], tK)         = "FIM" ++ " " ++ (show tK)
exCommands (_, [], _, _, _, _)          = "INCOMPLETO"
exCommands (tab, (h:t), s, (x, y, o), lg, tK) = 
	let ch = locate tab (x, y, o) (snd s)
	in if (not (isValidCommand (tab, (x, y, o), ch, s) h)) then exCommands (tab, t, s, (x, y, o), lg, tK)
	   else if (h /= 'L') then let (newTab, (x1, y1, o1)) = changePosition (x,y,o) h tab (snd s)
		              in exCommands (newTab, t, s, (x1, y1, o1), lg, (tK + 1))
	        else if (elem (x, y) lg) then ((show x) ++ " " ++ (show y) ++ ['\n']) ++ (exCommands (tab, t, s, (x, y, o), (rmL lg (x, y)), (tK + 1)))
		     else ((show x) ++ " " ++ (show y) ++ ['\n']) ++ (exCommands (tab, t, s, (x, y, o), (lg ++ (x, y) : []), (tK + 1)))
		   
					    
{- | 'separateTab' separa o /std input/, devolvendo um tuplo com as linhas do tabuleiro, o número de linhas do tabuleiro, a linha com as coordenadas iniciais, a linha com os comandos e a lista de coordenadas das lâmpadas.

>>> ["aaa", "Bbb", "ccC", "0 0 N", "ASDE"]
(["aaa", "bbb", "ccc"], 3, "0 0 N", "ASDE",[(2, 0), (0, 1)])
-}	

separateTab :: [String] -> TabInfo
separateTab [x]   = ([], 0, [], x, [])
separateTab (h:t) = 
	let (tb, height, cd, co, l) = separateTab t
        in if(not (isAlpha(head h))) then (tb, height, h ++ cd, co, l)
           else let lOff = map (\x -> (x, height)) (getLC h 0) 
		in ([h] ++ tb, 1 + height, cd, co, lOff ++ l)


{- | 'getLC' devolve, para uma linha, a lista das colunas em que existe uma lâmpada.

>>> "aAaaAB" 0
[1, 4, 5]
-}

getLC :: String -> Int -> [Int]
getLC [] _                = []
getLC (h:t) c | isUpper h = c : (getLC t (c + 1))
	      | otherwise = getLC t (c + 1)


{- | 'rmL' remove da lista de lâmpadas por acender, as coordenadas de uma lâmpada quando esta é acendida. 

>>> [(0, 1), (3, 4), (5, 6)] (3, 4)
[(0, 1), (5, 6)] 
-}
rmL :: [LightsOff] -> (Int, Int) -> [LightsOff]
rmL l c = filter (\x -> x /= c) l


{- | 'getCoords' calcula as coordenadas iniciais. Recebe uma linha com as coordenadas inicias e devolve um tuplo com dois inteiros e um caráter.

>>> ["0","0","N"]
(0, 0, 'N')
-}

getCoords :: [String] -> Coord
getCoords l = (read (l !! 0), read (l !! 1), head (l !! 2))


{- | 'locate' localiza um caráter no tabuleiro a partir das suas coordenadas, devolvendo-o no final.

>>> ["aaa", "bbb", "ccc"] (0, 0, N) 3
'c'
-}		
locate :: [String] -> Coord -> Int -> Char
locate tab (x, y, o) h = ((tab !! (h - 1 - y)) !! x)
		
				
{- | 'isValidCommand' chama a função necessária para verificar se o comando a excutar é válido na posição do /robot/.	

>>> ["aaa", "bbb", "ccc"] (0, 0, N) 'S' 'c' (3, 3)
True

>>> ["aaa", "bbb", "ccc"] (0, 0, N) 'A' 'c' (3, 3)
False
-}

isValidCommand :: State -> Char -> Bool
isValidCommand (tb, co, ch, s) cmm | cmm == 'A'  = walk (tb, co, (toLower ch), s)
		                   | cmm == 'S'  = jump (tb, co, (toLower ch), s)
		                   | cmm == 'L'  = (isUpper ch) 
			           | otherwise   = True


{- | 'walk' é chamada quando o comando a ser executado é A (Andar). Verifica se na posição actual a instrução é possível de executar. Devolve True caso seja possível. -}

walk :: State -> Bool
walk (tab, (x, y, o), ch, (w, h)) 
	| o == 'S' && (y == 0 || (y /= 0 && (toLower ((locate tab (x, y - 1, o) h)) /= ch)))             = False
	| o == 'N' && (y == (h - 1) || (y /= (h - 1) && (toLower ((locate tab (x, y + 1, o) h)) /= ch))) = False
	| o == 'E' && (x == (w - 1) || (x /= (w - 1) && (toLower((locate tab (x + 1, y, o) h)) /= ch)))  = False
	| o == 'O' && (x == 0 || (x /= 0 && (toLower ((locate tab (x - 1, y, o) h)) /= ch)))             = False
	| otherwise                                                                                      = True  


{- | 'jump' é chamada quando o comando a ser executado é S (Saltar). Verifica se na posição actual a instrução é possível de executar. Devolve True caso seja possível. -}

jump :: State -> Bool
jump (str, (x, y, o), ch, (w, h)) 
	| o == 'N' && y < (h - 1) && (ord (toLower (locate str (x, y + 1, o) h)) - (ord ch)) < 2 && (toLower (locate str (x, y + 1, o) h)) /= ch = True
	| o == 'S' && y > 0 && (ord (toLower (locate str (x, y - 1, o) h)) - (ord ch)) < 2 && (toLower (locate str (x, y - 1, o) h)) /= ch       = True
	| o == 'E' && x < (w - 1) && (ord (toLower (locate str (x + 1, y, o) h)) - (ord ch)) < 2 && (toLower (locate str (x + 1, y, o) h)) /= ch = True
	| o == 'O' && x > 0 && (ord (toLower (locate str (x - 1, y, o) h)) - (ord ch)) < 2 && (toLower (locate str (x - 1, y, o) h)) /= ch       = True
	| otherwise                                                                                                                              = False


{- | 'changePosition' é chamada quando a instrução é possível de executar. A partir do comando, poderá apresentar as coordenadas (quando não se alteram) ou chamar um função que as altere, apresentando-as depois.

>>> (0, 0, 'N') 'E'
(0, 0, 'O')

>>> (0, 0, 'N') 'S'
(0, 1, 'N')

>>> (0, 0, 'E') 'A'
(1, 0, 'E') 
-}

changePosition :: Coord -> Char -> [String] -> Int -> ([String], Coord)
changePosition (x, y, o) cmm tb h 
	| cmm == 'E' = (tb, (x, y, (left o)))
	| cmm == 'D' = (tb, (x, y, (right o))) 
	| otherwise  = let (x1, y1, o1) = moveRobot (x, y, o) 
		       in (tb, (x1, y1, o1))
		
		
{- | 'left' é invocada quando a instrução a executar é E (Esquerda - left), alterando a orientação do /robot/.-}	

left :: Char -> Char
left o | o == 'N'  = 'O'
       | o == 'O'  = 'S'
       | o == 'S'  = 'E'
       | otherwise = 'N'
       
       
{- | 'right' é invocada quando a instrução a executar é D (Direita - right), alterando a orientação do /robot/.-}    
       
right :: Char -> Char
right o | o == 'N'  = 'E'
        | o == 'O'  = 'N'
        | o == 'S'  = 'O'
        | otherwise = 'S'


{- | 'moveRobot' altera a coordenada x ou y, caso o comando S ou A sejam válidos. As novas coordenadas dependem da orientação do robot.

>>> (1, 0, 'O')
(0, 0, 'O')
-}

moveRobot :: Coord -> Coord
moveRobot (x, y, o) 
	| o == 'N'  = (x, y + 1, o)
	| o == 'E'  = (x + 1, y, o)
	| o == 'O'  = (x - 1, y, o)
	| otherwise = (x, y - 1, o)

