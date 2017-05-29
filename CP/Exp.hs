
-- (c) MP-I (1998/9-2006/7) and CP (2005/6-2014/5)
--
-- NB: unofficial, unstructured library (!) to be re-written if needed
--     Enables a data type of expressions to be displayed as html tables

module Exp where

import Cp
import BTree
import LTree
import System.Process
import GHC.IO.Exception

-- Functions dependent on your OS:------------------------------------------

-- (a) For Linux:

-- expShow fn e = do { expDisplay fn e ; system(open fn) } where open s = "gnome-open "++ s  --- Linux

-- (b) For MAC:

expShow fn e = do { expDisplay fn e ; system(open fn) } where open s = "open "++ s  --- MAC OS

-- (c) For Windows:

{--
expShow fn e = do { expDisplay fn e ;                            --- Windows
	            system("setx path \"%PATH%;"++path++"/m\"");
	            system("start/b " ++ fn)
                  }  where path = "C:\\Programs\\......." -- path of HTML default browser
--}
----------------------------------------------------------------------------

data Exp v o =   Var v              -- expressões ou são variáveis
               | Term o [ Exp v o ] -- ou termos envolvendo operadores e
                                    -- subtermos
               deriving Show

inExp = either Var (uncurry Term)
outExp(Var v) = i1 v
outExp(Term o l) = i2(o,l)

baseExp f g x = f -|- (g >< map x)

recExp x = baseExp id id x

cataExp g = g . recExp (cataExp g) . outExp

instance BiFunctor Exp
         where bmap f g = cataExp ( inExp . baseExp f g id )

data Cell a = ICell a Int Int | LCell a Int Int deriving Show

type Html a = [ Cell a ]

data Txt = Str String | Blk [ Txt ] deriving Show

inds :: [a] -> [Int]
inds [] = []
inds (h:t) = inds t ++ [succ (length t)]

seq2ff :: [a] -> [(Int,a)]
seq2ff = (uncurry zip) . (split inds id)

ff2seq m = map p2 m

txtFlat :: Txt -> [[Char]]
txtFlat (Str s) = [s]
txtFlat (Blk []) = []
txtFlat (Blk (a:l)) = txtFlat a ++ txtFlat (Blk l)

expFold :: (a -> b) -> (c -> [b] -> b) -> Exp a c -> b
expFold f g (Var e) = f e
expFold f g (Term o l) = g o (map (expFold f g) l)

expPara :: (a -> b) -> (Exp a c -> c -> [b] -> b) -> Exp a c -> b
expPara f g (Var e) = f e
expPara f g (Term o l) = g (Term o l) o (map (expPara f g) l)

expBiFunctor f g = expFold (Var . f) h
                   where h a b = Term (g a) b

expLeaves :: Exp a b -> [a]
expLeaves = expFold singl h
            where singl a = [a]
                  h o l = foldr (++) [] l 

expWidth :: Exp a b -> Int
expWidth = length . expLeaves

expDepth :: Exp a b -> Int
expDepth = expFold (const 1) h
           where h o x = (succ . (foldr max 0)) x

exp2Html n (Var v) = [ LCell v n 1 ]
exp2Html n (Term o l) = g (expWidth (Term o l)) o (map (exp2Html (n-1)) l)
                        where g i o k = [ ICell o 1 i ] ++ (foldr (++) [] k)

html2Txt :: (a -> Txt) -> Html a -> Txt
html2Txt f = html . table . (foldr g u) 
             where u = Str "\n</tr>"
                   g c (Str s) = g c (Blk [Str s])
                   g (ICell a x y) (Blk b) = Blk ([ cell (f a) x y ] ++ b)
                   g (LCell a x y) (Blk b) = Blk ([ cell (f a) x y,  Str "\n</tr>\n<tr>"] ++ b)
                   html t = Blk [ Str("<meta charset=\"utf-8\"/>"++"<html>\n<body bgcolor=\"#F4EFD8\" " ++
                                        "text=\"#260000\" link=\"#008000\" " ++
                                        "vlink=\"#800000\">\n"),
                                   t,
                                   Str "<html>\n"
                                 ]
                   table t = Blk [ Str "<table border=1 cellpadding=1 cellspacing=0>",
                               t,
                               Str "</table>\n"
                             ]
                   cell c x y = Blk [ Str("\n<td rowspan=" ++
                                            itoa y ++
                                            " colspan=" ++
                                            itoa x ++
                                            " align=\"center\"" ++
                                            ">\n"),
                                       c,
                                            Str "\n</td>"
                                     ]
                   itoa x = show x

expDisplay :: FilePath -> Exp String String -> IO ()
expDisplay fn =
      (writeFile fn) . (foldr (++) []) . txtFlat . (html2Txt Str) .
      (uncurry exp2Html . (split expDepth id))

{--
--import Ffun
exp2ExpTar (Var v) =  [[1] |-> v]
exp2ExpTar (Term o l) = [[1] |-> o] `plus`
           let m = map exp2ExpTar l
               n = seq2ff m
               k = map f n
           in mPLUS k
--}

-- (c) Auxiliary functions -----------------------------------------------------
class (Show t) => Expclass t where
      pict :: t -> IO ExitCode
--------------------------------------------------------------------------------
instance (Show a) => Expclass (BTree a) where
    pict = expShow "_.html" .  cBTree2Exp . (fmap show)

cBTree2Exp :: BTree a -> Exp [Char] a
cBTree2Exp = cataBTree (either (const (Var "nil")) h)
	     where h(a,(b,c)) = Term a [c,b] 
--------------------------------------------------------------------------------
instance (Show a) => Expclass [a] where
    pict = expShow "_.html" .  cL2Exp . (fmap show)

cL2Exp [] = Var " "
cL2Exp l = Term "List" (map Var l)

--------------------------------------------------------------------------------
instance (Show a) => Expclass (LTree a) where
    pict = expShow "_.html" .  cLTree2Exp . (fmap show)

cLTree2Exp = cataLTree (either Var h)
	     where h(a,b) = Term "Fork" [a,b] 
--------------------------------------------------------------------------------
