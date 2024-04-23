// ******************************************************************************************
// * Service-Funktionen für C
// *
// * Autor: Marcel Klein [klein.marcel@fh-swf.de]
// * Datei: fhswf_service.h
// * Datum: 20.10.2016
// *
// * Beschreibung:
// * Headerdatei mit diversen Service-Funktionen (z.B. zum Leeren des Tastaturpuffers) unter
// * Verwendung der Programmiersprache C für das Fach "Programmierung 1" an der FH-SWF.
// * Die Datei wird ggf. im Laufe des Semesters ergänzt (Änderungsdatum beachten!).
// *
// * Installation/Verwendung:
// * - Variante 1:  C-Projekt erstellen und Headerdatei (*.h) in das Projektverzeichnis
// *                kopieren (dort liegen auch die Quellcodedateien). Einbinden der Header-
// *                datei dann mit [#include "fhswf_service.h"].
// *                Bei dieser Variante muss die Headerdatei in jedes neue Projektverzeichnis
// *                erneut kopiert werden.
// * - Variante 2:  Headerdatei (*.h) in das globale Include-Verzeichnis des Kompilers
// * (empfohlen)    kopieren. Bei Visual Studio 2013 kann sich dies z.B. unter
// *                "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include"
// *                befinden. Einbinden der Headerdatei im Quellcode dann mit
// *                [#include <fhswf_service.h>]. Vorteil: Bei dieser Variante muss die
// *                Headerdatei nur einmalig kopiert werden und kann in jedem neuen Projekt
// *                per [#include <...>] eingebunden werden.
// * WICHTIG !!! :  Unabhängig von beiden Varianten muss das Inkludieren der Headerdatei im
// *                Quellcode ganz am Anfang und noch vor den anderen Präprozessor-Direktiven
// *                geschehen!
// *
// ******************************************************************************************


// Schutz vor mehrfachem Einbinden der Headerdatei
#pragma once
#ifndef _fhswf_service_h_
#define _fhswf_service_h_

// Unsichere Funktionen wie z.B. scanf() erlauben
#define _CRT_SECURE_NO_WARNINGS

// Zusätzliche Headerdateien einbinden
#include <stdio.h>


// Funktion zum Leeren des Tastaturpuffers
void tastaturpuffer_leeren()
{
	int tmp;
	
	do
	{
		tmp = getchar();
	}
	while (tmp != EOF && tmp != '\n');
}


// Ende der Header-Datei
#endif