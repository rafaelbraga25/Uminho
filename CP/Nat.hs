{-# OPTIONS_GHC -XNPlusKPatterns #-}

-- (c) MP-I (1998/9-2006/7) and CP (2005/6-2014/5)

module Nat where

import Cp

-- (1) Datatype definition -----------------------------------------------------

-- "data Nat = 0 | succ Nat"   -- in fact: Haskell Integer is used as carrier type

inNat = either (const 0) succ

outNat 0 = i1 ()
outNat (n+1) = i2 n

-- NB: inNat and outNat are isomorphisms only if restricted to non-negative integers

-- (2) Ana + cata + hylo -------------------------------------------------------

cataNat g   = g . recNat (cataNat g) . outNat

recNat f    = id -|- f

anaNat h    = inNat . (recNat (anaNat h) ) . h

hyloNat g h = cataNat g . anaNat h

-- paraNat g   = g . recNat (split id (paraNat g)) . outNat

-- (3) Map ---------------------------------------------------------------------

-- (4) Examples ----------------------------------------------------------------

for :: (Integral b) => (a -> a) -> a -> b -> a
--
-- for is the "fold" of natural numbers
--
for b i = cataNat (either (const i) b)

somar a = cataNat (either (const a) succ)

multip a = cataNat (either (const 0) (a+))

exp a = cataNat (either (const 1) (a*))

-- sq (square of a natural number) 

sq 0 = 0
sq (n+1) = oddn n + sq n where oddn n = 2*n+1

-- sq = paraNat (either (const 0) g)i

sq' = p1 . aux
       -- this is the outcome of calculating sq as a for loop using the
       -- mutual recursion law
      where aux = cataNat (either (split (const 0)(const 1)) (split (uncurry (+))((2+).p2)))

sq'' n  = -- the same as a for loop (putting variables in)
       p1 (for body (0,1) n)
       where body(s,o) = (s+o,2+o)

-- factorial

fac = p2. facfor
facfor = for (split (succ.p1) mul) (1,1) 

-- factorial = paraNat (either (const 1) g) where g(n,r) = (n+1) * r

-- Integer division as an anamorphism --------------

idiv :: Integer -> Integer -> Integer
{-- pointwise
x `wdiv` y  |   x <  y    = 0
            |   x >= y    = (x - y) `wdiv` y + 1
--}

idiv = flip aux

aux y = anaNat divide where 
           divide x | x <  y  = i1 ()
                    | x >= y  = i2 (x - y)

--- end of Nat.hs
