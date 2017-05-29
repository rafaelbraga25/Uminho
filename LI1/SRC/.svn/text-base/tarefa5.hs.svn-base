{-|
Module          : Main
Description     :: Módulo /Haskell/ com funções que imprimem o código /HTML/ para representar o tabuleiro e o robô a executar as instruções fornecidas.
Copyright       : Carlos Pereira <carloscdap@gmail.com>
	   	    Rafael Braga <rafael.braga.gc@gmail.com>

Conjunto de funções que calculam duas componentes do jogo: as posições de todos os blocos constituintes do tabuleiro e todas as posições que o robô ocupa enquanto executa as instruções. Tendo ambas as componentes, as funções deste módulo imprimem o código de uma página /HTML/, onde aparece o tabuleiro (blocos normais e lâmpadas) e o robô a movimentar-se segundo as instruções (andar, saltar, rodar para a esquerda ou para a direita e acender uma lâmpada). 
-}


module Main where

import Data.Char


{-| /LightsOff/ - coordenadas (x, y) de uma luz. -}

type LightsOff = (Int, Int)


{- | /Board/ - caráteres que compõem o tabuleiro.-}

type Board     = [String]


{-| /Size/ - largura e altura do tabuleiro. -}

type Size      = (Int, Int)


{- | /BoardInfo/ - informações do tabuleiro: /Board/, altura do tabuleiro, /string/ com as coordenadas e orientação iniciais do robô, /string/ com as instruções para o robô executar e lista com as coordenadas das lâmpadas por acender (/[LightsOff]/). -}

type BoardInfo = (Board, Int, String, String, [LightsOff])


{- | /Coord/ - coordenadas do robô (segundo x e segundo y) e orientação. -}

type Coord     = (Int, Int, Orientation)


{- |  /Position/ - posição do robô com coordenadas x, y e orientação, antes da transformação para /HTML/.-}

type Position  = (Int, Int, Float, Command)


{- |  /PositionP/ - parâmetros que influênciam o cálculo da próxima posição do robô: tabuleiro, coordenadas, linha de instruções, tamanho do tabuleiro e lista com as coordenadas das lâmpadas-}

type PositionP = (Board, Coord, String, Size, [LightsOff])


{- |  /Bot/ - posição do robô (coordenadas, orientação em radianos e comando a executar) após a transformação para o código /HTML/. -}

type Bot       = (Float, Float, Float, Float, Command) 


{- |  /Legs/ - código /HTML/ que faz com que as pernas do robô se movimentem.-}

type Legs      = (String, String)


{-| /Orientation/ - orientações possíveis do robô. -}

data Orientation = N | E | S | O
       deriving (Enum, Eq)

{- | /Command/ - comandos que o robô pode executar. -}

data Command = W | J | JU | JD | LON | LOFF | IL | R | L | NOT
       deriving (Eq)

-- Funções principais

{- | 'main' recebe o /std input/ de um ficheiro. Devolve uma /string/ resultante da função /process/. Esta /string/ devolvida é o código /HTML/ que constrói o tabuleiro e os movimentos do robô. -}

main = do s <- getContents
	  putStrLn (process (lines s))

{- | 'process' faz o processamento do tabuleiro, das coordenadas iniciais do robô, das instruções, das lâmpadas por acender e das dimensões do tabuleiro. Depois, faz os calculos necessários para determinar todas as posições que o robô percorre ao executar os comandos. No fim, imprime o código /HTML/ que gera o tabuleiro e o robô. -}

