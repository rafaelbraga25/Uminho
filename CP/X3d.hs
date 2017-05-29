-- Biblioteca x3dom
-- (c) CP (2014/5)

module X3d where

-- Desenha um prisma triângular
drawTriangle :: ((Int,Int),Int) -> String
drawTriangle ((x,y),side) = "\n <Transform translation='"++(show x)++" "++(show y)++" 0'> \n <shape> \n <appearance> \n <material diffuseColor = '0.8,0.8,0.8'> \n </material>\n </appearance>\n <indexedFaceSet coordIndex = '0 1 2 3 1'>\n <coordinate point = '0 0 0,"++ (show side) ++" 0 0, 0 "++ (show side) ++" 0, 0 "++ (show side) ++" 0'>\n </coordinate>\n </indexedFaceSet>\n </shape>\n \n <shape>\n <appearance>\n <material diffuseColor = 'blue'>\n </material>\n </appearance>\n <indexedFaceSet coordIndex = '0 1 2 3 1'>\n <coordinate point = '"++ (show side) ++" 0 -0.15, "++ (show side) ++" 0 0, 0 "++ (show side) ++" -0.15, 0 "++ (show side) ++" 0'>\n </coordinate>\n </indexedFaceSet>\n </shape>\n \n <shape>\n <appearance>\n <material diffuseColor = '0.8,0.8,0.8'>\n </material>\n </appearance>\n <indexedFaceSet coordIndex = '0 1 2 3 1'>\n <coordinate point = '0 0 -0.15, "++ (show side) ++" 0 -0.15, 0 "++ (show side) ++" -0.15, 0 "++ (show side) ++" -0.15'>\n </coordinate>\n </indexedFaceSet>\n </shape>\n \n <shape>\n <appearance>\n <material diffuseColor = 'blue'>\n </material>\n </appearance>\n <indexedFaceSet coordIndex = '0 1 2 3 1'>\n <coordinate point = '0 0 -0.15, 0 0 0, 0 "++ (show side) ++" 0, 0 "++ (show side) ++" -0.15'>\n </coordinate>\n </indexedFaceSet>\n </shape>\n \n <shape>\n <appearance>\n <material diffuseColor = 'blue'>\n </material>\n </appearance>\n <indexedFaceSet coordIndex = '0 1 2 3 1'>\n <coordinate point = '0 0 0, 0 0 -0.15, "++ (show side) ++" 0 -0.15, "++ (show side) ++" 0 0'>\n </coordinate>\n </indexedFaceSet> \n </shape> \n </Transform> \n"

-- Finaliza o ficheiro .x3d com as tags que faltam
finalize :: String -> String
finalize body = "<head> \n <title> </title> \n <script type='text/javascript' src='http://www.x3dom.org/download/x3dom.js'> </script> \n <link rel='stylesheet' type='text/css' href='http://www.x3dom.org/download/x3dom.css'></link> \n </head> \n <x3d width='600px' height='400px'> \n <scene> <html> \n" ++ body ++ "</scene> \n </x3d> \n </html>"
