\documentclass[a4paper]{article}
\usepackage[a4paper,left=3cm,right=2cm,top=2.5cm,bottom=2.5cm]{geometry}
\usepackage{palatino}
\usepackage[colorlinks=true,linkcolor=blue,citecolor=blue]{hyperref}
\usepackage{graphicx}
%include polycode.fmt
%include cp1415t.sty

\title{
		    Cálculo de Programas
\\
		Trabalho Prático
\\
		LCC+LEI --- Ano Lectivo de 2014/15
}

\author{
		\dium
\\
		Universidade do Minho
}


\date\mydate

\makeindex

\begin{document}

\maketitle

\tableofcontents

\newpage

\section{Preâmbulo}

A disciplina de Cálculo de Programas tem como objectivo principal ensinar
a progra\-mação de computadores como uma disciplina científica. Para isso
parte-se de um repertório de \emph{combinadores} que formam uma álgebra da
programação (conjunto de leis universais e seus corolários) e usa-se esses
combinadores para construir programas \emph{composicionalmente}, isto é,
compondo programas já existentes.
  
Na sequência pedagógica dos planos de estudo dos dois cursos que têm esta disciplina,
restringe-se a aplicação deste método ao desenvolvimento de programas funcionais na linguagem \Haskell.

O presente trabalho tem por objectivo concretizar na prática os objectivos
da disciplina, colocando os alunos perante problemas de programação que
deverão ser abordados composicionalmente e implementados em \Haskell.
Há ainda um outro objectivo: o de ensinar a documentar programas e
a produzir textos técnico-científicos de qualidade.

\section{Documentação}
Para cumprir de forma integrada e simples os objectivos enunciados acima
vamos recorrer a uma técnica de programa\-ção dita \litp{literária} \cite{Kn92},
cujo princípio base é o seguinte:
\begin{quote}\em
Um programa e a sua documentação devem coincidir.
\end{quote}
Por outras palavras, o código fonte e a sua documentação deverão constar
do mesmo documento (ficheiro).