process :: [String] -> String
process s = let (board, hght, c, com, lights) = separateBoard s
                (x, y, o)                     = getCoord (words (c)) 0
                width                         = length (head board)
                i                             = 0.25 * (fromIntegral width)
                j                             = 0.25 * (fromIntegral hght)
                positions                     = [(x, y, convert (locate board (x, y) hght), NOT)] ++ getP (board, (x, y, o), com, (width, hght), lights)
                lgt                           = length positions
                cycle                         = if (lgt == 1) 
                                                then 1
                                                else (1 /(fromIntegral (lgt - 1)))
                timeInterval                  = if(cycle == 1 && lgt == 1) 
                                                then "1"
                                                else htmlKey 0 cycle (lgt - 1)
                botPos                        = convertL positions (getRadians o) (i, j) hght
                htmlL                         = convertLights lights (i, j) hght
                botWalk                       = if (com /= "")
                                                then if (head com == 'A' && (not (null lights)))
                                                     then ("1 0 0 -0.35  1 0 0 0.35", "1 0 0 0.35  1 0 0 -0.35") : convert2Walk (tail botPos)
                                                     else convert2Walk botPos
                                                else convert2Walk (botPos)
                lgtLEGS                       = lgt * 2
                cycleLEGS                     = (1/(fromIntegral (lgtLEGS - 1)))
                legsInterval                  = htmlKey 0 (cycleLEGS) (lgtLEGS - 1) 
            in htmlHead ++
               htmlBodyShapes ++ 
               (htmlBoard board 0 i j) ++ 
               htmlBot ++
               "\t\t\t\t<timeSensor def=\"clock\" cycleInterval=\"" ++ show (0.75 * (fromIntegral lgt)) ++ "\" loop=\"true\"></timeSensor>\n" ++
               "\t\t\t\t<positionInterpolator def=\"moveRobot\" key=\"" ++ timeInterval ++ 
               "\" keyValue=\"" ++ (htmlAnimatronics botPos) ++ "\">" ++ 
               "</positionInterpolator>\n" ++
               htmlRoutePosition ++ "\n\n\n" ++
               
               "\t\t\t\t<orientationInterpolator def=\"rotate\" key=\"" ++ timeInterval ++ 
               "\" keyValue=\"" ++ (htmlRotation botPos) ++ "\">" ++ 
               "</orientationInterpolator>\n" ++
               htmlRouteOrientation ++ "\n\n\n" ++
               
               "\t\t\t\t<orientationInterpolator def=\"rotateLeftLeg\" key=\"" ++ legsInterval ++ 
               "\" keyValue=\"" ++ (htmlRotationLegs 'l' botWalk) ++ "\">" ++ 
               "</orientationInterpolator>\n" ++
               (htmlRouteOrientationLegs "rotateLeftLeg" "leftLeg") ++ "\n\n\n" ++
               
               "\t\t\t\t<orientationInterpolator def=\"rotateRightLeg\" key=\"" ++ legsInterval ++ 
               "\" keyValue=\"" ++ (htmlRotationLegs 'r' botWalk) ++ "\">" ++ 
               "</orientationInterpolator>\n" ++
               (htmlRouteOrientationLegs "rotateRightLeg" "rightLeg") ++ "\n\n\n" ++
               
               "\t\t\t\t<colorInterpolator def=\"colorA\" key=\"" ++ timeInterval ++ 
               "\" keyValue=\"" ++ (htmlColor botPos) ++ "\">" ++ 
               "</colorInterpolator>\n" ++
               "\t\t\t\t<route fromNode=\"clock\" toNode=\"colorA\"" ++
               " fromField=\"fraction_changed\" toField=\"set_fraction\"></route>\n" ++
               "\t\t\t\t<route fromNode=\"colorA\" toNode=\"antennaColor\"" ++
               " fromField=\"value_changed\" toField=\"diffuseColor\"></route>\n" ++
               (htmlLightsK htmlL botPos timeInterval) ++
               htmlEnding

{- | 'separateBoard' separa o conteúdo recebido, devolvendo as informações do tabuleiro.

>>> ["aaa", "Bbb", "ccC", "0 0 N", "ASDE"]
(["aaa", "bbb", "ccc"], 3, "0 0 N", "ASDE",[(2, 0), (0, 1)])

-}

separateBoard :: Board -> BoardInfo
separateBoard [x]   = if (isAlpha (head x))
                      then ([], 0, [], x, [])
                      else ([], 0, x, [], [])
separateBoard (h:t) = 
	let (tb, height, cd, co, l) = separateBoard t
       in if(not (isAlpha(head h))) then (tb, height, h ++ cd, co, l)
          else let lOff = map (\x -> (x, height)) (getLC h 0) 
		 in ([h] ++ tb, 1 + height, cd, co, lOff ++ l)

{-| 'getLC' devolve as coordendas em x, das luzes presentes numa dada linha do tabuleiro.

>>> "aaAaB" 
[2, 4]
-}

getLC :: String -> Int -> [Int]
getLC [] _                = []
getLC (h:t) c | isUpper h = c : (getLC t (c + 1))
	      | otherwise = getLC t (c + 1)


{- | 'getCoord' devolve as coordenadas iniciais do robô em formato /(Int, Int)/ e a orientação em formato /Orientation/.-}

getCoord :: [String] -> Int -> (Int, Int, Orientation)
getCoord [o] _   = (0, 0, toOrientation (head o))
getCoord (h:t) c = let (x, y, o) = getCoord t (c + 1)
		     in case c of 
                            0 -> ((read(h) :: Int) + x, y, o)
                            1 -> (x, (read(h) :: Int) + y, o)

{- | 'toOrientation' devolve a orientação do robô em formato /Orientation/.-}

toOrientation :: Char -> Orientation
toOrientation 'N' = N
toOrientation 'E' = E
toOrientation 'S' = S
toOrientation 'O' = O


-- Funções de cálculo de posições

{- | 'height' devolve a altura de um bloco (ou lâmpada) no formato para o código /HTML/. -}

height :: Int -> Float
height h = (0.75 * (fromIntegral h)) - 0.5 * (fromIntegral (h - 1))


{- | 'convert' faz a transformação da altura do robô para o formato a ser impresso no código /HTML/.-}

convert :: Char -> Float
convert ch = height ((ord (toLower ch)) - (ord 'a'))


{- | 'getP' calcula todas as posições por onde o robô passa, a partir da sua posição inicial e das instruções.-}

