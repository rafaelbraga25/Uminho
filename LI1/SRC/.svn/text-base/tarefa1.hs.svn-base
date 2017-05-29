
{-|
Module      : Main
Description :: Módulo Haskell que contem funções para detetar erros de sintaxe
	      de um tabuleiro do jogo /LightBot/.
Copyright   : Carlos Pereira <carloscdap@gmail.com>
	      Rafael Braga   <rafael.braga.gc@gmail.com>

Contém funções que detetam se o tabuleiro contém erros de sintaxe 
(ex: uma linha em branco, tabuleiro com digitos, ...).
Caso ocorra algum erro de sintaxe é retornado o valor da linha onde
ocorre o primeiro erro. Caso contrário é devolvida a /String OK/.
-}

module Main where

import Data.Char

{-| 'main' recebe o /std input/ de um ficheiro. 
       
    Devolve a mensagem resultante da função /process/.

>>>"aaa\naaa\n0 0 S\nLASED"
OK

>>>"aaa\nbaa\n\n0 0 S\nLASED"
3
-}

main = do input <- getContents
	  putStrLn (process (lines input))

{-| 'process' executa todas as funções necessárias para a 
    validação do tabuleiro,
    da posição inicial do /robot/ e dos comandos que lhe serão aplicados.
    Executa cada uma delas sequencialmente, caso alguma falhe, a função
    /process/ termina devolvendo uma mensagem contento o número da linha do
    ficheiro onde ocorreu o erro.
-} 

process :: [String] -> String
process str = 
	let (width, height, tab, r) = getBoard str
	in if (width == [] || (head (width)) == 0) then "1"
           else let tabError = isValidBoard (head (width)) 1 width
		in if (tabError /= 0) then show tabError
	           else if (r == []) then show (height + 1)
			else if(not (isVSintax (head(r)) (head (width), height))) then show (height + 1)
			     else let rt = (tail r)
			          in if (rt == [] || (head (rt)) == "") then show (height + 2)
				     else if(not (iError (head rt))) then show (height + 2)
				          else if((tail rt) /= []) then show (height + 3)
					       else "OK"      

{-| 'getBoard' separa o tabuleiro das coordenas e dos comandos.
    Devolve também a largura de cada linha do tabuleiro,
    bem como a altura do tabuleiro.

>>>["aaa","ba","1 0 S","LASDE"]
([3, 2], 2, ["aaa", "ba"], ["1 0 S", "LASDE"]

-}

getBoard :: [String] -> ([Int], Int, [String], [String])
getBoard []    = ([], 0, [], [])  
getBoard (h:t) = let (width, height, tab, r) = getBoard t
		     w = isBoard h 0
		 in if (w /= 0) then ([w] ++ width, height + 1, [h] ++ tab, r)
	            else ([], 0, [], (h:t))  

{-| 'isBoard' testa se uma linha pertence ou não ao tabuleiro
    (se todos os seus caráteres são letras). 
    Caso algum caráter não seja uma letra é devolvido o valor 0.
    Caso contrario é devolvido o valor da largura dessa linha.

>>> "aaa"
3

>>> "aa2"
0   

-}

isBoard :: String -> Int -> Int
isBoard [] _                = 0
isBoard (h:t) c | isAlpha h = 1 + (isBoard t (c - 1))
	        | otherwise = c

{-| 'isValidBoard' testa se o tabulero é valido 
    (se todas as linhas têm a mesma largura).
    Caso todas as linhas tenham a mesma largura é devolvido o valor 0.
    Caso contrário é devolvido o número da linha onde a condição falhou.
    O primeiro argumento recebido corresponde à largura da primeira linha
    do tabuleiro.

>>> 3 1 [3, 3, 4]
3

>>> 3 1 [3, 3, 3]
0 

-}

isValidBoard :: Int -> Int -> [Int] -> Int
isValidBoard _ _ []                = 0
isValidBoard w c (h:t) | w == h    = isValidBoard w (c + 1) t
		       | otherwise = c

{-| 'isVSintax' testa se as coordenadas são válidas.
     Para isso é necessário: 

     1 - que a /String/ recebida contenha 2 espaços.

     2 - que o tamanho da /words (String recebida)/ seja 3.

     3 - que a primeira e a segunda posições da /words (String recebida)/
	 sejam inteiros sem o seguinte formato (ex: 00001) e que a terceira
	 posição seja um caráter N, S, E ou O.

     4 - que a primeira posição da /words (String recebida)/ seja menor que
	 a (largura do tabuleiro - 1) e que a segunda posição seja menor que
	 a (altura do tabuleiro - 1).

>>> "1 0 S" (2, 2)
True

>>> "0001 0 S" (2, 2)
False

>>> "0 1 S" (2, 1)
False

-}

isVSintax :: String -> (Int, Int) -> Bool
isVSintax s (w, h) = 
	let c = words s
	in if((length c < 3) || (countSpaces s /= 2)) then False
           else if((not (isVCoord (c !! 0) 0)) || (not (isVCoord (c !! 1) 0))) then False
		else let h1 = read (c !! 1) :: Int
	                 w1 = read (c !! 0) :: Int 
                         p  = (c !! 2)
		     in if((h1 >= h) || (w1 >= w) || ((length p) /= 1) || (not (elem (head p) "NEOS"))) then False
		        else True    

{-| 'countSpaces' conta o número de espaços de uma /String/. 

>>> "1 0 S"
2

-}

countSpaces :: String -> Int
countSpaces []                = 0
countSpaces (h:t) | isSpace h = 1 + countSpaces t
		  | otherwise = countSpaces t	

{-| 'isVCoord' testa se uma coordenada x ou y são válidas.
     Caso sejam inteiros e não estejam no seguinte formato (ex: 00001).

>>> "10"
True

>>> "0"
True

>>> "a"
False

>>> "01"
False 

-}

isVCoord :: String -> Int -> Bool
isVCoord [] _                                    = True
isVCoord (h:t) c | not (isDigit h)               = False
		 | h == '0' && c == 0 && t /= [] = False
	         | otherwise                     = isVCoord t (c + 1) 	

{-| 'iError' testa se os comandos se encontram na sintaxe válida, ou seja,
     se todos os caráteres da /String/ recebida têm os seguintes valores:
     L, A, S, D ou E.

>>> "LAS"
True

>>> "As"
False

-}

iError :: String -> Bool
iError = all (\x -> elem x "ASEDL")                    

