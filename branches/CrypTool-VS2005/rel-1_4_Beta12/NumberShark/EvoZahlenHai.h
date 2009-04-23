#pragma once

// Potentielle R�ckgabewerte f�r Funktion takeComputerNumber()
const int ZAHLENHAI_TEILER_GEFUNDEN					= 1; // IDENTISCH MIT BOOLSCH 'TRUE'
const int ZAHLENHAI_KEINE_TEILER_GEFUNDEN			= 0; // IDENTISCH MIT BOOLSCH 'FALSE'

#define STR_LAENGE_STRING_TABLE 1000

enum StatusNumber
{
	FREE,
	COMPUTER,
	PLAYER
};

struct ComputerNumbers 
{
	int n; //Anzahl der Zahlen die der Hai jede Runde zieht

	int *pNumbers; // Zeiger auf Numbers
};

class EvoZahlenHai
{
	ComputerNumbers computerNumbers;
	
	
	int *numbers;
	int currentRound;
	int pointsplayer;
	int pointscomputer;
	int usablenumbersleft;
	
	int *optimalNumbers;
	int optimalNumbersCount;
			
public:
	EvoZahlenHai(void);
	~EvoZahlenHai(void);

	EvoZahlenHai(CString);
	int upperLimit;
	CString toString();
	CString getBestWay();
	
	ComputerNumbers getComputerNumbers();
	EvoZahlenHai& operator=(const EvoZahlenHai& Spiel);

	bool checkPlayerNumber(int);	//Eingabe des Spielers wird auf G�ltigkeit kontrolliert
	bool factorLeft(); // Jede Runde wird kontrolliert ob noch teilbare Zahlen vorhanden sind
	bool gameFinished();	//Wenn keine Zahl mehr auf FREE gesetzt ist, ist das Spiel beendet

	void pointsPlayerComputer();	//Die Punkte von Spieler und Hai werden zu der jeweiligen Gesamtpunktezahl zusammenaddiert
	void assignFreeNumbersToComputer();	// Wenn keine teilbaren Zahlen mehr frei sind erh�lt der Computer automatisch die restlichen zahlen
	void init(int);		//Initialiesierung

	int startRound(int);	//wird bei jeder Auswahl einer Zahl gestartet
	int maxPossiblePointsPlayer();	//aktuelle Punktestand vom Spieler + Summe aller verbliebenen Zahlen wird mit der aktuellen H�chstpunktezahl verglichen
	int getCurrentRound(){return currentRound;};	//die aktuelle Runde wird erfasst
	int getPointsPlayer(){return pointsplayer;};	//die Punkte vom Spieler werden erfasst
	int getPointsComputer(){return pointscomputer;};	//die Punkte vom Computer werden erfasst
	int *getNumbers() {return numbers;};	//vom Spieler get�tigte Zahl
	int getUpperLimit() {return upperLimit;};	//die vom Spieler gew�nschte Obergrenze f�r das Spiel
	int takeComputerNumber(int);	//Der Hai sucht sich die Teiler der vom Spieler gew�hlten Zahl heraus	
	int usableNumbersLeft();// Die Anzahl der Zahlen die dem Spieler noch zur Verf�gung stehen wird angezeigt
	int getOptimalNumbersCount() { return optimalNumbersCount; }; // Die Anzahl der beim "optimalen Spiel" gew�hlten Zahlen
	int *getOptimalNumbers() { return optimalNumbers; } // vom Spieler im "optimalen Spiel" gew�hlte Zahlen

	char* itoa_fmt (unsigned long ul_num);

	CString setSeperators(int seperateNumber);

	
};