getP :: PositionP -> [Position]
getP (_, _, _, _, [])                   = []
getP (_, _, [], _, _)                   = []
getP (b, (x, y, o), (h:t), (w, hgt), l) = 
       case h of
           'D' -> (x, y, convert ((b !! (hgt - 1 - y)) !! x), R) : (getP (b, (x, y, right o), t, (w, hgt), l))
           'E' -> (x, y, convert ((b !! (hgt - 1 - y)) !! x), L) : (getP (b, (x, y, left o), t, (w, hgt), l))
           'L' -> let (lC, lF) = getLightC (x, y) (w, hgt) l b 
                  in (x, y, convert ((b !! (hgt - 1 - y)) !! x), lC) : (getP (b, (x, y, o), t, (w, hgt), lF))
           _   -> let cmdL     = getWJC b (x, y, o) (w, hgt) h
                      (xF, yF) = getXY (last cmdL)
                  in cmdL ++ (getP (b, (xF, yF, o), t, (w, hgt), l))       


{- | 'getLightC' verifica, para a posição onde o robô se encontra e para o comando /L/ fornecido, se ele acende uma lâmpada, apaga uma lâmpada ou não é possível apagar ou acender uma lâmpada. 

>>> (1, 1) (3, 3) [(0, 0), (1,1)] ["aaa", "aAa", "Aaa"]
LON

>>> (1, 1) (3, 3) [(0, 0)] ["aaa", "aaa", "Aaa"]
IL

-}

getLightC :: (Int, Int) -> Size -> [LightsOff] -> Board -> (Command, [LightsOff])
getLightC (x, y) (w, h) l b | isLower ((b !! (h - 1- y)) !! x) = (IL, l)
                            | elem (x, y) l                    = (LON, rmL l (x, y))
                            | otherwise                        = (LOFF, l ++ [(x, y)]) 

{- | 'getWJC' devolve, para as instruções andar (A) e saltar (S), as coordenadas que o robô percorre.

>>> ["aaa", "bAa", "Aaa"] (0, 0, N) (3, 3) 'A'
[(0, 0, 0.25, W)]

>>> ["aaa", "bAa", "Aaa"] (0, 0, N) (3, 3) 'S'
[(0, 0, 0.5, JU), (0, 1, 0.5, JU)]
-}
 
getWJC :: Board -> Coord -> Size -> Char -> [Position]
getWJC b (x, y, o) s cmd = let (i, j) = getNextP o
                           in if (isInvalid (x + i, y + j) s)
                              then if (cmd == 'A')
                                   then [(x, y, convert (locate b (x, y) (snd s)), W)] 
                                   else [(x, y, (convert (locate b (x, y) (snd s))) + 0.25, J), (x, y, (convert (locate b (x, y) (snd s))), J)]
                              else case cmd of
                                       'A' -> getWC b (x, y) (i, j) s  
                                       'S' -> getJC b (x, y) (i, j) s


{- | 'getNextP' devolve, a partir da orientação do robô, o que se deve somar às coordenadas x e y quando a instrução é andar ou saltar. Isto para que calcule a posição seguinte.-}

getNextP :: Orientation -> (Int, Int)
getNextP N = (0, 1)
getNextP E = (1, 0)
getNextP S = (0, -1)
getNextP O = (-1, 0)


{- | 'isInvalid' verifica se nas coordenadas atuais do robô é possível executar as instruções andar e saltar.-}

isInvalid :: (Int, Int) -> Size -> Bool
isInvalid (x, y) (w, h) = (x < 0 || x >= w) || (y < 0 || y >= h)


{- | 'getWC' devolve a lista com as posições que o robô percorre quando ele anda.

>>> ["aaa", "aAa", "aaa"] (0, 0) (0 , 1) (3, 3)
[(0, 1, 0.25, W)]

>>> ["aaa", "bAa", "baa"] (0, 1) (0 , -1) (3, 3)
[(0, 0, 0.5, W)]
-}

getWC :: Board -> (Int, Int) -> (Int, Int) -> Size -> [Position]
getWC b (x, y) (i, j) (w, h) 
       | (ord (toLower ((locate b (x + i, y + j) h)))) /= (ord (toLower (locate b (x, y) h))) = [(x, y, convert (locate b (x, y) h), W)]
       | otherwise                                                                            = [(x + i, y + j, convert (locate b (x + i, y + j) h), W)]


{- | 'getJC' devolve a lista com as posições que o robô percorre quando ele salta.

>>> ["aaa", "aAa", "baa"] (0, 0) (0 , 1) (3, 3)
[(0, 1, 0.5, JD), (0, 1, 0.25, JD)]

>>> ["aaa", "bAa", "baa"] (0, 0) (0, 1) (3, 3)
[(0, 0, 0.75, J), (0, 0, 0.5, J)]
-}

