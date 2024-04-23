/**********************************************************/
/* Autor: Kasim Mermer                                    */
/* Datum: 13.01.2016									  */
/* Projekt: P13A1										  */
/* Beschreibung: Stätde raten							  */
/**********************************************************/
#define _CRT_SECURE_NO_WARNINGS		// fehlermeldung vermeiden
#include <time.h>		// bibliotheken einbinden
#include <stdio.h>		
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include"fhswf_service.h"	

#define DATNAME "test.bin"		// meine datei die cih öffnen möchte
#define LAENGE 25
#define GROESSE 20

//Deklaration Prototypen
int pruefen(char[GROESSE]);
int lesen(int);
int schreiben(void);
int loeschen(void);
int get_dateigroesse(FILE*);
FILE* datei_oeffnen(void);
int aendern(int);
int raten(int, FILE*);
void extra(int);

// hauptfunktion
int main(void)
{
	int beenden = 0, wahl = 0, ok = 0, anzahl = 0;		// variabledeklaration/ Initialisierungen
	char ende = 'n';
	char eingabe[GROESSE] = { 0 };
	float richtig = 0.0, versuche = 0.0;
	FILE* meine_datei;			// meine Datei
	srand(time(0));		// zufallsgenerator deklarieren

	while (beenden == 0)
	{
		versuche = 0;
		richtig = 0;
		anzahl = 0;
		system("CLS");      //Bildschirm löschen
							//Eingabeaufforderung und Wert einlesen
		printf("menue\n (1) = Datei lesen \n (2) = in Datei schreiben \n (3) = Datei loeschen\n (4) = Datei aendern \n (5) = Raten\n (6) = Programm beenden\nIhre wahl:\t");
		fgets(eingabe, GROESSE, stdin);
		wahl = pruefen(eingabe);		// auswahl wird gewaehlt

		switch (wahl)		// input wird gewaehtl
		{
		case 1: 
			printf("\nInhalt der Datei lesen\n");
			meine_datei = datei_oeffnen();			// funktionsaufruf zum öffnen der datei und sie dann in meine datei
											// speichern
			anzahl = get_dateigroesse(meine_datei);	// dateigroesse waehlen
			ok = lesen(anzahl);		
			break;		// case verlassen

		case 2:  
			printf("\n\nDatei beschreiben\n");	
			do
			{
				ok = schreiben();	// in datei reinschreiben. // funktionsaufruf.
				tastaturpuffer_leeren();
				printf("Eintraege rein schreiben beenden? \nj\\n:\t");
				scanf("%c", &ende);
			} while (ende != 'j');
			meine_datei = datei_oeffnen();			// Datei öffnen
			anzahl = get_dateigroesse(meine_datei);	// findet anzahl der gespeicherten werte.
			ok = lesen(anzahl);	
			break;

		case 3:	 printf("Datei loeschen\n");
			ok = loeschen();	// datei wird geleert. einträge werden also gelöscht.
			break;

		case 4:	 printf("Datei aendern\n");
			meine_datei = datei_oeffnen();			// Datei öffnen
			anzahl = get_dateigroesse(meine_datei);
			if (anzahl > 0)
			{
				ok = lesen(anzahl);		// werte ausgeben.
				ok = aendern(anzahl);
			}
			else
			{
				printf("Keine Eintraege vorhanden");
			}
			break;

		case 5:
			printf("Raten\n");
			meine_datei = datei_oeffnen();			// Datei öffnen
			anzahl = get_dateigroesse(meine_datei);
			if (anzahl > 0)
			{
				do
				{
					ok = raten(anzahl, meine_datei);	// funktionsaufruuf mit anzahl und die datei als übergabeparameter.
					// wenn eine 1 zurückgegeben wurde dann war das raten richtig.
					if (ok == 1)
					{
						printf("Richtig\n");
						richtig++;
						versuche++;		// versuche wird hochgezäht und richtig auch um prozentwert zu kriegen.
					}
					else
					{
						printf("Falsch\n");
						versuche++;
					}
					printf("Nicht mehr raten?\nj\\n:\t");
					scanf("%c", &ende);
					tastaturpuffer_leeren();
				} while (ende != 'j');
				// rechnet den prozentwert und gibt es dann anschließend aus.
				printf("Erfolgsquote liegt bei %.2f Prozent", ((richtig / versuche) * 100));
			}
			else
			{
				printf("Keine Eintraege vorhanden");	// andernfalls gibt er eine fehlermeldung aus.
			}
			break;
		case 6:
			beenden = 1;		// setzt beenden gleich 1 damit die while- bedigung erfüllt wird.
			printf("\n\nDas Programm wird nun beendent.\n");
			break;
		case 7:
			extra(anzahl);
			break;
		default: 
			printf("\nFalsche Eingabe!\n\n");	// falsche eingabe.
			break;
		}
		tastaturpuffer_leeren();
		system("cls");
	}
	return(1);
}

