//Steganograf v0.6 Copyright (C) 2013  Joakim Janjatovic <steganograf@outlook.com>
//GNU General Public License, version 3.0 (GPLv3)
//engleski prevod

#include "steg_lang.h"
#define NAZIV_DATOTEKE 50

char verzija[] = "\n Steganograf v0.6\n (C) 2013  Joakim Janjatovic\n Ovaj program koristi FreeImage biblioteku koja se koristi pod uslovima\n GNU General Public License, version 3.0 (GPLv3).\n Ovaj program je besplatan: mozete ga umnozavati i/ili menjati\n u skladu sa uslovima GNU General Public License, version 3.0 (GPLv3).\n Greske prijavite na: steganograf@outlook.com\n Dostupan na: https://sourceforge.net/projects/c-steganograf\n";
char formati[] = "\n Podrzani formati slika:\n  BMP\t\t\t\tWindows or OS/2 Bitmap\n  JPG/JIF/JPEG/JPE\t\tJPEG - JFIF Compliant; izlaz konvertovan u PNG\n  PNG\t\t\t\tPortable Network Graphics\n  TIF/TIFF\t\t\tTagged Image File Format\n";
char uputstvo[] = "\n Upotreba: ./steganograf [OPCIJA]... [DATOTEKA]...\n Osnovne opcije:\n  -w ime_slike\t\t\tza sakrivanje podatka\n  -r ime_slike\t\t\tza otkrivanje podatka\n  -v\t\t\t\tverzija, licenca\n  -h\t\t\t\tuputstvo\n Dodatne opcije:\n  -f ulazno/izlazna_datoteka\tpodrazumevan ekran tj. stdin/stdout (prekid unosa Ctrl+d)\n  -o izlazna_slika\t\tpodrazumevan izlaz.[bmp|png|tif]\n";
char izlaz_slika[NAZIV_DATOTEKE] = "izlaz";	//podrazumevana vrednost
char opcija[] = "Opcija";
char zahteva_arg[] = "zahteva argument.";
char r_opcija[] = "Izlazna slika se ne moze definisati uz -r opciju";
char nepoz_op[] = "Nepoznata opcija";
char nepoz_ozn_op[] = "Nepoznata oznaka opcije";
char neispravan_poz[] = "Neispravan poziv!";
char za_uputstvo[] = "Za uputstvo unesite:";
char arg_nije_op[] = "Argument koji nije opcija";
char nije_ulaz_s[] = "Nije moguce otvoriti ulaznu sliku!";
char form_nepodrzan[] = "format slike nije podrzan.";
char form_nepodrzan_ost[] = "format slike nije podrzan ili je datoteka ostecena.";
char ucitan[] = "Ucitan";
char svb[] = "sirina/visina/bpp";
char kapacitet[] = "kapacitet";
char nije_niz[] = "Nije moguce napraviti niz za smestanje podatka!";
char sakriveno[] = "Sakriveno";
char otkriveno[] = "Otkriveno";
char snimljen[] = "Snimljen";
char nije_snimljen[] = "Nije moguce snimiti";
char velicina[] = "Velicina podatka je";
char kapacitetje[] = "Kapacitet slike je";
char pov_kapacitet[] = "Povecan je kapacitet podataka. Unesite tekst ponovo:";
char nije_ulaz_d[] = "Nije moguce otvoriti ulaznu datoteku!";
char nije_izlaz_d[] = "Nije moguce otvoriti izlaznu datoteku!";
char nema_za_sak[] = "Nema podataka za sakrivanje.";
char nema_sak[] = "U slici nema sakrivenih podataka.";
char nije_prosiren[] = "Greska prilikom prosirenja kapaciteta podatka!";