getJC :: Board -> (Int, Int) -> (Int, Int) -> Size -> [Position]
getJC b (x, y) (i, j) (w, h) 
       | (ord (toLower (locate b (x + i, y + j) h))) == (ord (toLower (locate b (x, y) h)))    = [(x, y, (convert (locate b (x, y) h)) + 0.25, J), (x, y, (convert (locate b (x, y) h)), J)]
       | (ord (toLower (locate b (x + i, y + j) h))) - (ord (toLower (locate b (x, y) h))) > 1 = [(x, y, (convert (locate b (x, y) h)) + 0.25, J), (x, y, (convert (locate b (x, y) h)), J)]
       | (ord (toLower (locate b (x + i, y + j) h))) - (ord (toLower (locate b (x, y) h))) < 0 = [(x + i, y + j, convert (locate b (x, y) h), JD), (x + i, y + j, convert (locate b (x + i, y + j) h), JD)]
       | otherwise                                                                             = [(x, y, (convert (locate b (x, y) h)) + 0.25, JU), (x + i, y + j, convert (locate b (x + i, y + j) h), JU)]


{- | 'getXY' separa as coordenadas x e y da orientação e do comando a executar pelo robô.-}

getXY :: Position -> (Int, Int)
getXY (x, y, _, _) = (x, y)


{- | 'locate' localiza no tabuleiro, o caráter cuja posição corresponde à do robô.

>>>["abc"] (1, 0) 1
'b'
-}

locate :: Board -> (Int, Int) -> Int -> Char
locate b (x, y) h = ((b !! (h - 1 - y)) !! x)


{- | 'rmL' remove da lista com as coordenadas de todas as lâmpadas, as coordenadas fornecidas.

>>> [(0, 0), (1, 1), (2, 3)] (1, 1)
[(0, 0), (2, 3)}
 -}
 
rmL :: [LightsOff] -> (Int, Int) -> [LightsOff]
rmL l c = filter (\x -> x /= c) l


{- | 'left' é invocada quando a instrução a executar é E (Esquerda - left), alterando a orientação do /robot/.-}

left :: Orientation -> Orientation
left x = toEnum (mod ((fromEnum x) + 3) 4)


{- | 'right' é invocada quando a instrução a executar é D (Direita - right), alterando a orientação do /robot/.-}

right :: Orientation -> Orientation
right x = toEnum (mod ((fromEnum x) + 1) 4)


{- | 'getRadians' devolve a orientação do robô em radianos.-}

getRadians :: Orientation -> Float
getRadians N = 0
getRadians E = 1.5 * pi
getRadians S = pi
getRadians O = 0.5 * pi


{- | 'convertL' faz a conversão da lista com as posições do robô para uma lista com as posições prontas a serem impressas num código /HTML/.-}

convertL :: [Position] -> Float -> (Float, Float) -> Int -> [Bot]
convertL [] _ _ _                    = []
convertL ((x, z, y, c):t) r (i, j) h = let (xF, yF, zF) = ((fromIntegral x) * 0.525 - i, y, (fromIntegral (h - 1 - z)) * 0.525 - j)   
                                       in case c of
                                              R -> (xF, yF, zF, r - (0.5 * pi), c) : (convertL t (r - (0.5 * pi)) (i, j) h)
                                              L -> (xF, yF, zF, r + (0.5 * pi), c) : (convertL t (r + (0.5 * pi)) (i, j) h)
                                              _ -> (xF, yF, zF, r, c) : (convertL t r (i, j) h) 


{- | 'convertLights' faz a conversão da lista com as coordenadas inteiras das lâmpadas para uma lista com as coordenadas prontas a serem impressas num código /HTML/.-}

convertLights :: [LightsOff] -> (Float, Float) -> Int -> [(Float, Float)]
convertLights [] _ _              = []
convertLights ((x, y):t) (i, j) h = ((fromIntegral x) * 0.525 - i, (fromIntegral (h - 1 - y)) * 0.525 - j) : (convertLights t (i, j) h)


-- Funções de código html

{- | 'htmlHead' devolve o cabeçalho necessário para o código /HTML/.-}

htmlHead :: String
htmlHead = "<html>\n\t<head>\n" ++ 
           "\t\t<title>Lightbot</title>\n" ++ 
           "\t\t<script type=\"text/javascript\" src=\"http://www.x3dom.org/x3dom/release/x3dom.js\"> </script>\n" ++ 
           "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"http://x3dom.org/x3dom/release/x3dom.css\"></link>\n" ++ 
           "\t</head>\n"


{- | 'htmlBodyShapes' devolve o código /HTML/ que centra a janela com o tabuleiro e que contém as informações (dimensões e cores) dos blocos (que não são lâmpadas) do tabuleiro. -}