FILE* datei_oeffnen()
{
	FILE* meine_datei;

	meine_datei = fopen(DATNAME, "ab+");	// ab+: erstellt bzw. öffnet eine bereits existierende binärdatei
									// zum lesen oder schreiben. der dateipositionszeger steht am ende der datei.
									// dadurch werden neue daten hinten angehängt.
	if (!meine_datei)  	//wenn nicht erfolgreich  Programm beenden // ist das gleiche wenn ich fhd == 0 amchen würde
	{
		printf("Datei konnte nicht geoeffnet werden!\n\n");
		tastaturpuffer_leeren();
		return 0;
	}
	return(meine_datei);
}

int schreiben(void)
{
	FILE *meine_datei;				        //Deklaration Filepointer
	char land[LAENGE], hauptstadt[LAENGE];		//Deklaration der strings

	meine_datei = fopen(DATNAME, "ab");	    //Datei zum binären Schreiben öffnen
	if (!meine_datei)		            //Öffnen nicht erfolgreich
	{
		printf("Datei konnte nicht erzeugt werden!\n\n");
		getchar();
		return(0);                  //Fehler zurückgeben
	}
	// wenn Öffnen erfolgreich
	//Eingabeaufforderung und Werteeingabe
	printf("\n\nLand (Max. %i Zeichen)  :", LAENGE - 1);
	fgets(land, LAENGE, stdin);
	printf("Hauptstadt (Max. %i Zeichen) :", LAENGE - 1);
	fgets(hauptstadt, LAENGE, stdin);

	//eingegebene Werte in Datei schreiben
	fwrite(land, sizeof(land), 1, meine_datei);
	fwrite(hauptstadt, sizeof(hauptstadt), 1, meine_datei);
	fclose(meine_datei);		            //Datei schließen
	printf("\nEingabe beendet!\n");
	return(1);
}

int lesen(int anzahl)
{
	//Variablendeklaration wie in schreiben()
	FILE *meine_datei;
	char land[LAENGE], hauptstadt[LAENGE];

	meine_datei = fopen(DATNAME, "rb");	//Datei zum binären Lesen öffnen
	if (!meine_datei)		        //Öffnen nicht erfolgreich
	{
		printf("Datei konnte nicht erzeugt werden!\n\n");
		getchar();
		return(0);
	}

	if (anzahl == 0)
	{
		printf("Keine Eintraege vorhanden \n");
		return 0;
	}
	else
	{
		int i = 0;
		do
		{
			//Öffnen erfolgreich
			//Werte aus Datei lesen
			fread(land, sizeof(land), 1, meine_datei);		// die 1 wird mitgegeben damit das das ganze 1 mal ausgeführt
													// werden soll. land wird mitgegeben damit land ausgelesen
													// wird und die größe der bytes von land wird mitgegeben damit
													// das programm weiß wie viel er auslesen muss.
			fread(hauptstadt, sizeof(hauptstadt), 1, meine_datei);

			//Ausgabe der ausgelesenen Werte auf dem Monitor
			if (i <= 4)
			{
				printf("\n0%i. Land:\t%s", i + 1 + i, land);
				if (i == 4)
				{
					printf("%i. Hauptstadt:\t%s\n", i + 2 + i, hauptstadt);
				}
				else
				{
					printf("0%i. Hauptstadt:\t%s\n", i + 2 + i, hauptstadt);
				}
			}
			else
			{
				printf("\n%i. Land:\t%s", i + 1 + i, land);
				printf("%i. Hauptstadt:\t%s\n", i + 2 + i, hauptstadt);
			}

			i++;
		} while (i < (anzahl / 2));
	}
	fclose(meine_datei);                 //Datei schließen
	printf("\nEingabe beendet!\n");
	return(1);
}

