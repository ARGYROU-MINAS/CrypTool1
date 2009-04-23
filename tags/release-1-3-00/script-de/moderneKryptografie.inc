\setcounter{satz}{0}
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
\newcommand{\ggt}{\text{ggT}}
\newcommand{\kgv}{\text{kgV}}
\newcommand{\Id}{\text{Id}}
\newcommand{\nqcarre}{{\ncarre}_{q^2}}
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
\section{Die mathematischen Ideen hinter der modernen Kryptographie}
%**************************************************************************************************************************
(Oyono R./ Esslinger B., September 2000, Update Nov. 2000)
%--------------------------------------------------------------------------------------------------------------------------
       \subsection{Einwegfunktionen mit Fallt"ur und Komplexit"atsklassen}
%--------------------------------------------------------------------------------------------------------------------------
\index{Kryptographie!moderne} \index{Einwegfunktion}
Eine {\bf Einwegfunktion} \hypertarget{Einwegfunktionen1}{} ist eine effizient zu 
berechnende (injektive) Funktion, deren Umkehrung jedoch nur mit 
extrem hohem Rechenaufwand -- jedoch praktisch unm"oglich -- zu berechnen ist.\par

Etwas genauer formuliert:  Eine Einwegfunktion ist eine Abbildung $ f $ einer Menge $ X $ in eine Menge $ Y, $ so da"s $ f(x) $ f"ur jedes Element $ x $ von $ X $ leicht zu berechnen ist, w"ahrend es f"ur (fast) jedes $ y $ aus $ Y $  praktisch unm"oglich ist, ein Urbild $ x $ (d.h. ein $ x $ mit $ f(x)=y $) zu finden.\par

Ein allt"agliches Beispiel f"ur eine Einwegfunktion ist ein Telefonbuch: die auszuf"uhrende Funktion ist die, einem Namen die entsprechende Telefonnummer zuzuordnen. Da die Namen alphabetisch geordnet sind, ist diese Zuordnung einfach auszuf"uhren. Aber ihre Invertierung, also die Zuordnung eines Namens zu einer gegebenen Nummer, ist offensichtlich schwierig, wenn man nur ein Telefonbuch zur Verf"ugung hat. \par

Einwegfunktionen spielen in der Kryptographie eine entscheidende Rolle. Fast alle kryptographischen Begriffe kann man durch Verwendung des Begriffs Einwegfunktion umformulieren. Als Beispiel betrachten wir die Public-Key-Verschl"usselung \index{Verschl""usselung!Public-Key} (asymmetrische Kryptographie):\par

Jedem Teilnehmer $ T $ des Systems wird ein privater \index{Schl""ussel!privat} \index{Schl""ussel!""offentlich} Schl"ussel $ d_T $   und ein sogenannter "offentlicher Schl"ussel $ e_T $   zugeordnet. Dabei mu"s die folgende Eigenschaft (Public-Key-Eigenschaft) gelten:\\
F"ur einen Gegner, der den "offentlichen Schl"ussel $ e_T $  kennt, ist es praktisch unm"oglich, den privaten Schl"ussel  $ d_T $ zu bestimmen.\par

Zur Konstruktion n"utzlicher Public-Key-Verfahren sucht man also eine Einwegfunktion, die in einer Richtung \glqq einfach\grqq {} zu berechnen, die in der anderen Richtung jedoch \glqq schwer\grqq {} (praktisch unm"oglich) zu berechnen ist, solange eine bestimmte zus"atzliche Information \index{Einwegfunktion!mit Fallt""ur} (Fallt"ur) nicht zur Verf"ugung steht. Mit der zus"atzlichen Information kann die Umkehrung effizient gel"ost werden. Solche Funktionen nennt man {\bf Einwegfunktionen mit Fallt"ur} (trapdoor one-way function). Im obigen Fall ist $ d_T $ die Fallt"ur-Information. \par

Dabei bezeichnet man ein Problem als \glqq einfach\grqq, wenn es in \index{Laufzeit!polynomial} polynomialer Zeit als Funktion der L"ange der Eingabe l"osbar ist. Wenn die L"ange der Eingabe $ n $ Bits betr"agt, so ist die Zeit der Berechnung der Funktion proportional zu $ n^{a}, $ wobei $ a $  eine Konstante ist. Man sagt, da"s die \index{Komplexit""at} Komplexit"at solcher Probleme $ O(n^{a}) $ betr"agt. 

%Ferner sagt man auch, solche Probleme geh"oren der Klasse {\bf P} an. \\