htmlBodyShapes :: String
htmlBodyShapes = "\t<style>\n" ++
                 "\t\tbody {\n" ++
                 "\t\t\tbackground-color: #878686;\n" ++
                 "\t\t}\n" ++
                 "\t\tx3d {\n" ++
                 --"\t\t\tmargin-top: 100px;\n" ++
                 "\t\t\theight: 90%;\n" ++
                 "\t\t\twidth: 100%;\n" ++
                 "\t\t\tborder: 0px solid #878686;\n" ++
                 "\t\t}\n" ++
                 "\t\tcenter {\n" ++
                 "\t\t\theight: 10%;\n" ++
                 "\t\t\tfont-size: 50px;\n" ++
                 "\t\t\tcolor: #FFFFFF;\n" ++
                 "\t\t\tfont-weight: bold;\n" ++
                 "\t\t\tfont-family: Courier;\n" ++
                 "\t\t}\n" ++             
	          "\t</style>\n" ++
                 "\t<body>\n\t\t<center> Lightbot </center>\n" ++ 
                 "\t\t<x3d>\n" ++ 
                 "\t\t\t<scene>\n" ++ 
                 "\t\t\t\t<group render=\"false\">\n" ++ 
                 "\t\t\t\t\t<shape def=\"block\">\n" ++ 
                 "\t\t\t\t\t\t<appearance>\n" ++ 
                 "\t\t\t\t\t\t\t<material diffuseColor=\"0.4 0.7 1\"></material>\n" ++ 
                 "\t\t\t\t\t\t</appearance>\n" ++ 
                 "\t\t\t\t\t\t<box size=\"0.5 0.225 0.5\"></box>\n" ++ 
                 "\t\t\t\t\t</shape>\n" ++ 
                 "\t\t\t\t</group>\n"


{- | 'htmlBoard' devolve o código /HTML/ que contrói as linhas do tabuleiro.-}

htmlBoard :: Board -> Float -> Float -> Float -> String
htmlBoard [] _ _ _    = []
htmlBoard (h:t) l x y = (htmlLines h l 0 x y) ++ (htmlBoard t (l + 0.525) x y)


{- | 'htmlLines' devolve o código /HTML/ que constrói as colunas do tabuleiro. Invoca a função /htmlLights/ quando o caráter que está a ler é uma maiúscula (lâmpada). Invoca a função /htmlBlocks/ quando o caráter que está a ler é uma minúscula (bloco normal).-}

htmlLines :: String -> Float -> Float -> Float -> Float -> String
htmlLines [] _ _ _ _                = []
htmlLines (h:t) l c x y | isUpper h = (htmlLights l c (ord (toLower h) - ord 'a') x y) ++ (htmlLines t l (c + 0.525) x y)
		          | otherwise = (htmlBlocks l c (ord h - ord 'a') x y) ++ (htmlLines t l (c + 0.525) x y)


{- | 'htmlBlocks' devolve o código /HTML/ que constrói os blocos normais do tabuleiro.-}

htmlBlocks :: Float -> Float -> Int -> Float -> Float -> String
htmlBlocks l c 0 x y = "\t\t\t\t<transform translation=\"" ++ 
                         (show (c - x)) ++ " " ++ 
                         (show 0.5) ++ " " ++ 
                         (show (l - y)) ++  
                         "\"> \n\t\t\t\t\t<shape use=\"block\"></shape>\n" ++ 
                         "\t\t\t\t</transform>\n "
htmlBlocks l c h x y = "\t\t\t\t<transform translation=\"" ++ 
                         (show (c - x)) ++ " " ++ 
                         (show (height h)) ++ " " ++ 
                         (show (l - y))  ++ "\">\n" ++ 
                         "\t\t\t\t\t<shape use=\"block\"></shape> \n" ++ 
                         "\t\t\t\t</transform>\n" ++ 
                         (htmlBlocks l c (h - 1) x y)


{- | 'htmlLights' devolve o código /HTML/ que constrói as lâmpadas do tabuleiro.-}

htmlLights :: Float -> Float -> Int -> Float -> Float -> String
htmlLights l c 0 x y = "\t\t\t\t<transform translation=\"" ++ 
                   (show (c - x)) ++ " " ++ 
                   (show 0.5) ++ " " ++ 
                   (show (l -y)) ++ "\"> \n" ++ 
                   "\t\t\t\t\t<shape>\n" ++
                   "\t\t\t\t\t\t<appearance>\n" ++
                   "\t\t\t\t\t\t\t<material def=\"" ++ (show (auxRound (c - x))) ++ "_" ++ (show (auxRound (l - y))) ++ 
                   "\" diffuseColor=\"0.6 0.86 0.97\"></material>\n" ++
                   "\t\t\t\t\t\t</appearance>\n" ++
                   "\t\t\t\t\t\t<box size=\"0.5 0.225 0.5\"></box>\n" ++
                   "\t\t\t\t\t</shape>\n" ++
                   "\t\t\t\t</transform>\n"
                       
htmlLights l c h x y = "\t\t\t\t<transform translation=\"" ++ 
                   (show (c - x)) ++ " " ++ 
                   (show (height h)) ++ " " ++ 
                   (show (l - y)) ++ "\"> \n" ++ 
                   "\t\t\t\t\t<shape>\n" ++
                   "\t\t\t\t\t\t<appearance>\n" ++
                   "\t\t\t\t\t\t\t<material def=\"" ++ (show (auxRound (c - x))) ++ "_" ++ (show (auxRound (l - y))) ++ 
                   "\" diffuseColor=\"0.6 0.86 0.97\"></material>\n" ++
                   "\t\t\t\t\t\t</appearance>\n" ++
                   "\t\t\t\t\t\t<box size=\"0.5 0.225 0.5\"></box>\n" ++
                   "\t\t\t\t\t</shape>\n" ++
                   "\t\t\t\t</transform>\n" ++
                   (htmlBlocks l c (h - 1) x y) 