int loeschen(void)
{
	FILE *meine_datei;
	meine_datei = fopen(DATNAME, "wb");	//Datei zum binären Lesen öffnen

	if (!meine_datei)		        //Öffnen nicht erfolgreich
	{
		printf("Datei konnte nicht erzeugt werden!\n\n");
		getchar();
		return(0);
	}
	fclose(meine_datei);		            //Datei schließen
	printf("\nEingabe beendet!\n");
	return 1;
}

int get_dateigroesse(FILE* meine_datei)
{
	int  anzahl = 0;
	char land[LAENGE];
	rewind(meine_datei);	    //da beim Öffnen Dateipositionszeiger ggf. am Ende
	do				    //Datei lesen und Einträge zählen
	{
		fread(&land, sizeof(land), 1, meine_datei);
		anzahl++;
	} while (!feof(meine_datei));
	anzahl--;	            // da feof() erst nach Zugriff über Dateiende Wert ändert 
	printf("Es befinden sich %i Eintraege in der Datei\n", anzahl);
	rewind(meine_datei);  	    //Dateipositionszeiger wieder auf Anfang
	return(anzahl);
}

int aendern(int anzahl)
{
	//Variablendeklaration
	FILE *meine_datei;
	fpos_t skip;    //zum Positionieren des Dateipositionszeigers
	int nummer;
	char land[LAENGE];
	char eingabe[GROESSE];

	//Werteeingabe
	//Fehleingaben müssen noch abgefangen werden
	printf("\nWelcher Wert soll geaendert werden [1 bis %i] ", anzahl);
	fgets(eingabe, GROESSE, stdin);
	nummer = pruefen(eingabe);
	if (nummer <= anzahl && nummer != 0)
	{
		if (nummer % 2 == 1)
		{
			printf("\n\nLand aendern zu (Max. %i Zeichen)  :", LAENGE - 1);
			fgets(land, LAENGE, stdin);
			tastaturpuffer_leeren();
		}
		else
		{
			printf("\n\nHauptstadt aendern zu (Max. %i Zeichen)  :", LAENGE - 1);
			fgets(land, LAENGE, stdin);		// ist egal ob cih hauptstadt oder land eingebe. hauptsache an
											// der richtigen stelle speichern.
			tastaturpuffer_leeren();
		}
		meine_datei = fopen(DATNAME, "rb+"); 	//öffnen mit rb+ ,da Werte 
										//überschrieben werden sollen
		if (!meine_datei)		        //nicht erfolgreich
		{
			printf("Datei konnte nicht erzeugt werden!\n\n");
			getchar();
			return(0);
		}
		//Öffnen erfolgreich
		//Position zu überschreibendes Element berechnen
		skip = (nummer - 1) * sizeof(land);    //da Dateipositionszeiger
											   //hinter Element n-1 positioniert werden muss
											   //Dateipositionszeiger positionieren
		fsetpos(meine_datei, &skip);
		//neuen Wert in Datei schreiben 
		fwrite(&land, sizeof(land), 1, meine_datei);	// um den wert in die datei reinzuschreiben.
		printf("Wert wurde ueberschrieben\n");
		fclose(meine_datei);		            //Datei schließen
		return(1);
	}
	else
	{
		printf("Ungueltiger Wert.\n\n");	// fehlerausgabe
	}
	return 0;
}

