{-|
Module          : Main
Description     :: Módulo Haskell com funções que calculam a próxima posição do /robot/ do jogo /Lightbot/. 
Copyright       : Carlos Pereira <carloscdap@gmail.com>
	   	  Rafael Braga <rafael.braga.gc@gmail.com>

Conjunto de funções que determinam a próxima posição do /robot/ após a execução do primeiro comando. Começa-se por verificar se a instrução é possível de executar na posição actual. Se o comando for possível de executar, calcula-se a nova posição, apresentando-a no fim. Caso o comando não seja possível, é apresentada a mensagem /ERRO/. -}

module Main where

import Data.Char


{- | /Size/ é o tipo de variável das dimensões da matriz (altura e largura). -}

type Size  = (Int, Int)

{- | /Coord/ é o tipo de variável das coordenadas do /robot/. -}

type Coord = (Int, Int, Char)

{- | /State/ é o tipo de variável que contém o estado do /robot/. -}

type State = ([String], Coord, Char, Size)

{- | 'main' Recebe o /std input/ de um ficheiro. Devolve a mensagem resultante da função /process/.

>>>"aaa\nbbb\nccc\n0 0 N\nASDE"
ERRO

>>>aaa\nbbb\nccc\n0 0 N\nSEAL"
0 1 N
-}

main = do input <- getContents
	  putStrLn (process (lines (input)))
	  

{- | 'process' faz o processamento do tabuleiro e verifica se é possível executar o comando. Se for possível, apresenta as novas coordenadas. Caso contrário, apresenta a mensagem /ERRO/. -}
process :: [String] -> String
process str = let (tab, height, coord, commands) = separateTab str 
	          co    = getCoords (words coord)
		  com   = head (commands)
		  ch    = locate tab co height
		  width = length (head tab) 
	       in if (not (isValidCommand (tab, co, ch, (width, height)) com)) then "ERRO"
		  else changePosition co com

	  		        	  
{- | 'separateTab' separa o /std input/, devolvendo um tuplo com as linhas do tabuleiro, o número de linhas do tabuleiro, a linha com as coordenadas iniciais e a linha com os comandos.

>>> "aaa\nbbb\nccc\n0 0 N\nASDE"
(["aaa", "bbb", "ccc"], 3, "0 0 N", "ASDE")
-}
	  	  
separateTab :: [String] -> ([String], Int, String, String)
separateTab [x]   = ([], 0, [], x)
separateTab (h:t) = 
	let (tb, height, cd, co) = separateTab t
        in if(isAlpha(head h)) then ([h] ++ tb, 1 + height, cd, co)
           else (tb, height, h ++ cd, co)


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
	| o == 'E' && (x == (w - 1) || (x /= (w - 1) && (toLower ((locate tab (x + 1, y, o) h)) /= ch))) = False
	| o == 'O' && (x == 0 || (x /= 0 && (toLower ((locate tab (x - 1, y, o) h)) /= ch)))             = False
	| otherwise                                                                                      = True  
	

{- | 'jump' é chamada quando o comando a ser executado é S (Saltar). Verifica se na posição actual a instrução é possível de executar. Devolve True caso seja possível. -}

jump :: State -> Bool
jump (str, (x, y, o), ch, (w, h)) 
	| o == 'N' && y < (h - 1) && (ord (toLower (locate str (x, y + 1, o) h)) - (ord ch)) < 2 && (toLower (locate str (x, y + 1, o) h)) /= ch = True
	| o == 'S' && y > 0 && (ord (toLower (locate str (x, y - 1, o) h)) - (ord ch)) < 2 && (toLower (locate str (x, y - 1, o) h)) /= ch       = True
	| o == 'E' && x < (w - 1) && (ord (toLower (locate str (x + 1, y, o) h)) - (ord ch)) < 2 && (toLower (locate str (x + 1, y, o) h)) /= ch = True
	| o == 'O' && x > 0 && (ord (toLower (locate str (x - 1, y, o) h)) - (ord ch)) < 2 && (toLower (locate str (x - 1, y, o) h)) /= ch       = True
	|otherwise                                                                                                                               = False


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
        
        
{- | 'changePosition' é chamada quando a instrução é possível de executar. A partir do comando, poderá apresentar as coordenadas (quando não se alteram) ou chamar um função que as altere, apresentando-as depois.

>>> (0, 0, 'N') 'E'
(0, 0, 'O')

>>> (0, 0, 'N') 'S'
(0, 1, 'N')

>>> (0, 0, 'E') 'A'
(1, 0, 'E') 
-}

changePosition :: Coord -> Char -> String
changePosition (x, y, o) cmm 
	| cmm == 'E' = (show x) ++ " " ++ (show y) ++ " " ++ [left o]
	| cmm == 'D' = (show x) ++ " " ++ (show y) ++ " " ++ [right o] 
	| cmm == 'L' = (show x) ++ " " ++ (show y) ++ " " ++ [o]
	| otherwise  = let (x1, y1, o1) = moveRobot (x, y, o) 
		       in (show x1) ++ " " ++ (show y1) ++ " " ++ [o1]

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