{- | 'auxRound' arredonda um número à milésima.-}

auxRound :: Float -> Float
auxRound n = (fromIntegral (round (n * 1000))) / 1000


{- | 'htmlBot' contrói o código /HTML/ que constitui o robô.-}

htmlBot :: String
htmlBot = 
         "\t\t\t\t<transform def=\"bot\">\n" ++
         "\t\t\t\t\t<transform translation=\"0 0.735 0\" def=\"head\">\n" ++
         "\t\t\t\t\t\t<shape>\n" ++
         "\t\t\t\t\t\t\t<appearance>\n" ++
         "\t\t\t\t\t\t\t\t<material diffuseColor=\".5714 .5714 .5714\"></material>\n" ++
         "\t\t\t\t\t\t\t</appearance>\n" ++
         "\t\t\t\t\t\t\t<sphere radius=\".14\"></sphere>\n" ++
         "\t\t\t\t\t\t</shape>\n" ++
         "\t\t\t\t\t</transform>\n" ++
       
         "\t\t\t\t\t<transform translation=\"0 0.9 0\" def=\"antenna\">\n" ++
         "\t\t\t\t\t\t<shape>\n" ++
         "\t\t\t\t\t\t\t<appearance>\n" ++
         "\t\t\t\t\t\t\t\t<material diffuseColor=\"0 0 0\"></material>\n" ++
         "\t\t\t\t\t\t\t</appearance>\n" ++
         "\t\t\t\t\t\t\t<box size=\".01 .15 .01\"></box>\n" ++
         "\t\t\t\t\t\t</shape>\n" ++
         "\t\t\t\t\t</transform>\n" ++
       
         "\t\t\t\t\t<transform translation=\"0 1 0\" def=\"antennaLight\">\n" ++
         "\t\t\t\t\t\t<shape>\n" ++
         "\t\t\t\t\t\t\t<appearance>\n" ++
         "\t\t\t\t\t\t\t\t<material def=\"antennaColor\" diffuseColor=\"0.6 0.86 0.97\"></material>\n" ++
         "\t\t\t\t\t\t\t</appearance>\n" ++
         "\t\t\t\t\t\t\t<sphere radius=\".04\"></sphere>\n" ++
         "\t\t\t\t\t\t</shape>\n" ++
         "\t\t\t\t\t</transform>\n" ++
       
         "\t\t\t\t\t<transform translation=\"0.05 0.75 -0.12\" def=\"rightEye\">\n" ++
         "\t\t\t\t\t\t<shape>\n" ++
         "\t\t\t\t\t\t\t<appearance>\n" ++
         "\t\t\t\t\t\t\t\t<material diffuseColor=\"1 1 1\"></material>\n" ++
         "\t\t\t\t\t\t\t</appearance>\n" ++
         "\t\t\t\t\t\t\t<sphere radius=\".045\"></sphere>\n" ++
         "\t\t\t\t\t\t</shape>\n" ++
         "\t\t\t\t\t</transform>\n" ++
         
         "\t\t\t\t\t<transform translation=\"-0.05 0.75 -0.12\" def=\"leftEye\">\n" ++
         "\t\t\t\t\t\t<shape>\n" ++
         "\t\t\t\t\t\t\t<appearance>\n" ++
         "\t\t\t\t\t\t\t\t<material diffuseColor=\"1 1 1\"></material>\n" ++
         "\t\t\t\t\t\t\t</appearance>\n" ++
         "\t\t\t\t\t\t\t<sphere radius=\".045\"></sphere>\n" ++
         "\t\t\t\t\t\t</shape>\n" ++
         "\t\t\t\t\t</transform>\n" ++
       
         "\t\t\t\t\t<transform translation=\"0 0.535 0\" def=\"body\">\n" ++
         "\t\t\t\t\t\t<shape>\n" ++
         "\t\t\t\t\t\t\t<appearance>\n" ++
         "\t\t\t\t\t\t\t\t<material diffuseColor=\".5714 .5714 .5714\"></material>\n" ++
         "\t\t\t\t\t\t\t</appearance>\n" ++
         "\t\t\t\t\t\t\t<cylinder radius=\".1\" height=\".3\"></cylinder>\n" ++
         "\t\t\t\t\t\t</shape>\n" ++	
         "\t\t\t\t\t</transform>\n" ++
       
         "\t\t\t\t\t<transform translation=\"0.05 0.34 0\" def=\"rightLeg\">\n" ++
         "\t\t\t\t\t\t<shape>\n" ++
         "\t\t\t\t\t\t\t<appearance>\n" ++
         "\t\t\t\t\t\t\t\t<material diffuseColor=\".5714 .5714 .5714\"></material>\n" ++
         "\t\t\t\t\t\t\t</appearance>\n" ++
         "\t\t\t\t\t\t\t<box size=\".05 .4 .05\"></box>\n" ++  
         "\t\t\t\t\t\t</shape>\n" ++
         "\t\t\t\t\t</transform>\n" ++
       
         "\t\t\t\t\t<transform translation=\"-0.05 0.34 0\" def=\"leftLeg\">\n" ++
         "\t\t\t\t\t\t<shape>\n" ++
         "\t\t\t\t\t\t\t<appearance>\n" ++
         "\t\t\t\t\t\t\t\t<material diffuseColor=\".5714 .5714 .5714\"></material>\n" ++
         "\t\t\t\t\t\t\t</appearance>\n" ++
         "\t\t\t\t\t\t\t<box size=\".05 .4 .05\"></box>\n" ++  
         "\t\t\t\t\t\t</shape>\n" ++  
         "\t\t\t\t\t</transform>\n" ++
       
         "\t\t\t\t\t<transform translation=\"-0.11 0.485 0\" def=\"leftArm\">\n" ++
         "\t\t\t\t\t\t<shape>\n" ++
         "\t\t\t\t\t\t\t<appearance>\n" ++
         "\t\t\t\t\t\t\t\t<material diffuseColor=\".5714 .5714 .5714\"></material>\n" ++
         "\t\t\t\t\t\t\t</appearance>\n" ++
         "\t\t\t\t\t\t\t<box size=\".05 .25 .05\"></box>\n" ++
         "\t\t\t\t\t\t</shape>\n" ++
         "\t\t\t\t\t</transform>\n" ++  
       
         "\t\t\t\t\t<transform translation=\"0.11 0.485 0\" def=\"rightArm\">\n" ++
         "\t\t\t\t\t\t<shape>\n" ++
         "\t\t\t\t\t\t\t<appearance>\n" ++
         "\t\t\t\t\t\t\t\t<material diffuseColor=\".5714 .5714 .5714\"></material>\n" ++
         "\t\t\t\t\t\t\t</appearance>\n" ++
         "\t\t\t\t\t\t\t<box size=\".05 .25 .05\"></box>\n" ++  
         "\t\t\t\t\t\t</shape>\n" ++
         "\t\t\t\t\t</transform>\n" ++
       
         "\t\t\t\t</transform>\n" 