int raten(int anzahl, FILE* meine_datei)
{
	int x;		// deklarationen // x für zufallszahl
	int check = 0;	// initialisierungen
	char cheat[GROESSE];
	int ok = 0;
	char eingabe[LAENGE];
	char land[LAENGE];
	char hauptstadt[LAENGE];
	fpos_t skip;    //zum Positionieren des Dateipositionszeigers

	do
	{
		x = (rand() % (anzahl));		// zufallszahl speichern.
		skip = (x - 1) * sizeof(land);		// sizeof(land) sagt dem skip(dateipositionszeiger) nur um wie viele
											// bytes er drüber springen soll um an der richtigen stelle der datei
											// zu sein.
		fsetpos(meine_datei, &skip);
		fread(&land, sizeof(land), 1, meine_datei);	// liest den eintrag aus.
		if (x % 2 == 1)
		{
			system("cls");
			printf("Wie lautet die Hauptstadt zu  = ");
			for (int idx = 0; idx < LAENGE; idx++)
			{
				if (land[idx] != '\0')		// überprüft ob der string am ende ist.
				{
					printf("%c", land[idx]);	// wenn nein dann gibt er aus.
				}
				else
				{
					idx = 25;		// wenn doch dann beendet er die for schleife.	
				}
			}
			printf("\nIhre Antwort lautet:\t");		// zeilensprung.
			fgets(eingabe, LAENGE, stdin);
			printf("\nwollen sie die richtige antwort ausgegeben haben?\nj\\n?\t");
			fgets(cheat, GROESSE, stdin);
			fread(&hauptstadt, sizeof(hauptstadt), 1, meine_datei);	// liest den eintrag aus
			if (cheat[0] == 'j')
			{
				printf("Richtige Antwort = ");

				for (int idx = 0; idx < LAENGE; idx++)
				{
					if (hauptstadt[idx] != '\0')
					{
						printf("%c", hauptstadt[idx]);		// gibt die hauptstadt aus die in der datei egspeichert wurde.
					}
					else
					{
						idx = 25;
					}
				}
				printf("\n");
			}
			for (int idx = 0; idx < LAENGE; idx++)
			{
				if (toupper(eingabe[idx]) == toupper(hauptstadt[idx]))		// kontrolle ob gleich ist
				{
				//	if (eingabe[idx] != '\0' && hauptstadt[idx] != '\0')
				//	{
						// ja gut das ergibt kein sinn aber trd kann ich es evtl brauchen.
				//		return 1;
				//	}
				}
				else
				{
					return 0;
				}
			}
			return 1;
			check = 1;
		}
	} while (check == 0 && x % 2 == 0);
}

// funktionsaufruf für pruefen
int pruefen(char eingabe[GROESSE]) {		// ein string wurde übergeben. ein integer wert wird übergeben
	int laenge = 0, fehler = 0, index = 0;	// initialisierungen
	laenge = strlen(eingabe);		// um herauszufinden wie groß der string ist
	if (eingabe[0] == '+') {		// überprüft ob ein + am anfang steht um es abzufangen
		laenge -= 2;		// wenn ja dann dekrementiert er die länge um 2
		for (index = 0; index < laenge; index++) {		// dient dazu um den + weg zu machen und um die zahlen zu vertauschen
			eingabe[index] = eingabe[index + 1];		// tauscht den ersten wert des arrays mit dem nächsten
			eingabe[index + 1] = 0;		// setzt den nächsten wert des arrays auf 0
		}
	}
	else {		// wenn die obige bedingung nicht erfüllt wurde dann führt er das aus
		laenge -= 1;	// länge wird um 1 dekrementiert. (länge--)
	}
	for (index = 0; index < laenge; index++) {		// dient dazu um alle string- zeichen zu überprüfen ob auch alle zahlen sind
		if (isdigit(eingabe[index]) == 0) {	// wenn eine 0 zurückgegeben wurde(also false) dann ist die stelle des arrays KEINE zahl und
			fehler++;		// die variable fehler wird incrementiert
		}
	}
	index = 0;		// index wird auf 0 gesetzt
	if (fehler == 0) {		// wenn fehler = 0 ist dann führt er die schleife aus
		index = atoi(eingabe);		// wandelt den string in einen integer wert um und setzt es mit index gleich
	}
	fehler = 0;	// setzt fehler = 0
	return index;	// gibt index wieder zurück
}			// ende........

void extra(int anzahl)
{
	FILE *meine_datei;
	char land[LAENGE];
	int idx = 0;

	meine_datei = fopen(DATNAME, "rb");	// öffnet eine binaerdatei zum lesen.

	rewind(meine_datei);	// setzt dateipositionszeiger auf anfang der datei.
	do
	{
		fread(&land, sizeof(land), 1, meine_datei);
		// addresse an der die aus der datei gelesenen inhalte gespeichert werden sollen.
		// groesse der variablen feld in byte.
		// anzahld er variablen feldelemente.
		// zeiger auf die file-struktur mit die zu schreibende datei verknüpft ist.
		anzahl++;
	} while (!feof(meine_datei));
	rewind(meine_datei);

	int i = 0, zahl = 0;
	printf("\n");
	do
		{
			fread(land, sizeof(land), 1, meine_datei);
			if (i % 4 == 0) {
				printf("Land: ");
				zahl = strlen(land);
				zahl--;
				for (idx = zahl; idx >= 0; idx--)
				{
					{
						printf("%c", land[idx]);
					}
				}
				printf("\n%s\n", land);
			}
			i++;
	} while (i < (anzahl));
	fclose(meine_datei);
}