O ficheiro \texttt{cp1415t.pdf} que está a ler é já um exemplo de \litp{programação
literária}: foi gerado a partir do texto fonte \texttt{cp1415t.lhs}\footnote{O
suffixo `lhs' quer dizer \emph{\lhaskell{literate Haskell}}.} que encontrará
no \MaterialPedagogico\ desta disciplina descompactando o ficheiro \texttt{cp1415t.zip}
e executando
\begin{Verbatim}[fontsize=\small]
    lhs2TeX cp1415t.lhs > cp1415t.tex
    pdflatex cp1415t
\end{Verbatim}
em que \texttt\LhsToTeX\ é um pre-processador que faz ``pretty printing''
de código Haskell em \LaTeX\ e que deve desde já instalar a partir do endereço
\begin{quote}\tt\small
\lhstotex{https://hackage.haskell.org/package/lhs2tex}.
\end{quote}
Por outro lado, o mesmo ficheiro \texttt{cp1415t.lhs} é executável e contém
o ``kit'' básico, escrito em \Haskell, para realizar o trabalho. Basta executar
\begin{Verbatim}[fontsize=\small]
    ghci cp1415t.lhs
\end{Verbatim}
para ver que assim é: 
\begin{quote}
\begin{Verbatim}[fontsize=\small]
GHCi, version 7.8.3: http://www.haskell.org/ghc/  :? for help
Loading package ghc-prim ... linking ... done.
Loading package integer-gmp ... linking ... done.
Loading package base ... linking ... done.
[ 1 of 11] Compiling ListUtils        ( ListUtils.hs, interpreted )
[ 2 of 11] Compiling Cp               ( Cp.hs, interpreted )
[ 3 of 11] Compiling BTree            ( BTree.hs, interpreted )
[ 4 of 11] Compiling LTree            ( LTree.hs, interpreted )
[ 5 of 11] Compiling Exp              ( Exp.hs, interpreted )
[ 6 of 11] Compiling Nat              ( Nat.hs, interpreted )
[ 7 of 11] Compiling Show             ( Show.hs, interpreted )
[ 8 of 11] Compiling Probability      ( Probability.hs, interpreted )
[ 9 of 11] Compiling List             ( List.hs, interpreted )
[10 of 11] Compiling X3d              ( X3d.hs, interpreted )
[11 of 11] Compiling Main             ( cp1415t.lhs, interpreted )
Ok, modules loaded: List, Show, Nat, Exp, Cp, BTree, LTree, X3d,
Probability, Main, ListUtils.
\end{Verbatim}
\end{quote}
O facto de o interpretador carregar as bibliotecas do \MaterialPedagogico\ da disciplina,
entre outras, deve-se ao facto de, neste mesmo sítio do texto fonte,
se ter inserido o seguinte código \Haskell:

\begin{code}
import Data.List
import System.Process
import Cp
import List 
import Nat  
import Exp
import BTree
import LTree
import X3d
import Control.Parallel.Strategies
import Probability hiding (cond)
import System.Environment( getArgs )

\end{code}

\noindent Abra o ficheiro \texttt{cp1415t.lhs} no seu editor de texto preferido
e verifique que assim é: todo o texto que se encontra dentro do ambiente
\begin{quote}\small\tt
\verb!\begin{code}!
\\ ... \\
\verb!\end{code}!
\end{quote}
vai ser seleccionado pelo \GHCi\ para ser executado.

\section{Como realizar o trabalho}
Este trabalho teórico-prático deve ser realizado por grupos de três alunos.
Os detalhes da avaliação (datas para submissão do relatório e sua defesa
oral) são os que forem publicados na \cp{página da disciplina} na \emph{internet}.

Recomenda-se uma abordagem equilibrada e participativa dos membros do grupo
de trabalho por forma a poderem responder às questões que serão colocadas
na defesa oral do relatório.

Em que consiste, então, o \emph{relatório} a que se refere o parágrafo anterior?
É a edição do texto que está a ser lido, preenchendo o anexo \ref{sec:resolucao}
com as respostas. O relatório deverá conter ainda a identificação dos membros
do grupo de trabalho, na folha de rosto.

Para gerar o PDF integral do relatório deve-se ainda correr os comando seguintes,
que actualizam a bibliografia (com \Bibtex) e o índice remissivo (com \Makeindex)
\begin{Verbatim}[fontsize=\small]
    bibtex cp1415t.aux
    makeindex cp1415t.idx
\end{Verbatim}
e recompilar o texto como acima se indicou.

\section{Parte A}
Nesta primeira parte do trabalho pretende-se averiguar a capacidade de utilização
por parte dos alunos das bibliotecas fornecidas no \MaterialPedagogico\ da
disciplina. Algumas respostas são validadas por testes unitários. Sempre
que o resultado de um teste unitário for |False|, a solução proposta falha
a validação e deve ser revista.

\subsection{Biblioteca \LTree}\label{sec:LTree}
\begin{enumerate}
\item	A seguinte função
\begin{code}
balanced (Leaf _) = True
balanced (Fork(t,t')) = balanced t && balanced t' && abs(depth t - depth t') <= 1
\end{code}
testa se uma árvore binária está equilibrada ou não. Defina como catamorfismo
em \LTree\ a função auxiliar |depth|.
\item Seja dada:
\begin{code}
t = Fork (Fork (Leaf 10,Fork (Leaf 2,Fork (Leaf 5,Leaf 3))),Leaf 23)
\end{code}
\begin{teste}
Verifique que árvore |t| está desequilibrada:
\begin{code}
test01 = balanced t == False
\end{code}
\end{teste}
\item Recorrendo a funções da biblioteca \LTree,
escreva numa única linha de Haskell a função
\begin{spec}
balance :: LTree a -> LTree a
\end{spec}
que equilibra uma qualquer árvore binária.
\begin{teste}
Verifique que |balance t| é uma árvore equilibrada:
\begin{code}
test02 = balanced (balance t) == True
\end{code}
\end{teste}
\end{enumerate}

\subsection{Biblioteca \BTree}\label{sec:BTree}
Pretende-se construir um anamorfismo que produza uma árvore binária de procura
\emph{equilibrada} que contenha o intervalo definido por dois inteiros |(n,m)|:
\begin{code}
abpe(n,m) = anaBTree qsplit (n,m)
\end{code}
Comece por definir o gene |qsplit| e depois construa a árvore 
\begin{code}
t1 = abpe(20,30)
\end{code}
que será precisa na secção \ref{sec:parBTreeMap}.
\begin{teste}
Faça os testes seguintes:
\begin{code}
test03a = qsplit (4,30) == i2(17,((4,16),(18,30)))
test03b = qsplit (4,3) == i1()
test03c = qsplit (0,0) == i1()
test03d = qsplit (1,1) == Right (1,((1,0),(2,1)))
test03e = balBTree t1 == True
test03f = inordt t1 == [20..30]
\end{code}
\end{teste}

\subsection{Biblioteca para listas com sentinelas}\label{sec:SList}
Considere o tipo de dados que representa listas finitas com uma sentinela no fim:
\begin{code}
data SList a b = Sent b | Cons (a,SList a b) deriving (Show,Eq)
\end{code}
\begin{enumerate}
\item	Derive os isomorfismos |inSList| e |outSList|, adicione-os a este ficheiro
e passe aos testes que se seguem.
\begin{teste}
Faça os testes seguintes:
\begin{code}
test04a = let x = Cons(1,Sent "end") in inSList(outSList x) == x
test04b = let x = i2("ola",Sent "2") in outSList(inSList x) == x
\end{code}
\end{teste}
\item Derive os combinadores |cataSList|, |anaSList| e |hyloSList|,
e mostre que a função |merge| da biblioteca \LTree\ se pode escrever da forma seguinte,
\begin{code}
merge' :: Ord a => ([a], [a]) -> [a]
merge' = hyloSList (either id cons) mgen
\end{code}
para um dado gene |mgen| que deverá definir.
\begin{teste}
Faça os seguintes testes:
\begin{code}
test05a = mgen      ([0,2,5],[0,6]) == i2 (0,([2,5],[0,6]))
test05b = mgen ([0, 2, 5], []) == i1 [0,2,5]
test05c = merge' ([],[0,6]) == [0,6]
\end{code}
\end{teste}
\end{enumerate}

\section{Parte B}
O \sierp{triângulo de Sierpinski} é uma figura \fractal\ que
tem o aspecto da figura \ref{fig:sierp1} e que se
obtém da seguinte forma: considere-se um triângulo rectângulo e
isósceles $A$ cujos catetos têm comprimento $s$. A estrutura \fractal\ é
criada desenhando-se três triângulos no interior de $A$, todos eles
rectângulos e isósceles e com catetos de comprimento $s/2$. Este passo
é depois repetido para cada um dos triângulos desenhados, e assim
sucessivamente. O resultado dos cinco primeiros passos é dado na
Fig.~\ref{fig:sierp1}.

\begin{figure}
\begin{center}
	\includegraphics[width=0.4\textwidth]{media/sierp1.jpg}
\end{center}
	\caption{Um \sierp{triângulo de Sierpinski}}\label{fig:sierp1}
\end{figure}

Um \sierp{triângulo de Sierpinski} é gerado repetindo-se
infinitamente o processo acima descrito. No entanto, para efeitos de
visualização num monitor, cuja resolução é forçosamente finita,
faz sentido escolher uma representação adequada do triângulo, parando o
processo recursivo a um determinado nível. A figura a desenhar é
constituída por um conjunto finito de triângulos todos da mesma
dimensão (por exemplo, na figura \ref{fig:sierp1} há 243 triângulos).

\subsection{Criação de Triângulos de Sierpinski}
Seja cada triângulo geometricamente descrito pelas coordenadas do seu vértice
inferior esquerdo e o comprimento dos seus catetos:
\begin{code}
type Tri = (Point, Side)
\end{code}
onde
\begin{code}
type Side = Int
type Point = (Int, Int)
\end{code}

A estrutura recursiva de (uma representação finita de) um
\sierp{triângulo de Sierpinski} é captada por uma árvore ternária,
em que cada nó é um triângulo com os respectivos três sub-triângulos:
\begin{spec}
data TLTree = Tri Tri | Nodo TLTree TLTree TLTree
\end{spec}
Nas folhas dessa árvore encontram-se os triângulos mais pequenos,
todos da mesma dimensão, que deverão ser desenhados.
Apenas estes conterão informação de carácter
geométrico, tendo os nós da árvore um papel exclusivamente estrutural.
Portanto, a informação geométrica guardada em cada folha consiste nas
coordenadas do vértice inferior esquerdo e no lado dos catetos do
respectivo triângulo. A função
\begin{spec}
sierpinski :: Tri -> Int -> [Tri]
sierpinski t = apresentaSierp . (geraSierp t)
\end{spec}
recebe a informação do triângulo exterior e o número de níveis pretendido,
que funciona como critério de paragem do processo de construção do fractal.
O seu resultado é a lista de triângulos a desenhar.
Esta função é um hilomorfismo do tipo |TLTree|, i.e.\ a composição de
duas funções: uma que gera |TLTree|s,
\begin{spec}
geraSierp :: Tri -> Int -> TLTree
geraSierp t         0 = Tri t      
geraSierp ((x,y),s) n =
     let s' = div s 2
     in  Nodo
           (geraSierp ((x,y), s') (n-1))
           (geraSierp ((x+s',y), s') (n-1))
           (geraSierp ((x,y+s'), s') (n-1))
\end{spec}
e outra que as consome:
\begin{spec}
apresentaSierp :: TLTree -> [Tri]
apresentaSierp (Tri t      ) = [t]
apresentaSierp (Nodo a b c) = (apresentaSierp a)++(apresentaSierp b)++(apresentaSierp c)  
\end{spec}

\subsection{Trabalho a realizar}\label{sec:sierp}
\textbf{Preparação:}
\begin{enumerate}
\item Desenvolva a biblioteca ``pointfree" \texttt{TLTree.hs} de forma análoga
      a outras bibliotecas que conhece (\eg\ \BTree, \LTree, etc) e que estão
      disponíveis no \MaterialPedagogico.
\item Defina como catamorfismos de |TLTree| as funções
\begin{quote}
	|tipsTLTree :: TLTree b -> [b]|
\\	|countTLTree :: TLTree b -> Int|
\\	|depthTLTree :: TLTree b ->Int|
\\	|invTLTree :: TLTree b ->TLTree b|
\end{quote}
      respectivamente semelhantes a |tips|, |countLTree|, |depth| e |inv|
      (``mirror'') de \LTree.

\item Exprima as funções |geraSierp| e |apresentaSierp| recorrendo a
      anamorfismos e catamorfismos, respectivamente, do tipo |TLTree|.

\item Defina a árvore
\begin{code}
ts = geraSierp tri 5 where tri = ((0,0),256)
\end{code}
e faça os testes seguintes:
\begin{teste} Verifique a profundidade da árvore gerada e o respectivo número de triângulos:
\begin{code}
test06a = depthTLTree ts == 6
test06b = countTLTree ts == 243
test06c = countTLTree ts == length (tipsTLTree ts)
test06d = countTLTree ts == countTLTree (invTLTree ts)

\end{code}
\end{teste}
\end{enumerate}
\textbf{Visualização:}
Para visualizarmos triângulos de Sierpinski vamos usar \XFreedom,
uma biblioteca ``open-source'' para construção e visualização de gráficos
3D no Web.\footnote{Ver \url{http://examples.x3dom.org} para mais informação.
Em \url{http://examples.x3dom.org/IG/buddha-anim/x3dom_imageGeometry.html}, por exemplo,
pode ser visualizado um objecto gráfico com mais de um milhão de  triângulos.
Mais documentação em: 
\url{http://doc.x3dom.org/tutorials/index.html}.}
No pacote disponibilizado para a realização deste trabalho encontra a biblioteca
|X3d|, que inclui a função |drawTriangle| para geração de triângulos em 3D,
usando \XFreedom. Nesta abordagem, um ficheiro |x3dom| é construído em dois passos:
\begin{itemize}
\item Desenham-se os triângulos, utilizando:
\begin{spec}
drawTriangle :: ((Int,Int),Int) -> String
\end{spec}
\item Finaliza-se o ficheiro com as tags de início e final:
\begin{spec}
finalize :: String -> String
\end{spec}
\end{itemize}
\begin{enumerate}
\item
Usando estas funções e as que definiu anteriormente, faça a geração do HTML
que representa graficamente o triângulo de Sierpinski definido por
\begin{code}
dados = (((0,0), 32),4)
\end{code}
isto é, centrado na origem, com lado 32 e 4 níveis de recursividade.
No anexo \ref{sec:resolucao} sugere-se o recurso à função,
\begin{code}
render html = do { writeFile "triangle.html" html ; system "open triangle.html" }
\end{code}
(adapte-a, se necessário) para visualizar o triângulo gerado num ``browser".
Espera-se que o resultado final seja como o 
que se mostra na Figura~\ref{fig:sierp2}.
\end{enumerate}

\begin{figure}
\begin{center}
  \includegraphics[width=0.6\textwidth]{media/sierp2.jpg}
\end{center}
  \caption{Um \sierp{triângulo de Sierpinski} em x3dom}\label{fig:sierp2}
\end{figure}

\subsection*{Valorização}

Se tiver tempo, investigue como é que a sua resolução desta parte do trabalho
evolui para o desenho, não de \emph{triângulos} de Sierpinski, mas sim de
\emph{pirâmides} de Sierpinski --- ver a imagem da figura \ref{fig:sierp3}.
Pode recorrer, se desejar, às funções disponibilizadas no anexo \ref{sec:X3DOM}.

\begin{figure}
\begin{center}
	\includegraphics[width=0.6\textwidth]{media/pdSierpinski.jpg}
\end{center}
	\caption{Uma \psierp{pirâmide de Sierpinski}}\label{fig:sierp3}
\end{figure}

\section{Parte C}
\subsection{Mónades}
%format B = "\mathit B"
%format C = "\mathit C"
Os mónades são functores com propriedades adicionais que nos permitem obter
efeitos especiais em programação. Por exemplo, a biblioteca \Probability\
oferece um mónade para abordar problemas de probabilidades. Nesta biblioteca,
o conceito de distribuição estatística é captado pelo tipo
\begin{spec}
newtype Dist a = D {unD :: [(a, ProbRep)]}
\end{spec}
em que |ProbRep| é um real de |0| a |1|, equivalente a uma escala de |0| a |100%|.

Cada par |(a,p)| numa distribuição |d::Dist a| indica que a probabilidade
de |a| é |p|, devendo ser garantida a propriedade de  que todas as probabilidades
de |d| somam |100%|.
Por exemplo, a seguinte distribuição de classificações por escalões de $A$ a $E$,
\[
\begin{array}{ll}
A & \rule{2mm}{3pt}\ 2\%\\
B & \rule{12mm}{3pt}\ 12\%\\
C & \rule{29mm}{3pt}\ 29\%\\
D & \rule{35mm}{3pt}\ 35\%\\
E & \rule{22mm}{3pt}\ 22\%\\
\end{array}
\]
será representada pela distribuição
\begin{code}
d1 :: Dist Char
d1 = D [('A',0.02),('B',0.12),('C',0.29),('D',0.35),('E',0.22)]
\end{code}
que o \GHCi\ mostrará assim:
\begin{Verbatim}[fontsize=\small]
'D'  35.0%
'C'  29.0%
'E'  22.0%
'B'  12.0%
'A'   2.0%
\end{Verbatim}
É possível definir geradores de distribuições, por exemplo distribuições \emph{uniformes},
\begin{code}
d2 = uniform (words "Uma frase de cinco palavras")
\end{code}
isto é
\begin{Verbatim}[fontsize=\small]
     "Uma"  20.0%
   "cinco"  20.0%
      "de"  20.0%
   "frase"  20.0%
"palavras"  20.0%
\end{Verbatim}
distribuição \emph{normais}, eg.\
\begin{code}
d3 = normal [10..20]
\end{code}
etc.\footnote{Para mais detalhes ver o código fonte de \Probability, que é uma adaptação da
biblioteca \PFP\ (``Probabilistic Functional Programming''). A quem quiser souber mais
recomenda-se a leitura do artigo \cite{EK06}.}

|Dist| forma um \textbf{mónade} cuja unidade é |return a = D [(a,1)]| e cuja multiplicação é dada por
(simplificando a notação)
\begin{spec}
  ((kcomp f g)) a = [(y,q*p) | (x,p) <- g a, (y,q) <- f x]
\end{spec}
em que |g: A -> Dist B| e |f: B -> Dist C| são funções \textbf{monádicas} que representam
\emph{computações probabilísticas}.

Este mónade é adequado à resolução de problemas de \emph{probabilidades e
estatística} usando programação funcional, de forma elegante e como caso
particular de programação monádica. Vejamos um exemplo:
\begin{quote}
\emph{Problema: qual é a soma de faces mais provável quando lançamos dois dados num tabuleiro?}
\end{quote}
Assumindo que os dados não estão viciados, cada um oferece uma distribuição uniforme
das suas faces (|1| a |6|). Basta correr a expressão monádica
\begin{quote}
|do { x <- uniform [1..6] ;  y <- uniform [1..6] ; return(x+y) }|
\end{quote}
e obter-se-á:
\begin{Verbatim}[fontsize=\small]
*Main> do { x <- uniform [1..6] ;  y <- uniform [1..6] ; return(x+y) }
 7  16.7%
 6  13.9%
 8  13.9%
 5  11.1%
 9  11.1%
 4   8.3%
10   8.3%
 3   5.6%
11   5.6%
 2   2.8%
12   2.8%
\end{Verbatim}
A soma mais provável é |7|, com |16.7%|.

\subsection{Trabalho a realizar}\label{sec:monads}
É possível pensarmos em catamorfismos, anamorfismos etc probabilísticos,
quer dizer, programas recursivos que dão distribuições como resultados. Por
exemplo, neste enunciado é dado o combinador
\begin{code}
pcataList :: (Either () (a, b) -> Dist b) -> [a] -> Dist b
\end{code}
que é muito parecido com
\begin{spec}
cataList :: (Either () (a, b) -> b) -> [a] -> b
\end{spec}
da biblioteca \List. A única diferença é que o gene de |pcataList| é uma função probabilística.

Exemplo de utilização: recorde-se que |cataList (either zero add)| soma todos
os elementos da lista argumento, por exemplo:
\begin{quote}
|cataList (either zero add) [20,10,5] = 35|.
\end{quote}
Considere agora a função |padd| (adição probabilística) que,
com probabilidade |90%| soma dois números e com probabilidade |10%| os subtrai:
\begin{code}
padd(a,b) = D [(a+b,0.9),(a-b,0.1)]
\end{code}
Se se correr
\begin{code}
d4 = pcataList (either pzero padd) [20,10,5] where pzero = return . zero
\end{code}
obter-se-á:
\begin{Verbatim}[fontsize=\small]
35  81.0%
25   9.0%
 5   9.0%
15   1.0%
\end{Verbatim}

Com base nestes exemplos, resolva o seguinte
\begin{quote}\em
\textbf{Problema}: Uma unidade militar pretende enviar uma mensagem urgente
a outra, mas tem o aparelho de telegrafia meio avariado. Por experiência,
o telegrafista sabe que a probabilidade de uma palavra se perder (não ser
transmitida) é |5%|; no final de cada mensagem, o aparelho envia o código
|"stop"|, mas (por estar meio avariado), falha |10%| das vezes.

Qual a probabilidade de a palavra |"atacar"| da mensagem |words "Vamos atacar
hoje"| se perder, isto é, o resultado da transmissão ser |["Vamos","hoje","stop"]|?
e a de seguirem todas as palavras, mas faltar o |"stop"| no fim? E a da transmissão
ser perfeita?
\end{quote}

Responda a todas estas perguntas encontrando |g| tal que
\begin{code}
transmitir = pcataList gene
\end{code}
descreve o comportamento do aparelho.
%
\begin{teste}
Faça o seguinte teste unitário da sua versão para |gene|:
\begin{code}
test07 = gene (i2("a",["b"])) == D [(["a","b"],0.95),(["b"],0.05)]
\end{code}
\end{teste}
Responda então às perguntas do problema acima correndo a expressão:
\begin{quote}
|transmitir (words "Vamos atacar hoje")|
\end{quote}

\subsection{Programação funcional paralela}
Uma outra aplicação do conceito de mónade é a programação funcional paralela.
A biblioteca \ControlParallelStrategies, já carregada no início deste texto,
implementa esse tipo de programação, que hoje está na ordem do dia. O mónade
respectivo chama-se |Eval| e disponibiliza duas funções,
\begin{spec}
rpar :: a -> Eval a
rseq :: a -> Eval a
\end{spec}
conforme se deseja que uma dada computação seja efectuada em paralelo ou
sequencialmente.\footnote{Esta explicação é bastante simplista, mas serve
de momento. Para uma abordagem completa e elucidativa ver a referência \cite{Ma13}.}
Por exemplo,
\begin{code}
parmap :: (a -> b) -> [a] -> Eval [b]
parmap f [] = return []
parmap f (a:lt) = do
    a' <- rpar (f a)
    lt' <- parmap f lt
    return (a':lt')
\end{code}
é um |map| monádico que usa |rpar| para aplicar |f| a todos os elementos
de uma lista \emph{em paralelo}.

Se corrermos o |map| habitual em
\begin{quote}
|map fib [20..30] = [10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269]|
\end{quote}
(cálculo dos números de Fibonacci do vigésimo ao trigésimo), o tempo que
o cálculo vai demorar numa máquina com 2 cores\footnote{Intel Core 2 Duo
a 2.53 GHz.} será da ordem de |1.1|s. Já no caso de usar |parmap|
em vez de |map|, fará o mesmo cálculo em cerca de |60%| desse tempo.

Para verificar esta diferença siga as instruções seguintes:\footnote{Ver detalhes em \cite{Ma13}.}
\begin{enumerate}
\item	Compile o presente enunciado correndo:
\begin{verbatim}
ghc -O2 cp1415t -rtsopts -threaded
\end{verbatim}
\item	De seguida execute numa ``shell'' o seguinte comando,
\begin{verbatim}
./cp1415t exemplo seq +RTS -s -N2
\end{verbatim}
onde o |2| em |N2| indica |2| \emph{cores} (se a máquina em questão tiver
mais \emph{cores}, este número deverá ser actualizado). Como pode ver inspecionando
o código da função |main| na secção \ref{sec:main}, o que vai ser executado é
\begin{spec}
putStrLn . show . (map fib) $ [20..30]
\end{spec}
Das estatísticas que lhe aparecem no écran retenha esta:
\begin{verbatim}
Total   time    1.41s  (  1.11s elapsed)
\end{verbatim}
Em particular, o campo |elapsed| apresenta o tempo decorrido desde o início
da execução do programa até ao respectivo fim.
\item	De seguida execute
\begin{verbatim}
./cp1415t exemplo par +RTS -s -N2
\end{verbatim}
que irá chamar, desta vez
\begin{spec}
putStrLn . show . runEval . (parmap fib) $ [20..30]
\end{spec}
A estatística correspondente à de cima será, desta vez, da ordem seguinte:
\begin{verbatim}
Total   time    1.13s  (  0.69s elapsed)
\end{verbatim}
Em suma, a versão paralela é cerca de 1.61x mais rápida |((frac 1.11 0.69))|
que a sequencial.
\end{enumerate}

\subsection{Trabalho a realizar}\label{sec:parBTreeMap}
Com base na definição de |parmap| acima,
defina a função
\begin{code}

\end{code}
que implemente o ``map paralelo'' sobre \BTree's.

De seguida, corra testes semelhantes aos apresentados acima para apurar o ganho
em \emph{performance} da aplicação da função |fib| a todos os números
da árvore |t1| da secção \ref{sec:BTree}, em duas versões:
\begin{enumerate}
\item |fmap fib| (sem paralelismo, usando a função definida em \BTree), ou
\item usando |parBTreeMap fib|.
\end{enumerate}
Em máquinas mais rápidas e/ou com mais ``cores'' deve usar números maiores para obter
uma melhor distinção entre as duas versões.

%----------------- Bibliografia (exige bibtex) --------------------------------%

\bibliographystyle{plain}
\bibliography{cp1415t}

%----------------- Programa, bibliotecas e código auxiliar --------------------%

\newpage

\part*{Anexos}

\appendix

\section{Programa principal}\label{sec:main}
\begin{code}
main :: IO ()
main = getArgs >>= cond (not . null) exemp_or_exer errInvArgs
     where
        exemp_or_exer = cond (((==) "exemplo") . head) exemp exer
        exemp = cond (((==) 2) . length) execExemp errInvArgs
        execExemp = cond isPar execExempPar execExempSeq
        exer = cond (((==) 3) . length) execExer errInvArgs
        execExer = cond isPar execExerPar execExerSeq
        execExempSeq = const (putStrLn . show . (fmap fib) $ t1)      
        execExempPar = const (putStrLn . show . runEval . (parBTreeMap fib) $ t1)
\end{code}

\section{Bibliotecas e código auxiliar}
\begin{code}
errInvArgs :: a -> IO ()      
errInvArgs = const $ putStrLn msgInvArgs      
           where
           msgInvArgs = "Invalid arguments"           

execExerPar :: [String] -> IO ()
execExerPar  = undefined

execExerSeq :: [String] -> IO ()
execExerSeq = undefined

isPar :: [String] -> Bool
isPar = cond (((==) "par") . head . tail) (const True) (const False)

pcataList g = mfoldr (curry (g.i2)) ((g.i1) ()) where
    mfoldr f d [] = d
    mfoldr f d (a:x) = do { y <- mfoldr f d x ; f a y }
\end{code}

\subsection{``Easy X3DOM access''}\label{sec:X3DOM}
Defina-se a seguinte composição de funções
\begin{code}
x3dom = html . preamble . body . x3d . scene . items
\end{code}
para gerar um texto HTML que represente um objecto gráfico em \XFreedom.
Esta função usa as seguintes funções auxiliares:
\begin{code}
html = tag "html" []

preamble = headx `with` [title "CP/X3DOM generation",links,script]

body = tag "body" []

x3d = tag "x3d" [("width","\"500px\""),("height","\"400px\"")]

scene = tag "scene" []

items = concat

links = ctag "link" [
    ("rel",quote "stylesheet"),("type",quote "text/css"),
    ("href",quote "http://www.x3dom.org/x3dom/release/x3dom.css")]

script = ctag "script" [
    ("type",quote "text/javascript"),
    ("src",quote "http://www.x3dom.org/x3dom/release/x3dom.js")]

ctag t l = tag t l ""
\end{code}
onde
\begin{code}
tag t l x = "<"++t++" "++ps++">"++x++"</"++t++">"
     where ps = unwords [concat[t,"=",v]| (t,v)<-l]

headx = tag "head" []
\end{code}
De seguida dão-se mais algumas funções auxiliares facilitadoras:
\begin{code}
transform (x,y,z) = tag "transform" [("translation",quote(show3D(x,y,x)))]

groupx (x,y,z) = (tag "group" [("bboxSize", quote (show3D(x,y,z)))]) . items

shapex = tag "shape" []

title = tag "title" []

appearance = tag "appearance" []

show3D(x,y,z) = show x ++ " " ++ show y ++ " " ++ show z

t `with` l = ((t $ items l) ++)

quote s = "\""++s++"\""

prime s = "'"++s++"'"

box p col = (transform p . shapex . items) [ color col, ctag "box" [("size",prime "2,2,2")]]

cone p col b h = (transform p . shapex . items)
	 [ color col,
           ctag "cone" [("bottomRadius",prime (show b)), ("height",prime (show h))]]

color c = appearance (ctag "material" [("diffuseColor",prime c)])

\end{code}

%----------------- Soluções propostas -----------------------------------------%
\section{Soluções propostas}\label{sec:resolucao}

\subsection*{Secção \ref{sec:LTree}}

A função \emph{depth} calcula a profundidade de uma \emph{LTree}.
Esta função pode ter como parâmetro de entrada uma \emph{Leaf} ou um \emph{Fork}.

Quando recebe uma \emph{Leaf}, a função devolve o valor 1. Caso contrário, é um \emph{Fork} e é retornado o sucessor da sub-árvore (deste \emph{Fork}) com maior profundidade:

\begin{code}
depth :: LTree a -> Integer
depth = cataLTree (either one (succ . (uncurry max)))
\end{code}


A função \emph{balance} recebe uma \emph{LTree} e devolve essa \emph{LTree} balanceada. 

Começa por converter a \emph{LTree} numa lista (\emph{tips}). Depois disto, verifica se o comprimento dessa lista é igual a 1. Se isto for verdade, é retornado uma \emph{Leaf} de valor igual à da cabeça da lista. Caso contrário, divide a lista a meio (\emph{sep}) e retorna um \emph{Fork}. As sub-árvores deste \emph{Fork} são o resultado da chamada recursiva para cada metade da lista original.

Ao utilizar o anamorfismo de LTree (\emph{anaLTree}), foi possível definir esta função numa única linha:

\begin{code}
balance :: LTree a -> LTree a
balance = anaLTree (cond ((== 1) . length) (i1 . head) (i2 . (split (fst . sep) (snd . sep)))) . tips 
\end{code}


\subsection*{Secção \ref{sec:BTree}}

\emph{abpe} produz uma árvore binária de procura equilibrada definida pelo intervalo de dois inteiros \emph{(n, m)}.
É um anamorfismo de \emph{BTree}, em que o seu gene é a função \emph{qsplit}.

Começou-se por definir o \emph{qsplit} na versão \emph{pointwise}:

\begin{spec}
qsplit :: Integral a => (a, a) -> Either () (a, ((a, a), (a, a)))
qsplit (n, m) = if ((n, m) == (0, 0) || n > m)
                then i1 ()
                else let inter = (n + m) `div`  2
                     in i2 (inter, ((n, inter - 1), (inter + 1, m))) 
\end{spec}


No início a função verifica se os dois parâmetros de entrada são iguais a 0 ou se o parâmetro n (menor dos dois) é maior que o parâmetro m (maior dos dois). Caso isso aconteça, a função devolve (). Senão, calcula o valor intermédio (\emph{inter}) dos valores de entrada, devolvendo no final um par.

Depois, através do condicional de \emph{McCarthy}, definiu-se a versão \emph{pointfree}:

\begin{code}
qsplit :: Integral a => (a, a) -> Either () (a, ((a, a), (a, a)))
qsplit (n, m) = cond (p) (f) (g) (n, m)
	where inter = (`div` 2) . (uncurry (+))
              p = (uncurry (||)).(split (uncurry (>)) (== (0,0)))
              f = i1 . (!)
	      g = i2 . (split (inter) (split (split (fst) ((flip (-) 1) . inter)) (split ((flip (+) 1) . inter) (snd))))
\end{code}

\subsection*{Secção \ref{sec:SList}}

\begin{code}

inSList :: Either a (a1, SList a1 a) -> SList a1 a
inSList = either Sent Cons


outSList :: (SList a b) -> Either b (a, SList a b)
outSList (Sent x)      = i1 x
outSList (Cons (x, l)) = i2 (x, l)
\end{code}


O functor de uma \emph{SList} é igual ao functor de uma lista, sendo definido do seguinte modo:

\begin{code}
recSList f = id -|- id >< f
\end{code}

Assim sendo, o catamorfismo, o anamorfismo e o hilomorfismo, são idênticos aos de uma lista:

\begin{code}
cataSList :: (Either b (a, d) -> d) -> SList a b -> d
cataSList g  = g . recSList (cataSList g) . outSList   

anaSList :: (c -> Either a (b, c)) -> c -> SList b a
anaSList  g   = inSList . recSList (anaSList g) . g


hyloSList :: (Either b (d, c) -> c) -> (a -> Either b (d, a)) -> a -> c
hyloSList h g = cataSList h . anaSList g
\end{code}

\emph{mgen} recebe como parâmetro de entrada um par com duas listas. Se uma dessas listas seja vazia, devolve a lista não vazia. Caso contrário, devolve um par. O primeiro elemento é a maior das cabeças, extraída de uma das listas. O segundo elemento é um outro par com o resto das listas.


\begin{code}
mgen :: Ord a => ([a], [a]) -> Either [a] (a, ([a], [a]))
mgen (l, [])        = i1 l
mgen ([], r)        = i1 r
mgen (x:xs, y:ys) | (x <= y)  = i2 (x, (xs, y:ys))
                  | otherwise = i2 (y, (x:xs, ys))
\end{code}


\subsection*{Secção \ref{sec:sierp}}

Começou-se por definir três funções auxiliares, para facilitar o cálculo e a leitura do código:

\begin{code}

swapTLTree (a, (b, c)) = (c, (b, a))

maxTLTree :: (Integer, (Integer, Integer)) -> Integer
maxTLTree (a, (b, c)) = max a (max b c)

addTLTree :: (Integer, (Integer, Integer)) -> Integer
addTLTree (a, (b, c)) = a + b + c
\end{code}


Uma \emph{TLTree} pode ser um ponto com as coordenadas de um vértice do triângulo e o lado do triângulo (isósceles) ou três triângulos definidos da mesma maneira. 

Definiu-se o \emph{inTLTree} e o \emph{outTLTree} da seguinte forma:

\begin{code}
inTLTree = either L N

outTLTree (L t) = i1 t
outTLTree (N (a, (b, c))) = i2 (a, (b, c))
\end{code}

O functor base e o functor de \emph{TLTree} são semelhantes aos de uma \emph{LTree}, só que em vez de terem duas sub-árvores, numa \emph{TLTree} tem-se três sub-árvores:

\begin{code}
baseTLTree g f = g -|- ((f >< (f >< f)))

recTLTree f = id -|- ((f >< (f >< f)))

\end{code}

O catamorfismo, anamofismo e hilomorfismo, são idênticos aos de uma \emph{LTree}. Sendo aplicados aos functores de uma \emph{TLTree}:

\begin{code}

cataTLTree a = a . (recTLTree (cataTLTree a)) . outTLTree

anaTLTree f = inTLTree . (recTLTree (anaTLTree f)) . f

hyloTLTree a c = cataTLTree a . anaTLTree c

\end{code}

A estrutura das funções que se seguem também são semelhantes às de uma \emph{LTree}, mas usando as funções auxiliares definidas para uma \emph{TLTree}:

\begin{code}

tipsTLTree :: TLTree b -> [b]
tipsTLTree = cataTLTree (either singl conc)
        where conc (l, (m, r)) = l ++ m ++ r
        
invTLTree :: TLTree b -> TLTree b
invTLTree = cataTLTree (inTLTree . (id -|- swapTLTree))

depthTLTree :: TLTree b -> Int
depthTLTree = fromIntegral . (cataTLTree (either one (succ . maxTLTree)))

countTLTree :: TLTree b -> Int
countTLTree = fromIntegral . (cataTLTree (either one addTLTree))

\end{code}

Estas funções foram dadas pelo enunciado, sendo adaptadas para a estrutura de uma \emph{TLTree}:

\begin{code}

sierpinski :: Tri -> Int -> [Tri]
sierpinski t = apresentaSierp . (geraSierp t)
\end{code}

\begin{code}

geraSierp :: Tri -> Int -> TLTree Tri
geraSierp t 0           = L t
geraSierp ((x, y), s) n = let s' = div s 2
                          in N ((geraSierp ((x, y), s') (n - 1)),
                                ((geraSierp ((x + s', y), s') (n - 1)),
                                 (geraSierp ((x, y + s'), s') (n - 1))))  
\end{code}


\begin{code}
apresentaSierp (L t)           = [t]
apresentaSierp (N (a, (b, c))) = (apresentaSierp a) ++ (apresentaSierp b) ++
                                (apresentaSierp c)
\end{code}


\begin{code}
draw = render html where html = rep dados

\end{code}

\emph{rep} escreve o código \emph{HTML} que permite visualizar o triângulo, a partir de uma lista. Cada elemento desta lista representa as coodenadas dos pontos do triângulo e o lado do triângulo, sendo calculada a partir de um catamorfismo.

\begin{code}
rep x = finalize (cataList (either nil (conc . (drawTriangle >< id))) (sierpinski (fst x) (snd x)))
\end{code}

\pdfout{%

\begin{code}
data TLTree a = L a | N (TLTree a,(TLTree a,TLTree a)) deriving (Eq,Show)
\end{code}
}%

\subsection*{Secção \ref{sec:monads}}

\begin{figure}
\begin{center}
	\includegraphics[width=0.6\textwidth]{monades.jpg}
\end{center}
	\caption{Resultado da execução de \emph{transmitir (words "Vamos atacar hoje")}}
\end{figure}


Como se pode verificar na imagem acima:
\begin{itemize}
 	\item a probabilidade de se perder a palavra "atacar" é igual a 4.1\%
	\item a probabilidade de se receber a mensagem original, sem o "stop", é igual a 8.6\%
	\item a probabilidade da mensagem ser perfeita é igual a 77.2\%
\end{itemize}

O gene do \emph{pcataList} da função \emph{transmitir} é definido da seguinte forma:

\begin{code}

gene = (either ps pm)

\end{code}

\emph{ps} é uma distribuição onde há uma probabilidade de 90\% devolver a string "stop" e uma probabilidade de 10\% devolver uma lista vazia.

\begin{code}

ps _ = D [(["stop"], 0.9), ([], 0.1)]

\end{code}

\emph{pm} é uma distribuição que, recebendo um par, existe uma probabilidade de 95\% devolver uma lista com os parâmatros de entrada e uma probabilidade de 5\% devolver apenas o segundo elemento do par de entrada.

\begin{code}

pm (a, b)= D [(a : b, 0.95), (b, 0.05)]

\end{code}

\subsection*{Secção \ref{sec:parBTreeMap}}

\emph{parBTreeMap} define-se da seguinte forma:

\begin{code}

parBTreeMap :: (a -> b) -> (BTree a) -> Eval (BTree b) 
parBTreeMap _ Empty              = return Empty
parBTreeMap f (Node (n, (e, d))) = do n' <- rpar (f n)
                                      e' <- parBTreeMap f e
                                      d' <- parBTreeMap f d
                                      return (Node (n', (e', d')))

\end{code}

Executando o comando para a função sequencial:

\begin{verbatim}

./cp1415t exemplo seq +RTS -s -N4

\end{verbatim}

obtém-se o tempo de execução do programa:

\begin{verbatim}

Total	time	3.23s	(1.30s elapsed)

\end{verbatim}

Executando o comando para a função em paralelo:

\begin{verbatim}

./cp1415t exemplo par +RTS -s -N4

\end{verbatim}

obtém-se o tempo de execução do programa:

\begin{verbatim}

Total	time	2.52s	(0.80s elapsed)

\end{verbatim}


Como se pode verificar, a versão paralela é 1.63 vezes mais rápida que a versão sequencial.



\section{Pirâmide de Sierpinski}

O processo de construção de uma pirâmide de Sierpinski é semelhante ao de um triângulo de Sierpinski. Seja \emph{P} uma pirâmide 
constituída por quatro triângulos iguais cujo comprimento dos seus catetos é \emph{s}. A pirâmide é gerada desenhando cinco
pirâmides iguais, cujo valor dos catetos das suas faces é \emph{s/2}, no interior de \emph{P}. Este processo é repetido infinitamente.

Cada face da pirâmide é definida do seguinte modo:

\begin{code}

type PointPyr = (Float, Float, Float)
type Pyr      = (PointPyr, Float)

\end{code}

Optou-se por valores do tipo \emph{Float} em vez de valores do tipo \emph{Int} para maior precisão no desenho das pirâmides.

A estrutura recursiva de uma pirâmide de Sierpinski é a seguinte, em que cada nó é uma pirâmide com as respetivas cinco sub-pirâmides:

\begin{code}

data PLTree = Pyr Pyr | Nd PLTree PLTree PLTree PLTree PLTree deriving (Show)

\end{code}

\emph{dadosPyr} é um exemplo de uma pirâmide centrada na origem, com arestas de comprimento 32 e com 4 níveis de recursividade.

\begin{code}

dadosPyr = (((0, 0, 0), 32), 4)

\end{code}

As funções seguintes são semelhantes às funções para um triângulo, só que adaptadas para a estrutura de uma pirâmide:

\begin{code}

drawPyr = renderPyr html where html = repPyr dadosPyr

renderPyr html = do { writeFile "pyr.html" html; system "open pyr.html" }

repPyr x = finalize (cataList (either nil (conc . (drawPyramide >< id))) (sierpinskiPyr (fst x) (snd x)))

sierpinskiPyr p = apresentaSierpPyr . (geraSierpPyr p)

apresentaSierpPyr (Pyr p) = [p]
apresentaSierpPyr (Nd a b c d e) = (apresentaSierpPyr a) ++ 
                                   (apresentaSierpPyr b) ++ 
                                   (apresentaSierpPyr c) ++ 
                                   (apresentaSierpPyr d) ++ 
                                   (apresentaSierpPyr e)

geraSierpPyr t 0              = Pyr t
geraSierpPyr ((x, y, z), s) n = let s' = s / 2
                                in Nd (geraSierpPyr ((x, y, z), s') (n - 1))
                                      (geraSierpPyr ((x - (s2 s'), y + (sy s'), z + (s2 s')), s') (n - 1))
                                      (geraSierpPyr ((x - (s2 s'), y + (sy s'), z - (s2 s')), s') (n - 1))
                                      (geraSierpPyr ((x + (s2 s'), y + (sy s'), z - (s2 s')), s') (n - 1))             
                                      (geraSierpPyr ((x + (s2 s'), y + (sy s'), z + (s2 s')), s') (n - 1))
\end{code}

\emph{drawPyramide} constrói o código \emph{HTML} para a representação da pirâmide. Recebe como parâmetros de entrada as coordenadas de um ponto e o comprimento de uma aresta. Tendo isto, a função constrói uma pirâmide. Para isso, calcula as coordenadas dos cinco pontos que a constitui: \emph{coordinate point = ...}. Os pontos são unidos (criam-se as quatro faces laterais): \emph{indexedFaceSet coordIndex = ...}. A base da pirâmide não é desenhada.

Finalmente, a propriedade \emph{solid = 'false'} serve para a pirâmide ser visível em qualquer orientação.

\begin{code}

drawPyramide :: ((Float, Float, Float), Float) -> String
drawPyramide ((x,y,z),side) = "\n <Transform translation='"++
 (show x) ++ " " ++ (show y) ++ " " ++ (show z) ++ "'> \n" ++ 
  "<shape> \n" ++ 
   "<appearance> \n " ++ 
    "<material diffuseColor = '0.8,0.8,0.8'> \n </material>\n" ++ 
   "</appearance>\n" ++ 
   "<indexedFaceSet coordIndex = " ++
    "'0 1 2 -1 0 2 3 -1 0 3 4 -1 0 1 4 -1' solid='false'>" ++ 
    "\n<coordinate point = '0 0 0,"++ (show ((-1) * (s2 side))) ++ 
    " " ++ (show (sy side)) ++ " " ++ (show (s2 side)) ++ "," ++ 
    (show ((-1) * (s2 side))) ++ " " ++ (show (sy side)) ++ " " ++ 
    (show ((-1) * (s2 side))) ++ "," ++ (show (s2 side)) ++ " " ++ 
    (show (sy side)) ++ " " ++ (show ((-1) * (s2 side))) ++ "," ++ 
    (show (s2 side)) ++ " " ++ (show (sy side)) ++ " " ++ 
    (show (s2 side)) ++ "'>\n </coordinate>\n" ++ 
   "</indexedFaceSet>\n " ++ 
  "</shape>\n" ++    
 "</Transform> \n"

\end{code}

Funções auxiliares para calcular o comprimento dos lados de uma sub-pirâmide (\emph{s2}) e a altura de uma sub-pirâmide (\emph{sy}).

\begin{code}

s2 side = side / 2

sy side = (-1) * (sqrt ((side ^ 2) - (s2 side) ^ 2))

\end{code}

%----------------- Fim do anexo cpm soluções propostas -------------------------%

%----------------- Índice remissivo (exige makeindex) -------------------------%

\printindex

%----------------- Fim do documento -------------------------------------------%

\end{document}