{- | 'htmlAnimatronics' devolve todas as coordenadas x, y e z que o robô percorre, em forma de /String/.-}

htmlAnimatronics :: [Bot] -> String
htmlAnimatronics [(x, y, z, _, _)]   = (show x) ++ " " ++ (show y) ++ " " ++ (show z)
htmlAnimatronics ((x, y, z, _, _):t) = (show x) ++ " " ++ (show y) ++ " " ++ (show z) ++ "  " ++ (htmlAnimatronics t)
                                           

{- | 'htmlRotation' devolve todas as orientações do robô (segundo y), em forma de /String/.-}
                                           
htmlRotation :: [Bot] -> String
htmlRotation [(_, _, _, o, _)]   = "0 1 0 " ++ (show o)
htmlRotation ((_, _, _, o, _):t) = "0 1 0 " ++ (show o) ++ "  " ++ (htmlRotation t)
                                           
                                           
{- | 'htmlRoutePosition' devolve o código /HTML/ que faz as /routes/ das posições do robô.-}                                           
                                           
htmlRoutePosition :: String
htmlRoutePosition = 
       "\t\t\t\t<route fromNode=\"clock\" toNode=\"moveRobot\" fromField=\"fraction_changed\" toField=\"set_fraction\"></route>\n" ++
       "\t\t\t\t<route fromNode=\"moveRobot\" toNode=\"bot\" fromField=\"value_changed\" toField=\"translation\"></route>\n"


{- | 'htmlRouteOrientation' devolve o código /HTML/ que faz as /routes/ das orientações do robô.-}

htmlRouteOrientation :: String
htmlRouteOrientation = 
       "\t\t\t\t<route fromNode=\"clock\" toNode=\"rotate\" fromField=\"fraction_changed\" toField=\"set_fraction\"></route>" ++
       "\n\t\t\t\t<route fromNode=\"rotate\" toNode=\"bot\" fromField=\"value_changed\" toField=\"set_rotation\"></route>"


{- | 'htmlColor' devolve todas as cores que a antena do robô tem enquanto percorre o tabuleiro.-}

htmlColor :: [Bot] -> String
htmlColor [(_, _, _, _, c)]   | c == LON || c == LOFF || c == IL = "1 1 0"
                              | otherwise                        = "0.6 0.86 0.97" 
htmlColor ((_, _, _, _, c):t) | c == LON || c == LOFF || c == IL = "1 1 0  " ++ (htmlColor t)
                              | otherwise                        = "0.6 0.86 0.97  " ++ (htmlColor t) 


{- | 'htmlEnding' devolve o código final da página /HTML/.-}

htmlEnding :: String
htmlEnding = "\t\t\t</scene>\n" ++ "\t\t</x3d>\n" ++ "\t</body>\n" ++ "</html>"