Der Begriff \glqq praktisch unm"oglich\grqq {} ist etwas schwammiger. Allgemein kann man sagen, ein Problem ist \index{Laufzeit!effizient} nicht effizient l"osbar, wenn der zu seiner L"osung ben"otigte Aufwand schneller w"achst als die polynomiale Zeit als Funktion der Gr"o"se der Eingabe. Wenn beispielsweise die L"ange der Eingabe $ n $  Bits betr"agt und die Zeit  zur Berechnung der Funktion proportional zu $ 2^n $ ist, so gilt zur Zeit: die Funktion ist f"ur $n > 80$ praktisch nicht zu berechnen (f"ur $ a=5 $ gilt: ab der L"ange $ n=23 $ ist $ 2^n > n^5 $ und danach w"achst $ 2^n $ auch deutlich schneller ($ 2^{23}=8.388.608, $ $ 23^5= 6.436.343 $)).\par 

Die Entwicklung eines praktisch einsetzbaren Public-Key-Verfahrens h"angt daher von der Entdeckung einer geeigneten Einwegfunktion mit Fallt"ur ab.\par

Um Ordnung in die verwirrende Vielfalt von m"oglichen Problemen und ihre Komplexit"aten zu bringen, fa"st man Probleme mit "ahnlicher Komplexit"at zu Klassen zusammen.

Die wichtigsten Komplexit"atsklassen  sind die Klassen \textbf{P} und \textbf{NP}: 

\begin{itemize}

    \item Die Klasse \textbf{P}: Zu dieser Klasse geh"oren diejenigen Probleme, die mit polynomialem Zeitaufwand l"osbar sind.
    
    \item Die Klasse \textbf{NP}: Bei der Definition dieser Klasse betrachten wir nicht den Aufwand zur L"osung eines Problems, sondern den Aufwand zur Verifizierung einer gegebenen L"osung. Die Klasse \textbf{NP} besteht aus denjenigen Problemen, bei denen die Verifizierung einer gegebenen L"osung mit polynomialem Zeitaufwand m"oglich ist. Dabei bedeutet der Begriff \textbf{NP} \glqq nichtdeterministisch\grqq {} polynomial und bezieht sich auf ein Berechnungsmodell, d.h. auf einen nur in der Theorie existierenden Computer, der richtige L"osungen nichtdeterministisch \glqq raten\grqq {} und dies dann in polynomialer Zeit verifizieren kann.

\end{itemize}

Die Klasse \textbf{P} ist in der Klasse \textbf{NP} enthalten. Ein ber"uhmtes offenes Problem ist die Frage, ob $ \textbf{P} \neq \textbf{NP} $ gilt oder nicht, d.h. ob \textbf{P} eine echte Teilmenge ist oder nicht. Eine wichtige Eigenschaft der Klasse \textbf{NP} ist, da"s sie auch sogenannte \glqq \textbf{NP}-vollst"andige\grqq {} Probleme enth"alt. Dies sind Probleme, welche die Klasse \textbf{NP} im folgenden Sinne vollst"andig repr"asentieren: Wenn es einen \glqq guten\grqq {} Algorithmus f"ur ein solches Problem gibt, dann existieren f"ur alle Probleme aus \textbf{NP} \glqq gute\grqq {} Algorithmen. Insbesondere gilt: wenn auch nur ein vollst"andiges Problem in \textbf{P} l"age, d.h. wenn es einen polynomialen L"osungsalgorithmus f"ur dieses Problem g"abe, so w"are \textbf{P}=\textbf{NP}. In diesem Sinn sind die \textbf{NP}-vollst"andigen Probleme die schwierigsten Probleme in \textbf{NP}.

Viele kryptographische Protokolle sind so gemacht, da"s die \glqq guten\grqq {} Teilnehmer nur Probleme aus \textbf{P} l"osen m"ussen, w"ahrend sich ein Angreifer vor Probleme aus \textbf{NP} gestellt sieht.

Man wei"s leider bis heute nicht, ob es Einwegfunktionen "uberhaupt gibt. Man kann aber zeigen, da"s Einwegfunktionen genau dann existieren, wenn $ \textbf{P} \neq \textbf{NP} $ gilt \cite[S.63]{Balcazar1988}.
\vskip +5pt

Es gab immer wieder die Aussage, jemand habe die "Aquivalenz bewiesen, z.B.

{\href{http://www.geocities.com/st\_busygin/clipat.html}{http://www.geocities.com/st\_busygin/clipat.html}), 

aber bisher erwiesen sich diese Aussagen stets als falsch.

Es wurden eine Reihe von Algorithmen f"ur Public-Key-Verfahren vorgeschlagen. Einige davon erwiesen sich, obwohl sie zun"achst vielversprechend erschienen, als polynomial l"osbar. Der ber"uhmteste durchgefallene Bewerber ist der Knapsack mit Fallt"ur, der von Ralph Merkle \cite{Merkle1978} vorgeschlagen wurde.

%--------------------------------------------------------------------
       \subsection{Knapsackproblem als Basis f"ur Public-Key-Verfahren} \index{Kryptographie!Public-Key}
%--------------------------------------------------------------------
\index{Knapsack}
%--------------------------------------------------------------------
    \subsubsection{Knapsackproblem}
%--------------------------------------------------------------------

Gegeben $ n $ Gegenst"ande $ G_1, \dots, G_n $ mit den Gewichten $ g_1, \dots g_n $ und den Werten $w_1, \cdots, w_n. $ Man soll wertm"a"sig so viel wie m"oglich unter Beachtung einer oberen Gewichtsschranke $ g $ davontragen. Gesucht ist also eine Teilmenge von $ \{ G_1, \cdots,G_n\}, $ etwa $ \{G_{i_1}, \dots ,G_{i_k} \}, $ so da"s  $ w_{i_1}+ \cdots +w_{i_k} $ maximal wird unter der Bedingung $  g_{i_1}+ \cdots +g_{i_k} \leq g. $ \par
Derartige Fragen sind sogenannte {\bf NP}-vollst"andige Probleme (nicht \index{Laufzeit!nicht polynomial NP} deterministisch polynomial), die aufwendig zu berechnen sind.\index{Knapsack}

Ein Spezialfall des Knapsackproblems ist:\\
Gegeben sind die nat"urlichen Zahlen $ a_1, \dots, a_n $   und $ g .$
Gesucht sind  $ x_1, \dots, x_n \in \{ 0,1\} $  mit $ g = \sum_{i=1}^{n}x_i a_i $  (wo also $ g_i = a_i = w_i $ gew"ahlt ist). Dieses Problem hei"st auch  {\bf 0-1-Knapsackproblem} und wird mit $ K(a_1, \dots, a_n;g) $  bezeichnet.\\

Zwei 0-1-Knapsackprobleme  $ K(a_1, \dots, a_n;g) $   und  $ K(a'_1, \dots, a'_n;g') $  hei"sen kongruent, falls es zwei \index{teilerfremd} teilerfremde Zahlen $ w $ und $ m $ gibt, so da"s
\begin{enumerate}
    \item $ m > \max \{ \sum_{i=1}^n a_i , \sum_{i=1}^n a'_i \}, $

    \item $ g \equiv wg' \mod m, $

    \item $ a_i \equiv w a'_i \mod m $ f"ur alle $ i=1, \dots, n.$

\end{enumerate}
 
{\bf Bemerkung:}
Kongruente 0-1-Knapsackprobleme haben dieselben L"osungen.
Ein schneller Algorithmus zur Kl"arung der Frage, ob zwei 0-1-Knapsackprobleme kongruent sind, ist nicht bekannt.

Das L"osen eines 0-1-Knapsackproblems kann durch Probieren der $ 2^n $   M"oglichkeiten f"ur $ x_1, \dots, x_n $   erfolgen. Die beste Methode erfordert $ O(2^{n/2}) $  Operationen, was f"ur $ n=100 $  mit $ 2^{100} \approx 1,27 \cdot 10^{30} $  und  $ 2^{n/2} \approx 1,13 \cdot 10^{15} $ f"ur Computer eine un"uberwindbare H"urde darstellt.
Allerdings ist die L"osung f"ur spezielle $ a_1, \dots, a_n $   recht einfach zu finden, etwa f"ur $ a_i = 2^{i-1}. $  Die bin"are Darstellung von $ g $ liefert unmittelbar $ x_1, \dots, x_n$. Allgemein ist die L"osung des 0-1-Knapsackproblems leicht zu finden, falls eine \index{Permutation} Permutation\footnote{Eine Permutation $\pi$ der Zahlen $1, \dots, n$ ist die Vertauschung der Reihenfolge, in der
diese Zahlen aufgez"ahlt werden. Beispielsweise ist eine Permutation $\pi$ von $(1,2,3)$ gleich $(3,1,2),$ also $\pi(1) = 3$, $\pi(2) =1$ 
und $\pi(3) = 2$.} 
$ \pi $  von $ 1, \dots, n $  mit $ a_{\pi (j)} > \sum_{i=1}^{j-1} a_{\pi(i)} $  existiert. Ist zus"atzlich $ \pi $ die Identit"at, d.h. $ \pi(i)=i $ f"ur $ i=1,2,\dots,n, $ so hei"st die Folge $ a_1, \dots , a_n $ superwachsend.
Der folgende Algorithmus l"ost das Knapsackproblem mit superwachsender Folge im Zeitraum von $ O(n). $
\begin{center}

\fbox{\parbox{12cm}{        
\begin{tabbing}
\hspace*{0.5cm} \= \hspace*{0.5cm} \= \hspace*{0.5cm} \= \kill
\>{\bf for} $ i=n $ {\bf to} 1 {\bf do} \\
\>\> {\bf if} $ T\geq a_i $ {\bf then}\\
\>\> \> $ T:=T-s_i $ \\
\>\>\> $ x_i:=1 $ \\
\>\> {\bf else} \\
\>\>\> $ x_i:=0 $\\
\>{\bf if} $ T=0 $ {\bf then} \\
\>\> $ X:=(x_1, \dots, x_n) $ ist die L"osung. \\
\>{\bf else} \\
\>\> Es gibt keine L"osung.
\end{tabbing}
}}
\end{center}
\vskip +10 pt
{\bf Algorithmus 1.} L"osen von Knapsackproblemen mit superwachsenden Gewichten
\vskip +20 pt


%--------------------------------------------------------------------
    \subsubsection{Merkle-Hellman Knapsack Verschl"usselung}
%--------------------------------------------------------------------
\index{Hellman Martin} \index{Merkle} 1978 gaben Merkle und Hellman \cite{Merkle1978} \index{Verschl""usselung!Merkle-Hellman} ein Public-Key-Verschl"usselungs-Verfahren an, das darauf beruht, das leichte 0-1-Knapsackproblem mit einer superwachsenden Folge in ein kongruentes mit einer nicht superwachsenden Folge zu \glqq verfremden\grqq. Es ist eine Blockchiffrierung, die bei jedem Durchgang einen $n$ Bit langen Klartext chiffiert.
\index{Knapsack!Merkle-Hellman}
Genauer:

\begin{center}
\fbox{\parbox{12cm}{        
Es sei $ (a_1, \dots, a_n) $ superwachsend. Seien $ m $ und $ w $ zwei teilerfremde Zahlen mit $ m > \sum_{i=1}^{n} a_i $ und $ 1\leq w \leq m-1. $ W"ahle $\bar{w} $ mit $ w \bar{w} \equiv 1 \mod m $ die modulare Inverse von $ w $ und setze $ b_i:= wa_i \mod m, $ $ 0\leq b_i < m $ f"ur $ i=1, \dots ,n, $ und pr"ufe, ob die Folge $ b_1, \dots b_n $ nicht superwachsend ist. Danach wird eine Permutation $ b_{\pi (1)}, \dots , b_{\pi(n)} $ von $ b_1, \dots , b_n $ publiziert und insgeheim die zu $ \pi $ inverse Permutation $ \mu $ festgehalten. Ein Sender schreibt seine Nachricht in Bl"ocke $ (x_1^{(j)}, \dots, x_n^{(j)}) $ von Bin"arzahlen der L"ange $ n $ und bildet
\[ g^{(j)}:= \sum_{i=1}^n x_{i}^{(j)} b_{\pi(i)} \]
und sendet $ g^{(j)}, (j=1,2, \dots). $\par
Der Schl"usselinhaber bildet
\[ G^{(j)}:=\bar{w} g^{(j)} \mod m ,\quad 0 \leq G^{(j)} < m \]
und verschafft sich die $ x_{\mu(i)}^{(j)} \in \{ 0,1\} $ (und somit auch die $ x_i^{(j)} $) aus
\begin{eqnarray*}
G^{(j)} & \equiv & \bar{w} g^{(j)} = \sum_{i=1}^n x_i^{(j)} b_{\pi (i)} \bar{w} \equiv \sum_{i=1}^n x_i^{(j)} a_{\pi (i)} \mod m \\
& = & \sum_{i=1}^n x_{\mu (i)}^{(j)} a_{\pi (\mu (i))} = \sum _{i=1}^n x_{\mu (i)}^{(j)} a_i \mod m, 
\end{eqnarray*}
indem er die leichten 0-1-Knapsackprobleme $ K(a_1,\dots,a_n;G^{(j)}) $ mit superwachsender Folge $ a_1, \dots,a_n $ l"ost.
}}
\end{center}
\vskip +10 pt
{\bf Merkle-Hellman Verfahren} (auf Knapsackproblemen basierend).
\vskip +20 pt



1982 gab \index{Shamir Adi} Shamir \cite{Shamir1982} einen Algorithmus zum Brechen des Systems in polynomialer Zeit an, ohne das allgemeine Knapsackproblem zu l"osen. Len \index{Adleman Leonard} Adleman \cite{Adleman1982} und Jeff Lagarias \index{Lagarias Jeff} \cite{Lagarias1983} gaben einen Algorithmus zum Brechen des 2-fachen iterierten Merkle-Hellman-Knapsack Verschl"usselungsverfahrens in polynomialer Zeit an. Ernst Brickell \index{Brickell Ernst} \cite{Brickell1985} gab schlie"slich einen Algorithmus zum Brechen des mehrfachen iterierten Merkle-Hellman-Knapsack Verschl"usselungsverfahren in polynomialer Zeit an. Damit war dieses Verfahren als Verschl"usselungsverfahren ungeeignet. Dieses Verfahren liefert also eine Einwegfunktion, deren Fallt"ur-Information (Verfremden des 0-1-Knapsackproblems) durch einen Gegner entdeckt werden k"onnte.



%---------------------------------------------------------------------
      \subsection{Primfaktorzerlegung als Basis f"ur Public-Key-Verfahren}
%--------------------------------------------------------------------






%--------------------------------------------------------------------
    \subsubsection{Das RSA--Verfahren}
%--------------------------------------------------------------------
\index{RSA} \hypertarget{RSAVerfahren}{} Bereits 1978 stellten R. \index{Rivest Ronald} Rivest, \index{Shamir Adi} A. Shamir,  \index{Adleman Leonard} L. Adleman \cite{RSA1978} das bis heute wichtigste 
asymmetrische Kryptographie-Verfahren vor.  \par

\index{Faktorisierungsproblem}
\index{Eulersche Phi-Funktion}
\begin{center}
\fbox{\parbox{12cm}{        
\underline{Schl"usselgenerierung:} \vskip + 5pt
Seien $p$ und $q$ zwei verschiedene Primzahlen und $N=pq.$ Sei $e$ eine frei w"ahlbare, zu $ \phi (N) $ \index{Primzahlen!relative} relative Primzahl, d.h. $ \ggt (e,\phi (N))=1. $ Mit dem Euklidschen Algorithmus berechnet man die nat"urliche Zahl  $ d < \phi (N), $ so da"s gilt

\[ ed \equiv 1 \mod \phi (N). \]
Dabei ist $ \phi $ die {\bf Eulersche Phi-Funktion}. 

Der Ausgangstext wird in Bl"ocke zerlegt und verschl"usselt, wobei jeder Block einen bin"aren Wert $ x^{(j)} \leq N $ hat. \vskip + 5 pt

\underline{"Offentlicher Schl"ussel:}
\[ N,e. \]
\underline{Privater Schl"ussel:}
\[ d. \]
\underline{Verschl"usselung:}
\[ y= e_{T} (x) = x^{e} \mod N.\]
\underline{Entschl"usselung:}
\[ d_{T} (y) = y^d \mod N \]
}}
\end{center}

\vskip +10 pt
{\bf RSA-Verfahren} (auf dem Faktorisierungsproblem basierend).
\vskip +20 pt

{\bf Bemerkung:} 
Die Eulersche Phi-Funktion ist definiert duch: $ \phi (N)$ ist die  Anzahl der zu $ N $ \index{teilerfremd} {} teilerfremden nat"urlichen Zahlen 
$ x \leq N. $ Zwei nat"urliche Zahlen $ a $ und $ b $ \index{teilerfremd} sind teilerfremd, falls $ \ggt (a,b)=1. $ 

F"ur die Eulersche Phi-Funktion gilt: $ \phi (1)=1,~\phi(2)=1,
~\phi(3)=2, ~\phi (4)=2, ~\phi(6)=2, ~\phi (10)= 4, ~\phi (15)=8. $

Zum Beispiel ist $ \phi (24)=8, $ weil 
$|\{ x <24 : \ggt (x,24) =1 \}| =|\{1,5,7,11,13,17,19,23\}|. $

Ist  $ p $ eine Primzahl, so gilt $ \phi (p)= p-1. $

Kennt man die verschiedenen Primfaktoren  $ p_1, \dots , p_k $ von $ N, $ so ist $ \phi (N) = N \cdot (1-\frac{1}{p_1}) \,
\cdots \, (1-\frac{1}{p_k}) $\footnote{Weitere Formeln finden sich in den
Artikel \hyperlink{Kapitel_3_8}{\glqq Einf"uhrung in die elementare Zahlentheorie
mit Beispielen\grqq, Kap. 3.8}.}.

Im Spezialfall $ N=pq $ ist $ \phi (N)= pq(1-1/p)(1-1/q) = p(1-1/p)q(1-1/q)=(p-1)(q-1).$
\\ \vskip +5 pt
\begin{center}
\begin{tabular}{|l|l|l|}\hline
$n$ & $\phi (n) $ & Die zu $ n $ teilerfremden nat"urlichen Zahlen kleiner $ n. $ \\ \hline
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
Die Funktion $ e_T $  ist eine Einwegfunktion, deren Fallt"ur-Information die Primfaktorzerlegung von $ N $ ist.

Zur Zeit ist kein Algorithmus bekannt, der das Produkt zweier Primzahlen bei sehr gro"sen Werten geeignet schnell
zerlegen kann (z.B. bei mehreren hundert Dezimalstellen). Die heute schnellsten bekannten Algorithmen \cite{Stinson1995} zerlegen eine 
zusammengesetzte ganze Zahl $ N $ in einem Zeitraum proportional zu  
$ L(N)= e^{\sqrt{\ln (N) \ln (\ln (N))}}. $ 
%(z.B. f"ur $ N=10^{100} $ ist $ L(N)= 2,34154 \cdot 10^{15}$).
\vskip +5 pt
\begin{center}
\begin{tabular}{|l||l|l|l|l|l|l|}\hline
$N$ & $ 10^{50} $ & $ 10^{100} $ & $ 10^{150} $ & $ 10^{200} $ & $ 10^{250} $ & $ 10^{300} $ \\ \hline
$L(N)$ & $ 1,42 \cdot 10^{10} $ &  $ 2,34  \cdot 10^{15} $ &  $ 3,26 \cdot 10^{19} $ &  $ 1,20 \cdot 10^{23} $ &  $ 1,86 \cdot 10^{26} $ &  $ 1,53 \cdot 10^{29} $ \\ \hline
\end{tabular}
\end{center}
\vskip +5 pt 
Solange kein besserer Algorithmus gefunden wird, hei"st dies, da"s Werte der Gr"o"senordnung $ 100 $ bis $ 200 $ 
Dezimalstellen zur Zeit sicher sind. Einsch"atzungen der aktuellen Computertechnik besagen, da"s eine Zahl mit $100$ 
Dezimalstellen bei vertretbaren Kosten in etwa zwei Wochen zerlegt werden k"onnte. Mit einer teuren Konfiguration 
(z.B. im Bereich von 10 Millionen US-Dollar) k"onnte eine Zahl mit $150$ Dezimalstellen in etwa einem Jahr zerlegt werden. 
Eine $200-$stellige Zahl d"urfte noch f"ur eine sehr lange Zeit unzerlegbar bleiben, falls es zu keinem mathematischen 
Durchbruch kommt. Zum Beispiel w"urde es etwa 1000 Jahre dauern, um eine 200-stellige Zahl mit den bestehenden Algorithmen in 
Primfaktoren zu zerlegen; dies gilt selbst dann, wenn $ 10^{12} $  Operationen pro Sekunde ausgef"uhrt werden k"onnten, 
was jenseits der Leistung der heutigen Technik liegt und in der Entwicklung Milliarden von Dollar kosten w"urde. Da"s es aber
nicht doch schon morgen zu einem mathematischen Durchbruch kommt, kann man nie ausschlie"sen.

Bewiesen ist bis heute nicht, da"s das Problem, RSA zu brechen "aquivalent zum Faktorisierungsproblem \index{Faktorisierungsproblem}
ist. Es ist aber klar, dass wenn das Faktorisierungsproblem \glqq gel"ost\grqq {} ist, dass dann das RSA-Verfahren nicht mehr sicher ist.




%--------------------------------------------------------------------
    \subsubsection{Rabin-Public-Key-Verfahren (1979)}
%--------------------------------------------------------------------

F"ur \index{Rabin} \index{Rabin!Public-Key} dieses Verfahren konnte gezeigt werden, da"s es "aquivalent zum Brechen des Faktorisierungsproblems ist. Leider ist dieses Verfahren anf"allig gegen chosen-ciphertext-Angriffe.
\index{Angriff!chosen-ciphertex}
\begin{center}
\fbox{\parbox{12cm}{        
Seien $ p $ und $ q $ zwei verschiedene Primzahlen mit $ p,q\equiv 3 \mod 4 $ und $ n = pq.$ Sei $ 0\leq B \leq n-1.$ \\
\underline{"Offentlicher Schl"ussel:}
\[ e=(n,B). \]
\underline{Privater Schl"ussel:}
\[ d=(p,q). \]
\underline{Verschl"usselung:}
\[ y= e_{T} (x) = x(x+B) \mod n.\]
\underline{Entschl"usselung:}
\[ d_{T} (y) = \sqrt{y + B^2/4} -B/2 \mod n. \]
}}
\end{center}

\vskip +10 pt
{\bf Rabin-Verfahren} (auf dem Faktorisierungsproblem basierend).
\vskip +20 pt

Vorsicht:
Wegen $ p,q \equiv 3 \mod 4 $  ist die Verschl"usselung (mit Kenntnis des Schl"ussels) leicht  zu berechnen. Dies ist nicht der Fall f"ur $ p \equiv 1 \mod 4. $ Au"serdem ist die Verschl"usselungsfunktion nicht injektiv: Es gibt genau vier verschiedene Quellcodes, die $ e_T(x) $  als Urbild besitzen $ x,-x-B,\omega (x+B/2)-B/2, -\omega(x+B/2)-B/2, $ dabei ist  $ \omega $  eine der vier Einheitswurzeln. Es mu"s also eine  Redundanz der Quellcodes geben, damit die Entschl"usselung trotzdem eindeutig bleibt!!!

Hintert"ur-Information ist die Primfaktorzerlegung von $ n = pq. $ 






%--------------------------------------------------------------------
       \subsection{Der diskrete Logarithmus als Basis f"ur Public-Key-Verfahren}
%--------------------------------------------------------------------
Diskrete Logarithmen\index{Logarithmusproblem!diskret} sind  Grundlagen f"ur eine gro"se Anzahl von Algorithmen von Public-Key-Verfahren.





%--------------------------------------------------------------------
    \subsubsection{Der diskrete Logarithmus in $ \Z_p^* $}
%--------------------------------------------------------------------
Sei $ p $ eine Primzahl, und sei $g$ ein Erzeuger der zyklische multiplikative Gruppe $ \Z_p^\ast=\{1,\ldots,p-1\} $. Dann ist die diskrete Exponentialfunktion zur Basis $ g $  definiert durch
\[ e_g : k \longrightarrow y:=g^k \mod p, \quad 1\leq k \leq p-1. \]
Die Umkehrfunktion wird diskrete Logarithmusfunktion $ \log_g $ genannt; es gilt
\[ \log_g (g^k) =k. \]
\index{Exponentialfunktion!diskrete} Unter dem Problem des diskreten Logarithmus (in $ \Z_p^\ast$) versteht man das folgende:
\[ \text{Gegeben } p,g \text{~(ein Erzeuger der Gruppe } \Z_p^* \text{) und } y, \text{ bestimme } k \text{ so, da"s } y=g^k \mod p \text{ gilt.}\]
Die Berechnung des diskreten Logarithmus ist viel schwieriger als die Auswertung der diskreten Exponentialfunktion (siehe 3.4.4).
Es gibt viele Verfahren zur Berechung des diskreten Logarithmus \cite{Stinson1995}:
\vskip + 5pt
\begin{center}
\begin{tabular}{|l|l|}\hline
Name                 &        Komplexit"at \\ \hline \hline
Baby-Step-Giant-Step &         $ O(\sqrt{p}) $ \\ \hline
Silver-Pohlig-Hellman    &    polynomial in $ q, $ dem gr"o"sten \\
&  Primteiler von $ p-1. $ \\ \hline
Index-Calculus &             $ O(e^{(1+o(1)) \sqrt{\ln (p) \ln (\ln (p))}}) $ \\ \hline
\end{tabular}
\end{center}
\vskip +5 pt
%Damit der diskrete Logarithmus eine  gute Einwegfunktion wird, sollte man $ p $ so w"ahlen,  da"s $ p-1 $ ein gro"ser Primtei%ler besitzt. 
\index{Silver} \index{Pohlig} \index{Hellman Martin}




%--------------------------------------------------------------------
    \subsubsection{Diffie-Hellman-Schl"usselvereinbarung}
%--------------------------------------------------------------------

\index{Schl""usselvereinbarung!Diffie-Hellman} \index{Diffie Whitfield} Die Mechanismen und Algorithmen der klassischen Kryptographie greifen erst dann, wenn die Teilnehmer bereits den geheimen Schl"ussel ausgetauscht haben. Im Rahmen der klassischen Kryptographie  f"uhrt kein Weg daran vorbei, da"s geheimnisse kryptographisch ungesichert ausgetauscht werden m"ussen. Die Sicherheit der "Ubertragung mu"s hier durch nicht-kryptographische Methoden erreicht werden. Man sagt dazu, da"s man zum Austausch der Geheimnisse einen geheimen Kanal braucht; dieser kann physikalisch oder organisatorisch realisiert sein. \\
Das revolution"are der modernen Kryptographie ist unter anderem, da"s man keine geheimen Kan"ale mehr braucht: Man kann geheime Schl"ussel "uber nicht-geheime, also "offentliche Kan"ale vereinbaren. \\
Ein Protokoll, das dieser Problem l"ost, ist das von Diffie und Hellman \\

\begin{center}
\fbox{\parbox{12cm}{   
Zwei Teilnehmer $ A $ und $ B $ wollen einen gemeinsamen geheimen Schl"ussel vereinbaren. \par    
Sei $ p $ eine Primzahl und $ g $ eine nat"urliche Zahl. Diese beide Zahlen m"ussen nicht geheim sein. \\
Zun"achst w"ahlen sich die beiden Teilnehmer je eine geheime Zahl $ a $ bzw. $ b. $ Daraus bilden sie die Werte $ \alpha = g^{a}\mod p $ und $ \beta = g^b \mod p. $ Dann werden die Zahlen $ \alpha $ und $ \beta $ ausgetauscht. Schliesslich potenziert jeder den erhaltenen Wert mit seiner geheimen Zahl und erh"alt $ \beta^{a} \mod p $ bzw. $ \alpha^b \mod p. $\\
Damit gilt
\[ \beta^{a} \equiv (g^b)^{a} \equiv g^{ba} \equiv g^{ab} \equiv (g^{a})^b \equiv \alpha^b \mod p \]
}}
\end{center}

\vskip +10 pt
{\bf Diffie Hellman} (Schl"usselvereinbarung).
\vskip +20 pt


Die Sicherheit des {\bf Diffie-Hellman-Protokolls} h"angt eng mit der Berechnung der diskreten Logarithmus modulo $p$ zusammen. Es wird sogar vermutet, da"s diese Probleme "aquivalent sind.


%--------------------------------------------------------------------
    \subsubsection{ElGamal-Public-Key-Verschl"usselungsverfahren in $ \Z_p^\ast$}
%--------------------------------------------------------------------
\index{ElGamal!Public-Key}
Indem man das Diffie-Hellman Schl"usselvereinbarungsprotokoll \index{Verschl""usselung!El Gamal-Public-Key} leicht variiert, kann man einen asymmetrischen Verschl"usselungsalgorithmus erhalten. Diese Beobachtung geht auf Taher ElGamal zur"uck.
\begin{center}
\fbox{\parbox{12cm}{        
Sei $ p $ eine Primzahl, so da"s der diskrete Logarithmus in $ \Z_p $ schwer ist. Sei $ \alpha \in \Z_p^\ast $ ein primitives Element. Sei $ a $ und $ \beta = \alpha^{a}  \mod p. $\\
\underline{"Offentlicher Schl"ussel:}
\[ p,\alpha,\beta. \]
\underline{Privater Schl"ussel:}
\[a. \]
Sei $ k \in \Z_{p-1} $ eine zuf"allige Zahl und $ x \in \Z_p^{\ast} $ der Klartext. \\
\underline{Verschl"usselung:}
\[ e_T(x,k)=(y_1,y_2), \]
wobei
\[ y_1=\alpha^k \mod p,\]
und
\[ y_2 = x\beta^k \mod p.\]
\underline{Entschl"usselung:}
\[ d_T(y_1,y_2)= y_2 (y_1^{a})^{-1} \mod p. \]
}}
\end{center}


\vskip +10 pt
{\bf ElGamal Verfahren} (auf das diskrete Logarithmusproblem basierend).
\vskip +20 pt




%----------------------------------------------------------------------------------------------------------------------------------------------------------
    \subsubsection{Verallgemeinertes ElGamal-Public-Key-Verschl"usselungsverfahren }
%----------------------------------------------------------------------------------------------------------------------------------------------------------

Den diskreten Logarithmus kann man in beliebigen endlichen \index{Gruppen} Gruppen $ (G, \circ) $ verallgemeinern. Im folgenden geben wir einige Eigenschaften "uber die Gruppe $ G, $ damit das diskrete Logarithmusproblem schwierig wird. \\
\index{Exponentialfunktion!Berechnung}
\paragraph{Berechnung der diskreten Exponentialfunktion}
Sei $ G $ eine Gruppe mit der Operation $ \circ $ und $ g \in G. $ Die (diskrete) Exponentialfunktion  zur Basis $ g $ ist definiert durch
\[e_g: \N \ni k \longrightarrow g^k, \quad \text{ f"ur alle } k \in \N. \]
Dabei definiert man
 \[ \ g^{k}:=\underbrace{g \circ \ldots \circ g}_{k \text{ mal}}.\]
Die Exponentialfunktion ist leicht zu berechnen:
% \begin{lemma}
\vskip +20 pt \noindent
{\bf Lemma.}

{\em
  Die Potenz $ g^k $ kann in h"ochstens $ 2 \log_2 k $ Gruppenoperationen berechnet werden.
}
% \end{lemma}
\vskip +10 pt

\begin{Beweis}{}
Sei $ k=2^n + k_{n-1} 2^{n-1} + \cdots + k_1 2 + k_0 $ die Bin"ardarstellung von $k. $ Dann ist $ n \leq \log_2 (k), $  denn $ 2^n \leq k < 2^{n+1}. $ $ k $ kann in der Form $ k=2k' + k_0 $ mit $ k'= 2^{n-1} + k_{n-1} 2^{n-2} + \cdots + k_1 $ geschrieben werden. Es folgt 
\[ g^k = g^{2k'+k_0}= (g^{k'})^2 g^{k_0} .\]
Man erh"alt also $ g^k $ aus $ g^{k'} $ indem man einmal quadriert und eventuel mit $ g $ multipliziert. Damit folgt die Behauptung durch Induktion nach $ n. $
\end{Beweis}

\vskip +10 pt
{\bf Problem des diskreten Logarithmus'}
\vskip +10 pt
\begin{center}
\fbox{\parbox{12cm}{ 
Sei $ G $ eine endliche Gruppe mit der Operation $ \circ. $ Sei $ \alpha \in G $ und $ \beta \in H=\{ \alpha^{i}: i\geq 0\}. $ \\
Gesucht ist der eindeutige $ a \in \N $ mit $ 0 \leq a \leq |H| -1 $ und $ \beta = \alpha^{a}. $ \\       
Wir bezeichen $ a $ mit $ \log_\alpha (\beta). $
}}
\end{center}

\paragraph{Berechung des diskreten Logarithmus'}
Ein einfaches Verfahren zur Berechnung des diskreten Logarithmus' eines Gruppenelements, das wesentlich effizienter ist als das blo"se Durchprobieren aller m"oglichen Werte f"ur $ k, $ ist der \index{Baby-Step-Giant-Step} Baby-Step-Giant-Step-Algorithmus.
\begin{satz}[Baby-Step-Giant-Step-Algorithmus]\label{thm-cry-bsgs}
Sei $ G $ eine Gruppe  und $ g \in G. $ Sei $ n $ die kleinste nat"urliche Zahl mit $ |G|\leq n^2. $ Dann kann der diskrete Logarithmus eines Elements $ h 
\in G $ zur Basis $ g $ berechnet werden, indem man zwei Listen mit jeweils $ n $ Elementen erzeugt und diese Listen vergleicht.\\
Zur Berechnung dieser Listen braucht man $ 2n $ Gruppenoperationen.
\end{satz}

\begin{Beweis}{}
  Zuerst bilde man die zwei Listen \\
Giant-Step-Liste: $ \{1,g^n,g^{2n}, \ldots, g^{n \cdot n}\}, $\\
Baby-Step-Liste: $ \{ hg^{-1} , hg^{-2} , \ldots , hg^{-n} \}. $ \par
Falls $ g^{jn} = hg^{-i}, $ also $ h = g^{i+jn}, $ so ist das Problem gel"ost. Falls die Listen disjunkt sind, so ist $ h $ nicht als $ g^{i + jn}, i, j\leq n,$ darstellbar. Da dadurch alle Potenzen von $ g $ erfa"st werden, hat das Logarithmusproblem keine L"osung.
\end{Beweis}

Man kann sich mit Hilfe des Baby-Step-Giant-Step-Algorithmus klar machen, da"s die Berechnung des diskreten Logaithmus' sehr viel schwieriger ist als die Berechnung der diskreten Exponentialfunktion. Wenn die auftretenden Zahlen etwa 1000 Bit L"ange haben, so ben"otigt man zur Berechnung von $ g^k $ nur etwa 2000 Multiplikationen, zur Berechnung des diskreten Logarithmus' mit dem Baby-Step-Giant-Step-Algorithmus aber etwa $ 2^{500} \approx 10^{150} $ Operationen. \\
Neben dem Baby-Step-Giant-Step-Algorithmus gibt es noch zahlreiche andere Verfahren zur Berechnung des diskreten Logarithmus' \cite{Stinson1995}.

\paragraph{Der Satz von Silver-Pohlig-Hellman}
In endlichen abelschen Gruppen l"a"st sich das  diskrete Logarithmusproblem in Gruppen kleinerer Ordnung reduzieren.
\begin{satz}[Silver-Pohlig-Hellman]\label{thm-cry-pohe}
Sei $ G $ eine endliche abelsche Gruppe mit $ |G|= p_1^{a_1} p_2^{a_2} \cdot \ldots \cdot p_s^{a_s}. $ Dann l"a"st sich das diskrete Logarithmusproblem in $ G $ auf das L"osen von Logarithmenproblemen in Gruppen der Ordnung $ p_1, \ldots , p_s $ zur"uckf"uhren.
\end{satz}

Enth"alt $ |G| $ eine \glqq dominanten\grqq {} Primteiler $ p ,$ so ist die Komplexit"at \index{Komplexit""at} des Logarithmenproblem ungef"ahr
\[ O(\sqrt{p}). \]
Wenn also das Logarithmusproblem schwer sein soll, so mu"s die Ordnung der verwendeten Gruppe $ G $ einen gro"sen Primteiler haben. Insbesondere gilt, wenn die diskrete Exponentialfunktion in der Gruppe $ \Z_p^{\ast} $ eine Einwegfunktion sein soll, so mu"s $ p -1 $ einen gro"sen Primteiler haben.



%%Unter geeigneten Voraussetzung "uber die Gruppe $ G $ kann der diskrete Logarithmus schwierig werden. Dies ist Grundbaustein f"ur das verallgemeinerte El% Gamal-Public-Key-Verfahren.

\begin{center}
\fbox{\parbox{12cm}{    
Sei $ G $ eine endliche Gruppe  mit Operation $  \circ, $ und sei $ \alpha \in G, $ so da"s der diskrete Logarithmus in $ H =\{ \alpha^{i}: i \geq 0 \} $ schwer ist. Sei $ a $ mit $   0 \leq a \leq |H| -1 $ und sei $ \beta = \alpha^{a}. $\\
\underline{"Offentlicher Schl"ussel:}
\[ \alpha,\beta. \]
\underline{Privater Schl"ussel:}
\[a. \]
Sei $ k \in \Z_{|H|} $ eine zuf"allige Zahl und $ x \in G $ ein Klartext. \\
\underline{Verschl"usselung:}
\[ e_T(x,k)=(y_1,y_2), \]
wobei
\[ y_1=\alpha^k, \]
und
\[ y_2 = x\circ \beta^k .\]
\underline{Entschl"usselung:}
\[ d_T(y_1,y_2)= y_2\circ (y_1^{a})^{-1}.  \]
}}
\end{center}


\vskip +10 pt
{\bf Verallgemeinertes ElGamal Verfahren} (auf das diskrete Logarithmusproblem basierend).
\vskip +20 pt

\hyperlink{ellcurve}{Elliptische Kurven} {} liefern n"utzliche Gruppen f"ur Public-Key-Verschl"usselungsverfahren.

\newpage
\addcontentsline{toc}{subsection}{Literaturverzeichnis}
\begin{thebibliography}{99}
           
           \bibitem[Adleman1982]{Adleman1982} Adleman L.: \index{Adleman Leonard}
           \emph{On breaking the iterated Merkle-Hellman public key Cryptosystem.} \\ 
           Advances in Cryptologie, Proceedings of Crypto 82, Plenum Press 1983, 303-308.

 \bibitem[Balcazar1988]{Balcazar1988} Balcazar J.L., Daaz J., Gabarr\'{} J.: \index{Balcazar 1988}
           \emph{Structural Complexity I.} \\ 
           Springer Verlag, pp 63.
           
       \bibitem[Brickell1985]{Brickell1985} Brickell E.F.:
           \emph{Breaking Iterated Knapsacks.}  \\
       Advances in Cryptology: Proc. CRYPTO\'84, Lecture Notes in Computer Scince, vol. 196, 
           Springer-Verlag, New York, 1985, pp. 342-358.

           \bibitem[Lagarias1983]{Lagarias1983} Lagarias J.C.:
           \emph{Knapsack public key Cryptosystems and diophantine Approximation.} \\
           Advances in Cryptologie, Proseedings of Crypto 83, Plenum Press.

           \bibitem[Merkle1978]{Merkle1978} Merkle R. and Hellman M.:
           \emph{Hiding information and signatures in trapdoor knapsacks.}  \\
           IEEE Trans. Information Theory, IT-24, 1978.

       \bibitem[RSA1978]{RSA1978} Rivest R.L., Shamir A. and Adleman L.:\index{RSA}\index{Shamir Adi}
           \emph{A Method for Obtaining Digital Signatures and Public-Key Cryptosystems.} \\
           Commun. ACM, vol 21, April 1978, pp. 120-126.

           \bibitem[Shamir1982]{Shamir1982} Shamir A.:
           \emph{A polynomial time algorithm for breaking the basic Merkle-Hellman Cryptosystem.}\\
           Symposium on Foundations of Computer Science (1982), 145-152.
       
       \bibitem[Stinson1995]{Stinson1995} Stinson D.R.:
           \emph{Cryptography.}  \index{Stinson 1995} \\
           CRC Press, Boca Raton, London, Tokyo, 1995.
\end{thebibliography}
\addcontentsline{toc}{subsection}{URLs}
\section*{URLs}
\begin{enumerate}
   \item \href{http://www.geocities.com/st\_busygin/clipat.html}{http://www.geocities.com/st\_busygin/clipat.html }
\end{enumerate}