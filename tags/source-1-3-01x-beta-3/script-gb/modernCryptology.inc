\setcounter{theorem}{0}
\setcounter{definition}{0}

\newcommand{\NT}{\vspace*{0.2\baselineskip}\\}
%\newcommand{\VT2}{\vspace*{0.1\baselineskip}\\}
\newcommand{\HZ}{\vspace*{0.5\baselineskip}}
\newcommand{\R}{\text{I}\!\text{R}}
\newcommand{\N}{\text{I}\!\text{N}}
\newcommand{\Q}{\text{Q}\!\!\!\text{l}\,\,}
\newcommand{\C}{\text{C}\!\!\!\text{l}\,\,}
\newcommand{\K}{\text{I}\!\text{K}}
\newcommand{\Z}{\mathbf{\mathbb{Z}}}
%--------------------------------------- matheScript-Zeichen definieren
\newcommand{\fs}{\mathscr{F}}  
\newcommand{\es}{\mathscr{E}}  
\newcommand{\cs}{\mathscr{C}}  
\newcommand{\gs}{\mathscr{G}}
\newcommand{\is}{\mathscr{I}}
\newcommand{\os}{\mathscr{O}}
\newcommand{\ks}{\mathscr{K}}
\newcommand{\qs}{\mathscr{Q}}
\newcommand{\us}{\mathscr{U}}
\newcommand{\hs}{\mathscr{H}}
\newcommand{\ps}{\mathscr{P}}
\newcommand{\as}{\mathscr{A}}
\newcommand{\rs}{\mathscr{R}}
\newcommand{\bs}{\mathscr{B}}
%-------------------------------------
\newcommand{\PG}{\text{I}\!\text{P}}
\newcommand{\carre}{\square}
\newcommand{\ncarre}{/\negthickspace\negthickspace\square}
\newcommand{\ncarreq}{{\ncarre}_q}
\newcommand{\ncarree}{/\negthickspace\negthickspace\negthickspace\square}
\newcommand{\ncarrepi}{{\ncarre}_{p^i}}
\newcommand{\mc}[1]{{\cal #1}}
\newcommand{\Char}{\text{char}}
\newcommand{\Aut}{\text{Aut}}
\newcommand{\Fix}{\text{Fix}}
\newcommand{\Syl}{\text{Syl}}
\newcommand{\Bild}{\text{Bild}}
\newcommand{\ggt}{{\rm gcd}}
\newcommand{\kgv}{\text{kgV}}
\newcommand{\Id}{\text{Id}}
\newcommand{\nqcarre}{{\ncarre}_{q^2}}
%\newcommand{\mod}{{\rm mod~}}
%\normalsize
%\parindent = 0pt
%\setlength{\textwidth}{140mm}
%\setlength{\textheight}{216mm}


% \theorembodyfont{\} 
% \newtheorem{Bsp}{Beispiel}[section]

% {\theorembodyfont{\em}
%                  \newtheorem{Def}[Bsp]{Definition} }

% \theorembodyfont{\em} 
% \newtheorem{Hilf}[Bsp]{Hilfssatz}

%\theorembodyfont{\em} 
% \newtheorem{Lem}[Bsp]{Lemma}

%\theorembodyfont{\em} 
% \newtheorem{Kor}[Bsp]{Korollar}

%\theorembodyfont{\em}
% \newtheorem{Folg}[Bsp]{Folgerung}

%\theorembodyfont{\em}
%  \newtheorem{Satz}[Bsp]{Satz}

% \theoremstyle{break} 
% {\theorembodyfont{\em} 
% \newtheorem{Theo}[Bsp]{Theorem}}                 
% In diesem Stil wird nach dem Theoremkopf ein Zeilenumbruch vorgenommen.

% \theoremstyle{break} 
% {\theorembodyfont{\em} 
% \newtheorem{Haupt}[Bsp]{Hauptsatz}}                 
% In diesem Stil wird nach dem Theoremkopf ein Zeilenumbruch vorgenommen.
% \newenvironment{Beweis}[1]
%   {\textbf{Beweis #1} \\}
%   {\hfill$\Box$ \\}

\setlength{\fboxrule}{.4pt}
\setlength{\fboxsep}{4pt}

\newpage
%**************************************************************************************************************************
\section{The Mathematical Ideas Behind Modern Cryptography}
 (Oyono R. / Esslinger B., September 2000, Update Nov. 2000)
\subsection{One-way functions with trapdoor and complexity classes}
\index{Cryptography!modern} \index{One-way function} \hypertarget{OneWayFunktion1}{}
A {\bf one-way function} is a (one-to-one) function that can be calculated 
efficiently, but whose inverse is extremely complicated and practically 
impossible to calculate.\par

To put it more precisely:  A one-way function is a mapping $ f $ from a set $ X 
$ to a set $ Y, $ such that $ f(x) $ can be calculated easily for each element $ 
x $ of $ X $, whereas for (almost) every $ y $ from $ Y $  it is practically 
impossible to find an inverse image $ x $ (i.e. an $ x $ where $ f(x)=y $).\par

An everyday example of a one-way function is a telephone book: the function to 
be performed is to assign a name to the corresponding telephone number. This can 
be done easily due to the fact that the names are sorted alphabetically. 
However, the inverse function - assigning a name to a given number - is 
obviously difficult if you only have a telephone book available. \par

One-way functions play a decisive role in cryptography. Almost all cryptographic 
terms can be rephrased using the term one-way function. Let's take for example 
public-key encryption \index{Encryption!public-key} (asymmetric 
cryptography):\par

Each subscriber $ T $ to the system is assigned a private \index{Key!private} 
\index{Key!public} key $ d_T $   and what is known as a public key $ e_T $. 
These keys must have the following property (public-key property):\\
For an opponent who knows the public key $ e_T $, it is practically impossible 
to determine the private key  $ d_T $.\par

In order to construct useful public-key procedures, therefore, we look for a 
one-way function that is ''easy'' to calculate in one direction {}, but 
is ''difficult'' (practically impossible) to calculate in the other 
direction, provided that a particular piece of additional information 
\index{One-way function!with trapdoor } (trapdoor) is not available. This 
additional piece of information allows the inverse to be found efficiently. Such 
functions are called {\bf trapdoor one-way functions}. In the above case, $ d_T 
$ is the trapdoor information. \par

In this process, we describe a problem as ''easy'' if it can be solved in 
\index{Runtime!polynomial} polynomial time as a function of the length of the 
input. If the length of the input is $ n $ bits, then the time for calculating 
the function is proportional to $ n^{a}, $ where $ a $  is a constant. We say 
that the \index{Complexity} complexity of such problems is $ O(n^{a}) $. 


The term ''practically impossible'' is slightly less precise. In 
general, we can say that a problem cannot be solved \index{Runtime!efficient} 
efficiently, if the time required to solve it increases more quickly than the 
polynomial time as a function of the size of the input. If, for example, the 
length of the input is $ n $  bits and the time required for calculating the 
function is proportional to $ 2^n $, then the following currently applies: the 
function practically cannot be calculated for $n > 80$ (for $ a=5 $ the 
following applies: from the length $ n=23 $, $ 2^n$ is greater than $n^5 $, after 
which $ 2^n $ clearly increases more quickly ($ 2^{23}=8,388,608, $ $ 23^5= 
6,436,343 $)).\par 

In order to develop a public-key procedure that can be implemented in practice, 
it is therefore necessary to discover a suitable trapdoor one-way function.\par

In order to tidy things up among this confusing multitude of possible problems 
and their complexities, we group problems with similar complexities into 
classes.

The most important complexity classes are the classes \textbf{P} and 
\textbf{NP}: 

\begin{itemize}

    \item The class \textbf{P}: This class contains those problems that can be 
solved in a polynomial amount of time.
    
    \item The class \textbf{NP}: The definition of this class looks not at the 
time required to solve a problem, but rather at the time required to verify a 
given solution. The class \textbf{NP} consists of those problems for which a 
given solution can be verified in a polynomial amount of time. Hereby, the term 
\textbf{NP} ''non-deterministic'' means polynomial and is based on a 
calculation model, i.e. on a computer that only exists in theory and can 
''guess'' correct solutions non-deterministically then verify them in 
polynomial time.

\end{itemize}

The class \textbf{P} is contained in the class \textbf{NP}. A well-known 
unsolved problem is the question whether or not $ \textbf{P} \neq \textbf{NP} $ 
is true, i.e. whether or not \textbf{P} is a true subset. An important property 
of the class \textbf{NP} is that it also contains what are known as ''\textbf{NP}-complete''
problems. These are problems that represent the 
class \textbf{NP} as follows: If a ''good'' algorithm for such a 
problem exists, then ''good'' algorithms exist for all problems from 
\textbf{NP}. In particular: if \textbf{P} only contained one complete problem, 
i.e. if a polynomial solution algorithm existed for this problem, then 
\textbf{P}would be equal to \textbf{NP}. In this sense, the \textbf{NP}-complete 
problems are the most difficult problems in \textbf{NP}.

Many cryptographic protocols are formed in such a way that the ''good''
subscribers only have to solve problems from \textbf{P}, whereas a 
perpetrator is faced with problems from \textbf{NP}.

Unfortunately, we do not yet know whether one-way functions actually exist. 
However, we can prove that one-way functions exist if and only if $ \textbf{P} 
\neq \textbf{NP} $ \cite[S.63]{Balcazar1988}.\\

\vskip +3pt
Mathematicians have again and again claimed to have proven the equivalence, e.g.

{\href{http://www.geocities.com/st_busygin/clipat.html}{
http://www.geocities.com/st\_busygin/clipat.html}), 

but so far the claims have always turned out to be false.

A number of algorithms have been suggested for public-key procedures. In many 
cases - although they at first appeared promising - it was discovered that they 
could be solved polynomially. The most famous failed applicant is the knapsack 
with trapdoor, suggested by Ralph Merkle \cite{Merkle1978}.

\newpage
\subsection{Knapsack problem as a basis for public-key procedures}
\index{Knapsack}
\subsubsection{Knapsack problem}

You are given $ n $ objects $ G_1, \dots, G_n $ with the weights $ g_1, \dots 
g_n $ and the values $w_1, \cdots, w_n. $ The aim is to carry away as much as 
possible in terms of value while restricted to an upper weight limit $ g $. You 
therefore need to find a subset of $ \{ G_1, \cdots,G_n\}, $ i.e. $ \{G_{i_1}, 
\dots ,G_{i_k} \}, $ so that $ w_{i_1}+ \cdots +w_{i_k} $ is maximised under the 
condition $  g_{i_1}+ \cdots +g_{i_k} \leq g. $ \par
Such questions are called {\bf NP}-complete problems (not \index{Runtime!not 
polynomial NP} deterministically polynomial) that are difficult to 
calculate.\index{Knapsack}

A special case of the knapsack problem is:\\
Given the natural numbers $ a_1, \dots, a_n $   and $ g .$,
find $ x_1, \dots, x_n \in \{ 0,1\} $  where $ g = \sum_{i=1}^{n}x_i a_i $  
(i.e. where $ g_i = a_i = w_i $ is selected). This problem is also called a  
{\bf 0-1 knapsack problem} and is identified with $ K(a_1, \dots, a_n;g) $.\\

Two 0-1 knapsack problems  $ K(a_1, \dots, a_n;g) $   and  $ K(a'_1, \dots, 
a'_n;g') $  are called congruent if two \index{Coprime} coprime numbers $ w $ 
and $ m $ exist such that
\begin{enumerate}
    \item $ m > \max \{ \sum_{i=1}^n a_i , \sum_{i=1}^n a'_i \}, $

    \item $ g \equiv wg' \mod m, $

    \item $ a_i \equiv w a'_i \mod m $ for all $ i=1, \dots, n.$

\end{enumerate}
 
{\bf Comment:}
Congruent 0-1 knapsack problems have the same solutions.
No quick algorithm is known for clarifying the question whether two 0-1 knapsack 
problems are congruent.

A 0-1 knapsack problem can be solved by testing the $ 2^n $   possibilities for 
$ x_1, \dots, x_n $. The best method requires $ O(2^{n/2}) $  operations, which 
for $ n=100 $  with $ 2^{100} \approx 1.27 \cdot 10^{30} $  and  $ 2^{n/2} 
\approx 1.13 \cdot 10^{15} $ represents an insurmountable hurdle for computers.
However, for special $ a_1, \dots, a_n $   the solution is quite easy to find, 
e.g. for $ a_i = 2^{i-1}. $  The binary representation of $ g $ immediately 
delivers $ x_1, \dots, x_n$. In general, the a 0-1 knapsack problem can be 
solved easily if a \index{Permutation} permutation\footnote{A permutation $\pi$ 
of the numbers $1, \dots, n$ is a change in the order in which these numbers are 
listed. For example, a permutation $\pi$ of $(1,2,3)$ is $(3,1,2),$ i.e. 
$\pi(1) = 3$, $\pi(2) =1$ 
and $\pi(3) = 2$.} 
$ \pi $  of $ 1, \dots, n $  exists with $ a_{\pi (j)} > \sum_{i=1}^{j-1} 
a_{\pi(i)} $. If, in addition, $ \pi $ is the identity, i.e. $ \pi(i)=i $ for $ 
i=1,2,\dots,n, $ then the sequence $ a_1, \dots , a_n $ is said to be 
superincreasing.
The following algorithm solves the knapsack problem with a superincreasing 
sequence in the timeframe of $ O(n). $
\begin{center}

\fbox{\parbox{12cm}{        
\begin{tabbing}
\hspace*{0.5cm} \= \hspace*{0.5cm} \= \hspace*{0.5cm} \= \kill
\>{\bf for} $ i=n $ {\bf to} 1 {\bf do} \\
\>\> {\bf if} $ T\geq a_i $ {\bf then}\\
\>\> \> $ T:=T-s_i $ \\
\>\>\> $ x_i:=1 $ \\
\>\> {\bf else} \\
\>\>\> $ x_i:=0 $ \\
\>{\bf if} $ T=0 $ {\bf then} \\
\>\> $ X:=(x_1, \dots, x_n) $ is the solution. \\
\>{\bf else} \\
\>\> No solution exists.
\end{tabbing}
}}
\end{center}
\vskip +10 pt
{\bf Algorithm 1.} Solving knapsack problems with superincreasing weights
\vskip +20 pt


\subsubsection{Merkle-Hellman knapsack encryption}
\index{Hellman Martin} \index{Merkle} In 1978, Merkle and Hellman 
\cite{Merkle1978} \index{Encryption!Merkle-Hellman} specified a public-key 
encryption procedure that is based on ''defamiliarising'' the easy 0-1 
knapsack problem with a superincreasing sequence into a congruent one with a 
superincreasing sequence. It is a block ciphering that ciphers an $n$-bit 
plaintext each time it runs.
\index{Knapsack!Merkle-Hellman}
More precisely:

\begin{center}
\fbox{\parbox{12cm}{        
Let $ (a_1, \dots, a_n) $ be superincreasing. Let $ m $ and $ w $ be two coprime 
numbers with $ m > \sum_{i=1}^{n} a_i $ and $ 1\leq w \leq m-1. $ Select 
$\bar{w} $ with $ w \bar{w} \equiv 1 \mod m $ the modular inverse of $ w $ and 
set $ b_i:= wa_i \mod m, $ $ 0\leq b_i < m $ for $ i=1, \dots ,n, $ and verify 
whether the sequence $ b_1, \dots b_n $ is not superincreasing. A permutation $ 
b_{\pi (1)}, \dots , b_{\pi(n)} $ of  $ b_1, \dots , b_n $ is then published and 
the inverse permutation $ \mu $ to $ \pi $ is defined secretly. A sender writes 
his/her message in blocks $ (x_1^{(j)}, \dots, x_n^{(j)}) $ of binary numbers $ 
n $ in length, calculates
\[ g^{(j)}:= \sum_{i=1}^n x_{i}^{(j)} b_{\pi(i)} \]
and sends $ g^{(j)}, (j=1,2, \dots). $\par
The owner of the key calculates
\[ G^{(j)}:=\bar{w} g^{(j)} \mod m ,\quad 0 \leq G^{(j)} < m \]
and obtains the $ x_{\mu(i)}^{(j)} \in \{ 0,1\} $ (and thus also the $ x_i^{(j)} 
$) from
\begin{eqnarray*}
G^{(j)} & \equiv & \bar{w} g^{(j)} = \sum_{i=1}^n x_i^{(j)} b_{\pi (i)} \bar{w} 
\equiv \sum_{i=1}^n x_i^{(j)} a_{\pi (i)} \mod m \\
& = & \sum_{i=1}^n x_{\mu (i)}^{(j)} a_{\pi (\mu (i))} = \sum _{i=1}^n x_{\mu 
(i)}^{(j)} a_i \mod m, 
\end{eqnarray*}
by solving the easier 0-1 knapsack problems $ K(a_1,\dots,a_n;G^{(j)}) $ with 
superincreasing sequence $ a_1, \dots,a_n $.
}}
\end{center}
\vskip +10 pt
{\bf Merkle-Hellman procedure} (based on knapsack problems).
\vskip +20 pt



In 1982, \index{Shamir Adi} Shamir \cite{Shamir1982} specified an algorithm for 
breaking the system in polynomial time without solving the general knapsack 
problem. Len \index{Adleman Leonard} Adleman \cite{Adleman1982} and Jeff 
Lagarias \index{Lagarias Jeff} \cite{Lagarias1983} specified an algorithm for 
breaking the twice iterated Merkle-Hellman knapsack encryption procedure in 
polynomial time. Ernst Brickell \index{Brickell Ernst} \cite{Brickell1985} then 
specified an algorithm for breaking multiply iterated Merkle-Hellman knapsack 
encryption procedures in polynomial time. This made this procedure unsuitable as 
an encryption procedure. It therefore delivers a one-way function whose trapdoor 
information (defamiliarisation of the 0-1 knapsack problem) could be discovered 
by a perpetrator.



\subsection{Decomposition into prime factors as a basis for public-key 
procedures}





\subsubsection{The RSA procedure}
\index{RSA} \hypertarget{RSAVerfahren}{} As early as 1978, R. \index{Rivest Ronald} Rivest, \index{Shamir 
Adi} A. Shamir,  \index{Adleman Leonard} L. Adleman \cite{RSA1978} introduced 
the most important asymmetric cryptography procedure to date.  \par


\begin{center}
\fbox{\parbox{12cm}{        
\underline{Key generation:} \vskip + 5pt

Let $ p $ and $ q $ be two different prime numbers and $ N = pq$. Let 
$ e $ be any prime number relative to $ \phi (N) $ \index{Prime 
number!relative}, i.e. $ \ggt (e,\phi (N))=1. $ Using the Euclidean algorithm, 
we calculate the natural number  $ d < \phi (N), $ such that
\[ ed \equiv 1 \mod \phi (N). \]
whereby $ \phi $ is the {\bf Euler phi Function}. 

The output text is divided into blocks and encrypted, whereby each block has a 
binary value $ x^{(j)} \leq N $. \vskip + 5 pt

\underline{Public key:}
\[ N,e. \]
\underline{Private key:}
\[ d. \]
\underline{Encryption:}
\[ y= e_{T} (x) = x^{e} \mod N.\]
\underline{Decryption:}
\[ d_{T} (y) = y^d \mod N. \]
}} % \fbox

\end{center}

\vskip +10 pt
{\bf RSA procedure} (based on the factorisation problem).
\vskip +20 pt
\index{Factorisation problem}
\index{Euler!(phi) function}
{\bf Comment:} 
The Euler phi function is defined as: $ \phi (N)$ is the number of natural 
numbers that do not have a common factor with $ N $ \index{Coprime} {}
$ x \leq N. $ Two natural numbers $ a $ and $ b $ are coprime if 
$ \ggt (a,b)=1. $ 

For the Euler phi function: $ \phi (1)=1, \phi(2)=1,
\phi(3)=2, \phi (4)=2, \phi(6)=2, \phi (10)= 4, \phi (15)=8. $  For example, $ 
\phi (24)=8, $ because
$|\{ x <24 : \ggt (x,24) =1 \}| =|\{1,5,7,11,13,17,19,23\}|. $

If  $ p $ is a prime number, then $ \phi (p)= p-1. $

If we know the various prime factors $ p_1, \dots , p_k $ of $ N, $ then $ \phi 
(N) = N \cdot (1-\frac{1}{p_1}) \,
\cdots \, (1-\frac{1}{p_k}) $\footnote{Further formulas for the Euler phi function are in the 
article \hyperlink{Kap_3_8}{''Introduction to Elementary Number Theory with Examples, chapter 3.8}.}.

In the case of $ N=pq $, $ \phi (N)= pq(1-1/p)(1-1/q) = p(1-1/p)q(1-1/q)=(p-
1)(q-1). $
\\ \vskip +5 pt
\begin{center}
\begin{tabular}{|l|l|l|}\hline
$n$ & $\phi (n) $ & The natural numbers that are coprime to $ n $ and less than 
$ n. $ \\ \hline
1 & 1 & 1  \\
2 & 1 & 1 \\
3 &  2 & 1, 2 \\ 
4 &  2 & 1, 3 \\ 
5 &  4 & 1, 2, 3, 4 \\ 
6 &  2 & 1, 5 \\ 
7 &  6 & 1, 2, 3, 4, 5, 6 \\ 
8 &  4 & 1, 3, 5, 7 \\ 
9 &  6 & 1, 2, 4, 5, 7, 8 \\ 
10 &  4 & 1, 3, 7, 9 \\ 
15 &  8 & 1, 2, 4, 7, 8, 11, 13, 14 \\ \hline
\end{tabular}
\end{center}
\vskip +5 pt
The function $ e_T $  is a one-way function whose trapdoor information is the 
decomposition into primes of $ N $.

At the moment, no algorithm is known that can factorise two prime numbers 
sufficiently quickly for extremely large values (e.g. for several hundred 
decimal places). The quickest algorithms known today \cite{Stinson1995} 
factorise a compound whole number $ N $ in a time period proportional to $ L(N)= 
e^{\sqrt{\ln (N) \ln (\ln (N))}}. $ 
\vskip +5 pt
\begin{center}
\begin{tabular}{|l||l|l|l|l|l|l|}\hline
$N$ & $ 10^{50} $ & $ 10^{100} $ & $ 10^{150} $ & $ 10^{200} $ & $ 10^{250} $ & 
$ 10^{300} $ \\ \hline
$L(N)$ & $ 1.42 \cdot 10^{10} $ &  $ 2.34  \cdot 10^{15} $ &  $ 3.26 \cdot 
10^{19} $ &  $ 1.20 \cdot 10^{23} $ &  $ 1.86 \cdot 10^{26} $ &  $ 1.53 \cdot 
10^{29} $ \\ \hline
\end{tabular}
\end{center}
\vskip +5 pt
As long as no better algorithm is found, this means that values of the order of 
magnitude $ 100 $ to $ 200 $ decimal places are currently safe. Estimates of the 
current computer technology indicate that a number with $100$ decimal places 
could be factorised in approximately two weeks at justifiable cost. Using an 
expensive configuration (e.g. of around 10 million US dollars), a number with 
$150$ decimal places could be factorised in about a year. A $200-$digit number 
should remain impossible to factorise for a long time to come, unless there is a 
mathematical breakthrough. For example, it would take about 1000 years to 
decompose a 200-digit number into prime factors using the existing algorithms; 
this applies even if $ 10^{12} $  operations can be performed per second, which 
is beyond the performance of current technology and would cost billions of 
dollars in development costs. However, you can never be sure that there won't be 
a mathematical breakthrough tomorrow.

To this date, it has not been proved that the problem of breaking RSA is 
equivalent to the factorisation problem. Nevertheless, it is clear that the RSA 
procedure will no longer be safe if the factorisation problem is ''solved''.


\subsubsection{Rabin public-key procedure (1979)}

In this case it has been shown that the procedure \index{Rabin} 
\index{Rabin!public-key} is equivalent to breaking the factorisation problem. 
Unfortunately, this procedure is susceptible to chosen-ciphertext attacks.
\index{Attack!chosen-ciphertext}
\begin{center}
\fbox{\parbox{12cm}{        
Let $ p $ and $ q $ be two different prime numbers with $ p,q\equiv 3 \mod 4 $ 
and $ n = pq.$ Let $ 0\leq B \leq n-1.$ \\
\underline{Public key:}
\[ e=(n,B). \]
\underline{Private key:}
\[ d=(p,q). \]
\underline{Encryption:}
\[ y= e_{T} (x) = x(x+B) \mod n.\]
\underline{Decryption:}
\[ d_{T} (y) = \sqrt{y + B^2/4} -B/2 \mod n. \]
}}
\end{center}

\vskip +10 pt
{\bf Rabin procedure} (based on the factorisation problem).
\vskip +20 pt

Caution:
Because $ p,q \equiv 3 \mod 4 $  the encryption is easy to calculate (if the key 
is known). This is not the case for $ p \equiv 1 \mod 4. $ In addition, the 
encryption function is not injective: There are precisely four different source 
codes that have $ e_T(x) $  as inverse image: $ x,-x-B,\omega (x+B/2)-B/2, -
\omega(x+B/2)-B/2, $ where $ \omega $  is one of the four roots of unity. The 
source codes therefore must be redundant for the encryption to remain unique!!!

Backdoor information is the decomposition into prime numbers of $ n = pq. $ 






       \subsection{The discrete logarithm as a basis for public-key procedures}
Discrete logarithms \index{discrete logarithm} form the basis for a large number of algorithms for public-
key procedures.
\index{Logarithm problem!discrete}





    \subsubsection{The discrete logarithm in $ \Z_p $}
Let $ p $ be a prime number and let $ g \in \Z_p^\ast=\{0,1,\ldots,p-1\} $. Then 
the discrete exponential function base $ g $  is defined as
\[ e_g : k \longrightarrow y:=g^k \mod p, \quad 1\leq k \leq p-1. \]
The inverse function is called a discrete logarithm function $ \log_g $; the 
following holds:
\[ \log_g (g^k) =k. \]
\index{Exponential function!discrete} The problem of the discrete logarithm (in 
$ \Z_p^\ast$) is understood to be as follows:
\[ {\rm Given~ } p,g {\rm ~and~ } y, {\rm~determine~} k {\rm ~such~that~ } 
y=g^k \mod p {\rm .}\]
It is much more difficult to calculate the discrete logarithm than to evaluate 
the discrete exponential function (see 3.4.4).
There are several procedures for calculating the discrete logarithm 
\cite{Stinson1995}:
\vskip + 5pt
\begin{center}
\begin{tabular}{|l|l|}\hline
Name                 &        Complexity \\ \hline \hline
Baby-Step-Giant-Step &         $ O(\sqrt{p}) $ \\ \hline
Silver-Pohlig-Hellman    &    polynomial in $ q, $ the greatest \\
&  prime factor of $ p-1. $ \\ \hline
Index-Calculus &             $ O(e^{(1+o(1)) \sqrt{\ln (p) \ln (\ln (p))}}) $ \\ 
\hline
\end{tabular}
\end{center}
\vskip +5 pt
\index{Silver} \index{Pohlig} \index{Hellman Martin}




    \subsubsection{Diffie-Hellman key agreement}

\index{Key agreement!Diffie-Hellman} \index{Diffie Whitfield} The mechanisms and 
algorithms of classical cryptography only take effect when the subscribers have 
already exchanged the secret key. In classical cryptography, you cannot avoid 
exchanging secrets without encrypting them. Transmission safety here must be 
achieved using non-cryptographic methods. We say that we need a secret channel 
for exchanging secrets. This channel can be realised either physically or 
organisationally. \\
What is revolutionary about modern cryptography is, amongst other things, that 
you no longer need secret channels: You can agree secret keys using non-secret, 
i.e. public channels. \\
One protocol that solves this problems is that of Diffie and Hellman \\

\begin{center}
\fbox{\parbox{12cm}{        
Two subscribers $ A $ and $ B $ want to agree on a joint secret key. \par
Let $ p $ be a prime number and $ g $ a natural number. These two numbers do not 
need to be secret. \\
The two subscribers then select a secret number $ a $ and $ b. $ from which they 
calculate the values $ \alpha = g^{a}\mod p $ and $ \beta = g^b \mod p. $ They 
then exchange the numbers $ \alpha $ and $ \beta $. To end with, the two 
subscribers calculate the received value to the power of their secret value to 
get $ \beta^{a} \mod p $ and $ \alpha^b \mod p. $\\
Thus
\[ \beta^{a} \equiv (g^b)^{a} \equiv g^{ba} \equiv g^{ab} \equiv (g^{a})^b 
\equiv \alpha^b \mod p \]
}}
\end{center}

\vskip +10 pt
{\bf Diffie Hellman} (Key agreement).
\vskip +20 pt


The safety of the {\bf Diffie-Hellman protocol} is closely connected to 
calculating the discrete logarithm mod $p$. It is even thought that these 
problems are equivalent.


    \subsubsection{ElGamal public-key encryption procedure in $ \Z_p^\ast$}
\index{ElGamal!public-key}
By varying the Diffie-Hellman key agreement protocol \index{Encryption!El Gamal 
public-key} slightly, you can obtain an asymmetric encryption algorithm. This 
observation was made by Taher ElGamal.
\begin{center}
\fbox{\parbox{12cm}{        
Let $ p $ be a prime number such that the discrete logarithm in $ \Z_p $ is 
difficult. Let $ \alpha \in \Z_p^\ast $ be a primitive element. Let $ a $ and $ 
\beta = \alpha^{a}  \mod p. $\\
\underline{Public key:}
\[ p,\alpha,\beta. \]
\underline{Private key:}
\[a. \]
Let $ k \in \Z_{p-1} $ be a random number and $ x \in \Z_p^{\ast} $ the 
plaintext. \\
\underline{Encryption:}
\[ e_T(x,k)=(y_1,y_2), \]
where
\[ y_1=\alpha^k \mod p\]
and
\[ y_2 = x\beta^k \mod p.\]
\underline{Decryption:}
\[ d_T(y_1,y_2)= y_2 (y_1^{a})^{-1} \mod p \]
}}
\end{center}


\vskip +10 pt
{\bf ElGamal procedure} (based on the factorisation problem).
\vskip +20 pt




    \subsubsection{Generalised ElGamal public-key encryption procedure}

The discrete logarithm can be generalised in any number of finite \index{Groups} 
groups $ (G, \circ) $. The following provides several properties of $ G, $ that 
make the discrete logarithm problem difficult. \\
\index{Exponential function!calculation}
\paragraph{Calculating the discrete exponential function}
Let $ G $ be a group with the operation $ \circ $ and $ g \in G. $ The 
(discrete) exponential function  base $ g $ is defined as
\[ e_g : {\rm ~N} \ni k \longrightarrow g^k, \quad {\rm for~all~} k \in {\rm N}. \]
where
 \[ \ g^{k}:=\underbrace{g \circ \ldots \circ g}_{k {\rm ~times}}.\]
The exponential function is easy to calculate:
\vskip +20 pt \noindent
{\bf Lemma.}

{\em
  The power $ g^k $ can be calculated in at most $ 2 \log_2 k $ group 
operations.
}
\vskip +10 pt

\begin{Proof}{}
Let $ k=2^n + k_{n-1} 2^{n-1} + \cdots + k_1 2 + k_0 $ be the binary 
representation of $k. $ Then $ n \leq \log_2 (k), $  because $ 2^n \leq k < 
2^{n+1}. $ $ k $ can be written in the form $ k=2k' + k_0 $ with $ k'= 2^{n-1} + 
k_{n-1} 2^{n-2} + \cdots + k_1 $. Thus 
\[ g^k = g^{2k'+k_0}= (g^{k'})^2 g^{k_0} .\]
We therefore obtain $ g^k $ from $ g^{k'} $ by squaring and then multiplying by 
$ g $. The claim is thus proved by induction to $ n. $
\end{Proof}

\vskip +10 pt
{\bf Problem of the discrete logarithm}\index{Logarithm problem!discrete}
\vskip +10 pt
\begin{center}
\fbox{\parbox{12cm}{        
Let $ G $ by a finite group with the operation $ \circ. $ Let $ \alpha \in G $ 
and $ \beta \in H=\{ \alpha^{i}: i\geq 0\}. $ \\
We need to find a unique $ a \in {\rm N} $ with $ 0 \leq a \leq |H| -1 $ and $ \beta 
= \alpha^{a}. $ \\       
We define $ a $ as $ \log_\alpha (\beta). $
}}
\end{center}

\paragraph{Calculating the discrete logarithm }
A simple procedure for calculating the discrete logarithm of a group element, 
that is considerably more efficient than simply trying all possible values for $ 
k, $ is the \index{Baby-Step-Giant-Step} Baby-Step-Giant-Step algorithm.
\begin{theorem}\label{thm-cry-bsgs}[Baby-Step-Giant-Step algorithm]
Let $ G $ be a group and $ g \in G. $ Let $ n $ be the smallest natural number 
with $ |G|\leq n^2. $ Then the discrete logarithm of an element $ h 
\in G $ can be calculated base $ g $ by generating two lists each containing $ n 
$ elements and comparing these lists.\\
In order to calculate these lists, we need $ 2n $ group operations.
\end{theorem}

\begin{Proof}{}
  First create the two lists \\
Giant-Step list: $ \{1,g^n,g^{2n}, \ldots, g^{n \cdot n}\}, $\\
Baby-Step list: $ \{ hg^{-1} , hg^{-2} , \ldots , hg^{-n} \}. $ \par
If $ g^{jn} = hg^{-i}, $ i.e. $ h = g^{i+jn}, $ then the problem is solved. If 
the lists are disjoint, then $ h $ cannot be represented as $ g^{i + jn}, i, 
j\leq n,$. As all powers of $ g $ are thus recorded, the logarithm problem does 
not have a solution.
\end{Proof}

You can use the Baby-Step-Giant-Step algorithm to demonstrate that it is much 
more difficult to calculate the discrete logarithm than to calculate the 
discrete exponential function. If the numbers that occur have approximately 1000 
bits in length, then you only need around 2000 multiplications to calculate $ 
g^k $ but around $ 2^{500} \approx 10^{150} $ operations to calculate the 
discrete logarithm using the Baby-Step-Giant-Step algorithm. \\
In addition to the Baby-Step-Giant-Step algorithm, there are also numerous other 
procedures for calculating the discrete logarithm \cite{Stinson1995}.

\paragraph{The theorem from Silver-Pohlig-Hellman}
In finite abelian groups, the discrete logarithm problem can be reduced to 
groups of a lower order.
\begin{theorem}\label{thm-cry-pohe}[Silver-Pohlig-Hellman]
Let $ G $ be a finite abelian group with $ |G|= p_1^{a_1} p_2^{a_2} \cdot \ldots 
\cdot p_s^{a_s}. $ The discrete logarithm in $ G $ can then be reduced to 
solving logarithm problems in groups of the order $ p_1, \ldots , p_s $.
\end{theorem}

If $ |G| $ contains a ''dominant'' prime factor $ p ,$ then the 
complexity \index{Complexity} of the logarithm problem is approximately
\[ O(\sqrt{p}). \]
Therefore, if the logarithm problem is to be made difficult, the order of the 
group used $ G $ should have a large prime factor. In particular, if the 
discrete exponential function in the group $ \Z_p^{\ast} $ is to be a one-way 
function, then $ p -1 $ must be a large prime factor.




\begin{center}
\fbox{\parbox{12cm}{        
Let $ G $ be a finite group with operation $  \circ, $ and let $ \alpha \in G, $ 
so that the discrete logarithm in $ H =\{ \alpha^{i}: i \geq 0 \} $ is 
difficult, Let $ a $ with $   0 \leq a \leq |H| -1 $ and let $ \beta = 
\alpha^{a}. $\\
\underline{Public key:}
\[ \alpha,\beta. \]
\underline{Private key:}
\[a. \]
Let $ k \in \Z_{|H|} $ be a random number and $ x \in G $ be a plaintext. \\
\underline{Encryption:}
\[ e_T(x,k)=(y_1,y_2), \]
where
\[ y_1=\alpha^k \]
and
\[ y_2 = x\circ \beta^k .\]
\underline{Decryption:}
\[ d_T(y_1,y_2)= y_2\circ (y_1^{a})^{-1}  \]
}}
\end{center}


\vskip +10 pt
{\bf Generalised ElGamal procedure} (based on the factorisation problem).
\vskip +20 pt

\hyperlink{ellcurve}{Elliptic curves} {} provide useful groups for public-key 
encryption procedures.

\newpage
\begin{thebibliography}{99}
\addcontentsline{toc}{subsection}{Bibliography}
           \bibitem[Adleman1982]{Adleman1982} Adleman L.: \index{Adleman Leonard}
           \emph{On breaking the iterated Merkle-Hellman public key 
Cryptosystem.} \\ 
           Advances in Cryptologie, Proceedings of Crypto 82, Plenum Press 1983, 
303-308.

 \bibitem[Balcazar1988]{Balcazar1988}\index{Balcazar 1988} Balcazar J.L., Daaz J., Gabarr\'{} J.: 
           \emph{Structural Complexity I.} \\ 
           Springer Verlag, pp 63.
           
       \bibitem[Brickell1985]{Brickell1985} Brickell E.F.:
           \emph{Breaking Iterated Knapsacks.}  \\
       Advances in Cryptology: Proc. CRYPTO\'84, Lecture Notes in Computer 
Scince, vol. 196, 
           Springer-Verlag, New York, 1985, pp. 342-358.

           \bibitem[Lagarias1983]{Lagarias1983} Lagarias J.C.:
           \emph{Knapsack public key Cryptosystems and diophantine 
Approximation.} \\
           Advances in Cryptologie, Proseedings of Crypto 83, Plenum Press.

           \bibitem[Merkle1978]{Merkle1978} Merkle R. and Hellman M.:
           \emph{Hiding information and signatures in trapdoor knapsacks.}  \\
           IEEE Trans. Information Theory, IT-24, 1978.

       \bibitem[RSA1978]{RSA1978} Rivest R.L., Shamir A. and Adleman L.:
           \emph{A Method for Obtaining Digital Signatures and Public Key 
Cryptosystems.} \\
           Commun. ACM, vol 21, April 1978, pp. 120-126.

           \bibitem[Shamir1982]{Shamir1982} Shamir A.:
           \emph{A polynomial time algorithm for breaking the basic Merkle-
Hellman Cryptosystem.}\\
           Symposium on Foundations of Computer Science (1982), 145-152.
       
       \bibitem[Stinson1995]{Stinson1995} Stinson D.R.:
           \emph{Cryptography.}  \index{Stinson 1995} \\
           CRC Press, Boca Raton, London, Tokyo, 1995.
\end{thebibliography}
\section*{URLs} \addcontentsline{toc}{subsection}{URLs}
\begin{enumerate}
   \item 
\href{http://www.geocities.com/st_busygin/clipat.html}{http://www.geocities.com/st\_busygin/clipat.html }
\end{enumerate}