{- | 'htmlKey' devolve todas as /Keys/ para os vários /interpolators/.-}

htmlKey :: Float -> Float -> Int -> String
htmlKey _ _ 0 = "1"
htmlKey x y i = (show x) ++ " " ++ (htmlKey (x + y) y (i - 1))


{- | 'htmlLightsK' devolve o /colorInterpolator/ de cada lâmpada e as respetivas /routes/.-}

htmlLightsK :: [(Float, Float)] -> [Bot] -> String -> String
htmlLightsK [] _ _            = []
htmlLightsK ((x, y):t) bot tI = "\t\t\t\t<colorInterpolator def=\"color" ++ (show (auxRound x)) ++ "_" ++ (show (auxRound y)) ++ "\" key=\"" ++ tI ++
                                "\" keyValue=\"" ++ (htmlLightsC (x, y) "0.6 0.86 0.97" bot) ++ "\">" ++ "</colorInterpolator>\n" ++
                                "\t\t\t\t<route fromNode=\"clock\" toNode=\"color" ++ (show (auxRound x)) ++ "_" ++ (show (auxRound y)) ++ "\"" ++
                                " fromField=\"fraction_changed\" toField=\"set_fraction\"></route>\n" ++
                                "\t\t\t\t<route fromNode=\"color" ++ (show (auxRound x)) ++ "_" ++ (show (auxRound y)) ++ 
                                "\" toNode=\"" ++ (show (auxRound x)) ++ "_" ++ (show (auxRound y)) ++ "\"" ++
                                " fromField=\"value_changed\" toField=\"diffuseColor\"></route>\n" ++  
                                htmlLightsK t bot tI


{- | 'htmlLightsC' devolve as cores de uma lâmpada, enquanto o robô percorre o tabuleiro.-}

htmlLightsC :: (Float, Float) -> String -> [Bot] -> String
htmlLightsC (xL, zL) color [(x, _, z, _, c)] | c == LON && auxLights (xL, zL) (x, z)  = "1 1 0"
                                             | c == LOFF && auxLights (xL, zL) (x, z) = "0.6 0.86 0.97"
                                             | otherwise                              = color

htmlLightsC (xL, zL) color ((x, _, z, _, c):t) | c == LON && auxLights (xL, zL) (x, z)  = "1 1 0  " ++ (htmlLightsC (xL, zL) "1 1 0" t)
                                               | c == LOFF && auxLights (xL, zL) (x, z) = "0.6 0.86 0.97  " ++ (htmlLightsC (xL, zL) "0.6 0.86 0.97" t)
                                               | otherwise                              = color ++ "  " ++ (htmlLightsC (xL, zL) color t)


{- | 'auxLights' compara duas coordenadas de lâmpadas e verifica se são iguais, com um desvio de 0.005.-}

auxLights :: (Float, Float) -> (Float, Float) -> Bool
auxLights (a, b) (c, d) = (abs (a - c)) <= 0.005 && (abs (b - d)) <= 0.005


{- | 'convert2Walk' devolve uma lista com as orientações, em radianos, das pernas do robô.-}

convert2Walk :: [Bot] -> [Legs]
convert2Walk []                              = []
convert2Walk ((_, _, _, _, c):t) | c == W    = ("1 0 0 -0.2  1 0 0 0.2", "1 0 0 0.2  1 0 0 -0.2") : (convert2Walk t)
                                 | c == JU   = ("1 0 0 0  1 0 0 0", "1 0 0 0  1 0 0 0") : 
                                               ("1 0 0 -0.2  1 0 0 0.2", "1 0 0 0.2  1 0 0 -0.2") : (convert2Walk (tail t))
                                 | c == JD   = ("1 0 0 -0.2  1 0 0 0.2", "1 0 0 0.2  1 0 0 -0.2") : 
                                               ("1 0 0 0  1 0 0 0", "1 0 0 0  1 0 0 0") : (convert2Walk (tail t))
				     | otherwise = ("1 0 0 0  1 0 0 0", "1 0 0 0  1 0 0 0") : (convert2Walk t)
				
				
{- | 'htmlRouteOrientationLegs' devolve o código /HTML/ que faz as /routes/ das pernas do robô.-}				
				 
htmlRouteOrientationLegs :: String -> String -> String
htmlRouteOrientationLegs node2 leg = "<route fromNode=\"clock\" toNode=\"" ++ node2 ++ "\" fromField=\"fraction_changed\" toField=\"set_fraction\"> </route>\n" ++
				     "<route fromNode=\"" ++ node2 ++ "\" toNode=\"" ++ leg ++ "\" fromField=\"value_changed\" toField=\"set_rotation\"> </route>"


{- | 'htmlRotationLegs' devolve o código /HTML/ para as orientações das pernas do robô.-}

htmlRotationLegs :: Char -> [Legs] -> String
htmlRotationLegs _ []                    = []
htmlRotationLegs c ((l, r):t) | c == 'l' = l ++ "  " ++ (htmlRotationLegs c t)
                              | c == 'r' = r ++ "  " ++ (htmlRotationLegs c t)
