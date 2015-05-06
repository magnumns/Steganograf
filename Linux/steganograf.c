//////////////////////////////////////////////////////////////////////////
///////////////////////////Steganograf v0.6///////////////////////////////
//////////////////////////////////////////////////////////////////////////
/*
 Steganograf је program koji ucitava sliku, otkriva podatak ili sakriva podatak
 u slici i snima sliku. Sakriva po jedan bit podatka u poslednjem bitu svakog bajta slike.
 
 Steganograf is a program which loads a picture, unhides or hides data in the picture
 and saves picture. Hides one bit of data in the last bit of every byte of the picture.
 
 https://sourceforge.net/projects/c-steganograf\
//////////////////////////////////////////////////////////////////////////
 Steganograf v0.6 Copyright (C) 2013  Joakim Janjatovic <steganograf@outlook.com>
 Mentor/Menthor: Lazar Stricevic, Fakultet tehnickih nauka/Faculty of Technical Sciences

 Ovaj program koristi FreeImage biblioteku koja se koristi pod uslovima:
 GNU General Public License, version 3.0 (GPLv3).
 Ovaj rad je besplatan mozete ga umnozavati i/ili menjati u skladu sa uslovima:
 GNU General Public License, version 3.0 (GPLv3).
 U prilogu je kopija licence "LICENCE.txt" na engleskom jeziku.
 Ovaj rad se distribuira u nadi da će biti koristan ali bez ikakve garancije
 i bez podrzumevane garancije funkcionalnosti ili prikladnosti za određenu namenu.

 This software uses the FreeImage open source image library used under:
 GNU General Public License, version 3.0 (GPLv3)
 This program is free software you can redistribute it and/or modify it under the terms of:
 GNU General Public License, version 3.0 (GPLv3).
 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 You should have received a copy of the licence "LICENCE.txt" in English.
*/
//////////////////////////////////////////////////////////////////////////
//Podrzani formati:
//BMP			Windows or OS/2 Bitmap
//JPG/JIF/JPEG/JPE	JPEG - JFIF Compliant; izlaz konvertovan u PNG
//PNG			Portable Network Graphics
//TIF/TIFF		Tagged Image File Format
//
//Ovaj program koristi prethodno instaliranu FreeImage biblioteku.
//http://freeimage.sourceforge.net/
//////////////////////////////////////////////////////////////////////////

#define MAXL 100000 //pocetni kapacitet podatka
#define NAZIV_DATOTEKE 50 //u steg_sr.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "FreeImage.h"
#include "steg_lang.h"

int snimi(int x, int y, int bpp, FREE_IMAGE_FORMAT fif,FIBITMAP *dib, char *izlaz_slika);
int ulaz_podatak(unsigned char **podatak, char *ime_ulaz_fajl, int najvise, int *br_prosirenja);
int izlaz_podatak(unsigned char *podatak, unsigned int duzina, char *ime_izlaz_fajl);
int podatak_slika(unsigned char *podatak, unsigned int duzina, unsigned char *slika, unsigned int *b, int najvise);
int slika_podatak(unsigned char *podatak, unsigned int duzina, unsigned char *slika, unsigned int *b, int najvise);
int upisi_duzinu(unsigned char *slika, unsigned int duzina);
int procitaj_duzinu(unsigned char *slika, float najvise);
float najvise_znakova(int x, int y, int bpp);
unsigned char *prosiri(unsigned char *podatak, int *br_prosirenja);
int oslobodi(FIBITMAP *dib, unsigned char *podatak);
const char *get_filename_ext(const char *filename);
void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message);
FIBITMAP* ucitaj_sliku(const char* lpszPathName, FREE_IMAGE_FORMAT fif);

int main(int argc, char *argv[])
{
	unsigned char *slika;	//pokazivac na prvi gornji levi piksel u slici
	int x, y, bpp;		//sirina, visina, broj komponenti (rgb->3)
	unsigned int duzina;	//ukupna duzina niza upisanog/za upis u "slika"
	float najvise;		//koliko znakova moze da stane u "slika"
	unsigned int b=0;	//brojac bajtova u slici
	char readwrite;		//sakrivanje/otkrivnje
	unsigned char *podatak = NULL;	//pokazivac na niz u koji se smesta podatak
	int br_prosirenja = 1;	//brojac prosirenja podatka
	int n;			//brojac za inicijalizovanje podatka
	char ulaz_slika[NAZIV_DATOTEKE];
	char ime_ulaz_fajl[NAZIV_DATOTEKE] = "";	//podrazumevana vrednost
	char ime_izlaz_fajl[NAZIV_DATOTEKE] = "";	//podrazumevana vrednost
	FIBITMAP *dib = NULL, *ptr = NULL;	//pokazivac na bitmapu
	FREE_IMAGE_FORMAT fif;	//format slike
	// Pocetak provere poziva ////////////////////////////////////////////////////
	int vflag = 0;
	int hflag = 0;
	char *wvalue = NULL;
	char *rvalue = NULL;
	char *fvalue = NULL;
	char *ovalue = NULL;
	int index;
	int g;
	opterr = 0;

	while ((g = getopt (argc, argv, "vhw:r:f:o:")) != -1)
		switch (g){
		case 'v':
			vflag = 1;
			puts(verzija);
			return 1;
		case 'h':
			hflag = 1;
			puts(uputstvo);
			puts(formati);
			return 1;
		case 'w':
			wvalue = optarg;
			if (wvalue[0] == '-'){ //provera da li ima argumenta
				printf("%s -%c %s\n", opcija, g, zahteva_arg);
				return 1;
			}
			readwrite = g;
			strncpy(ulaz_slika, wvalue, NAZIV_DATOTEKE);
			ulaz_slika[NAZIV_DATOTEKE - 1]= '\0'; //kraj stringa ako je predugacak
			break;
		case 'r':
			rvalue = optarg;
			if (rvalue[0] == '-'){
				printf("%s -%c %s\n", opcija, g, zahteva_arg);
				return 1;
			}
			readwrite = g;
			strncpy(ulaz_slika, rvalue, NAZIV_DATOTEKE);
			ulaz_slika[NAZIV_DATOTEKE - 1]= '\0';
			break;
		case 'f':
			fvalue = optarg;
			if (fvalue[0] == '-'){
				printf("%s -%c %s\n", opcija, g, zahteva_arg);
				return 1;
			}
			strncpy(ime_ulaz_fajl, fvalue, NAZIV_DATOTEKE);
			ime_ulaz_fajl[NAZIV_DATOTEKE - 1]= '\0';
			strncpy(ime_izlaz_fajl, fvalue, NAZIV_DATOTEKE);
			ime_izlaz_fajl[NAZIV_DATOTEKE - 1]= '\0';
			break;
		case 'o':
			if (readwrite == 'r'){
				printf("%s\n", r_opcija);
				break;
			}
			ovalue = optarg;
			if (ovalue[0] == '-'){
				printf("%s -%c %s\n", opcija, g, zahteva_arg);
				return 1;
			}
			strncpy(izlaz_slika, ovalue, NAZIV_DATOTEKE);
			izlaz_slika[NAZIV_DATOTEKE - 1]= '\0';
			break;
		case '?':
			if (optopt == 'w')
				fprintf(stderr, "%s -%c %s\n", opcija, optopt, zahteva_arg);
			else if (optopt == 'r')
				fprintf(stderr, "%s -%c %s\n", opcija, optopt, zahteva_arg);
			else if (optopt == 'f')
				fprintf(stderr, "%s -%c %s\n", opcija, optopt, zahteva_arg);
			else if (optopt == 'o')
				fprintf(stderr, "%s -%c %s\n", opcija, optopt, zahteva_arg);
			else if (isprint (optopt))
				fprintf(stderr, "%s -%c.\n", nepoz_op, optopt);
			else
				fprintf(stderr, "%s \\x%x.\n", nepoz_ozn_op, optopt);
			return 1;
		default:
			abort();
		}
	if ((wvalue == 0) && (rvalue == 0)){
		printf("%s\n", neispravan_poz);
		printf("%s\n%s -h\n", za_uputstvo, argv[0]);
		return 1;
	}
	for(index = optind; index < argc; index++)
		printf("%s %s\n", arg_nije_op, argv[index]);
	//za proveru poziva otkomentarisati
	//printf("wvalue = %s, rvalue = %s, fvalue = %s, ovalue = %s\n", wvalue, rvalue, fvalue, ovalue);
	// Kraj provere poziva ///////////////////////////////////////////////////////
	FILE *test;
	test = fopen(ulaz_slika, "rb");
	if (test == NULL){
		printf("%s\n", nije_ulaz_s);
		perror("");
		return 1;
	}
	fclose(test);
	
	FreeImage_Initialise(FALSE);
	
	fif = FreeImage_GetFileType(ulaz_slika, 0);
	if ((fif != FIF_BMP) && (fif != FIF_JPEG) && (fif != FIF_PNG) && (fif != FIF_TIFF)){
		printf("%s %s\n", get_filename_ext(ulaz_slika), form_nepodrzan);
		oslobodi(dib, podatak);
		return 1;
	}
	
	dib = ucitaj_sliku(ulaz_slika, fif);
	if (dib == NULL) {
		printf("%s %s\n", get_filename_ext(ulaz_slika), form_nepodrzan_ost);
		FreeImage_SetOutputMessage(FreeImageErrorHandler);
		oslobodi(dib, podatak);
		return 1;
	}
	printf("%s \"%s\".\n", ucitan, ulaz_slika);

	slika = (unsigned char*)FreeImage_GetBits(dib);
	x = FreeImage_GetWidth(dib);
	y = FreeImage_GetHeight(dib);
	bpp = FreeImage_GetBPP(dib);
	
	//ispis informacija o slici
	najvise = najvise_znakova(x, y, bpp);
	printf("r/w = %c     %s = %d/%d/%d     %s = %.0f B\n", readwrite, svb, x, y, bpp, kapacitet, najvise);
	
	//zauzimanje memorije za podatak i inicijalizacija
	podatak = (char *)calloc(sizeof(char), MAXL);
	if (podatak == NULL){
		printf("%s\n", nije_niz);
		oslobodi(dib, podatak);
		return 1;
	}
		
	//sakrivanje ili otkrivanje
	if (readwrite == 'w'){
		//ucitava znakove iz "ime_ulaz_fajl" u "podatak" i proverava najvecu duzinu
		duzina = ulaz_podatak(&podatak, ime_ulaz_fajl, najvise, &br_prosirenja);
		if (duzina == -1){
			oslobodi(dib, podatak);
			return 1;
		}
		
		//upisuje duzinu u "slika"
		if (upisi_duzinu(slika, duzina)){
			oslobodi(dib, podatak);
			return 1;
		}
		
		//upisuje "podatak" u "slika"
		b = 32;
		if (podatak_slika(podatak, duzina, slika, &b, najvise)){
			oslobodi(dib, podatak);
			return 1;
		}
		printf("%s %d B\n", sakriveno, duzina);
		
		//snima "slika" u "izlaz_slika"
		if (snimi(x, y, bpp, fif, dib, izlaz_slika)){
			oslobodi(dib, podatak);
			return 1;
		}
	}
	else if (readwrite == 'r'){
		//cita duzinu iz "slika"
		duzina = procitaj_duzinu(slika, najvise);
		if (duzina == 0){
			oslobodi(dib, podatak);
			return 1;
		}
		printf("%s %d B\n", otkriveno, duzina);
		
		//prosiruje "podatak" ako je duzina veca od njega
		if (duzina >= MAXL*br_prosirenja){
			do{
			podatak = prosiri(podatak, &br_prosirenja);
			if (podatak == NULL){
				oslobodi(dib, podatak);
				return 1;
			}
			}while (duzina >= MAXL*br_prosirenja);
		}
		
		//ucitava "podatak" iz "slika"
		b = 32;
		if (slika_podatak(podatak, duzina, slika, &b, najvise)){
			oslobodi(dib, podatak);
			return 1;
		}
		
		//ispisuje "podatak" u "ime_izlaz_fajl"
		if (izlaz_podatak(podatak, duzina, ime_izlaz_fajl)){
			oslobodi(dib, podatak);
			return 1;
		}
	}
	oslobodi(dib, podatak);
	return 0;
}

//snima "slika" u "izlaz_slika"
//vrca 0 za uspesan upis, 1 za neuspesan
int snimi(int x, int y, int bpp, FREE_IMAGE_FORMAT fif,FIBITMAP *dib, char *izlaz_slika){
	if (fif == FIF_BMP){
		if (((strcmp(izlaz_slika, "izlaz")) == 0) || ((strcmp(izlaz_slika, "exit")) == 0))
			strcpy(izlaz_slika, strcat(izlaz_slika, ".bmp"));
		if (FreeImage_Save(fif, dib, izlaz_slika, BMP_DEFAULT)){
			printf("%s \"%s\".\n", snimljen, izlaz_slika);
			return 0;
		}
	}
	if (fif == FIF_JPEG){
		if (((strcmp(izlaz_slika, "izlaz")) == 0) || ((strcmp(izlaz_slika, "exit")) == 0))
			strcpy(izlaz_slika, strcat(izlaz_slika, ".png"));
		if (FreeImage_Save(FIF_PNG, dib, izlaz_slika, 0)){
			printf("%s \"%s\".\n", snimljen, izlaz_slika);
			return 0;
		}
	}
	if (fif == FIF_PNG){
		if (((strcmp(izlaz_slika, "izlaz")) == 0) || ((strcmp(izlaz_slika, "exit")) == 0))
			strcpy(izlaz_slika, strcat(izlaz_slika, ".png"));
		if (FreeImage_Save(fif, dib, izlaz_slika, 0)){
			printf("%s \"%s\".\n", snimljen, izlaz_slika);
			return 0;
		}
	}
	if (fif == FIF_TIFF){
		if (((strcmp(izlaz_slika, "izlaz")) == 0) || ((strcmp(izlaz_slika, "exit")) == 0))
			strcpy(izlaz_slika, strcat(izlaz_slika, ".tif"));
		if (FreeImage_Save(fif, dib, izlaz_slika, TIFF_NONE)){
			printf("%s \"%s\".\n", snimljen, izlaz_slika);
			return 0;
		}
	}
	printf("%s \"%s\"!\n", nije_snimljen, izlaz_slika);
	FreeImage_SetOutputMessage(FreeImageErrorHandler);
    	return 1;
}

FIBITMAP* ucitaj_sliku(const char* lpszPathName, FREE_IMAGE_FORMAT fif){
	if (fif == FIF_BMP){
		FIBITMAP *dib = FreeImage_Load(fif, lpszPathName, 0);
		return dib;
	}
	if (fif == FIF_JPEG){
		FIBITMAP *dib = FreeImage_Load(fif, lpszPathName, JPEG_ACCURATE);
		return dib;
	}
	if (fif == FIF_PNG){
		FIBITMAP *dib = FreeImage_Load(fif, lpszPathName, 0);
		return dib;
	}
	if (fif == FIF_TIFF){
		FIBITMAP *dib = FreeImage_Load(fif, lpszPathName, 0);
		return dib;
	}
	return NULL;
}
//ucitava znakove iz "ime_ulaz_fajl" ako je zadato,a ako nije,
//ucitava sa "stdin" i snima u "podatak"
//vrca broj ucitanih znakova za uspesan upis, -1 za neuspesan
int ulaz_podatak(unsigned char **podatak, char *ime_ulaz_fajl, int najvise, int *br_prosirenja){
	int s;
	//ako "ime_ulaz_fajl" nije zadato, ucitava znakove sa "stdin"
	if (strlen(ime_ulaz_fajl) == 0){
		__fpurge(stdin);//fflush(stdin);//
		rewind(stdin);
		s = fread(*podatak, 1, MAXL*(*br_prosirenja), stdin);
		//fgets(*podatak, MAXL*(*br_prosirenja)*sizeof(char), stdin);
		//s = strlen(*podatak);
		if (s > najvise){
			printf("%s %d B\n%s %d B\n", velicina, s, kapacitetje, najvise);
			return -1;
		}
		//prosiruje "podatak" ako nije dovoljno dugacak
		if (s >= MAXL*(*br_prosirenja)){
			do{
			(*podatak) = prosiri(*podatak, br_prosirenja);
			if ((*podatak) == NULL)
				return -1;
			printf("%s\n", pov_kapacitet);
			__fpurge(stdin);//fflush(stdin);//
			rewind(stdin);
			s = fread(*podatak, 1, MAXL*(*br_prosirenja), stdin);
			//fgets(*podatak, MAXL*(*br_prosirenja)*sizeof(char), stdin);
			//s = strlen(*podatak);
			if (s > najvise){
				printf("%s %d B\n%s %d B\n", velicina, s, kapacitetje, najvise);
				return -1;
			}
			}while (s >= MAXL*(*br_prosirenja));
		}
		return s;
	}
	//ucitava znakove iz "ime_ulaz_fajl"
	FILE *ulaz;
	ulaz = fopen(ime_ulaz_fajl, "rb");
	if (ulaz == NULL){
		printf("%s\n", nije_ulaz_d);
		perror("");
		return -1;
	}
	
	s = fread(*podatak, 1, MAXL*(*br_prosirenja), ulaz);
	if (s > najvise){
			printf("%s %d B\n%s %d B\n", velicina, s, kapacitet, najvise);
			return -1;
	}
	//prosiruje "podatak" ako nije dovoljno dugacak
	if (s >= MAXL*(*br_prosirenja)){
		do{
		(*podatak) = prosiri(*podatak, br_prosirenja);
		if ((*podatak) == NULL)
			return -1;
		rewind(ulaz);
		s = fread(*podatak, 1, (MAXL*(*br_prosirenja)), ulaz);
		if (s > najvise){
			printf("%s %d B\n%s %d B\n", velicina, s, kapacitet, najvise);
			return -1;
		}
		}while (s >= MAXL*(*br_prosirenja));
	}
	printf("%s \"%s\"\n", ucitan, ime_ulaz_fajl);
	fclose (ulaz);
	return s;
}

//ispisuje "podatak" u "ime_izlaz_fajl"
//vrca 0 za uspesan upis, 1 za neuspesan
int izlaz_podatak(unsigned char *podatak, unsigned int duzina, char *ime_izlaz_fajl){
	if (strlen(ime_izlaz_fajl) == 0){
		fwrite(podatak, 1, duzina, stdout);
		return 0;
	}
	FILE *izlaz;
	izlaz = fopen(ime_izlaz_fajl, "wb");
	if(izlaz == NULL) {
		printf("%s\n", nije_izlaz_d);
		perror("");
		return 1;
	}
	fwrite(podatak, 1, duzina, izlaz);
	fclose (izlaz);
	printf("%s \"%s\"\n", snimljen, ime_izlaz_fajl);
	return 0;
}

//upisuje "podatak" u "slika"
//vrca 0 za uspesan upis, 1 za neuspesan
int podatak_slika(unsigned char *podatak, unsigned int duzina, unsigned char *slika, unsigned int *b, int najvise){
	unsigned int i, j;
	unsigned m;
	//prilikom ulaza se proverava najveca duzina, za svaki slucaj evo jos jednom...
	if (duzina > najvise){
		printf("%s %d B\n%s %d B\n", velicina, duzina, kapacitet, najvise);
		return 1;
	}
	//upisuje "podatak" u "slika"
	for (i = 0; i < duzina; i++){
		for (j = 0; j < 8; j++){
			m = podatak[i];
			m >>= 7-j;
			slika[*b] = slika[*b] - slika[*b]%2 + m%2;
			(*b)++;
		}
	}
	return 0;
}

//ucitava "podatak" iz "slika"
//vrca 0 za uspesan upis, 1 za neuspesan
int slika_podatak(unsigned char *podatak, unsigned int duzina, unsigned char *slika, unsigned int *b, int najvise){
	unsigned int i, j;
	unsigned char m;
	//provera da ne proba da procita vise nego sto ima u slici
	if (duzina > najvise){
		return 1;
	}
	//"duzina" znakova iz "slika" upisuje u "podatak"
	for (i = 0; i < duzina; i++){	
		for (j = 0; j < 8; j++){
			podatak[i] <<= 1;
			podatak[i] += slika[*b]%2;
			(*b)++;
		}
	}
	return 0;
}

//upisuje duzinu "podatak"a u "slika"
//vraca 0 za ispravan upis a 1 ako je duuzina <=0
int upisi_duzinu(unsigned char *slika, unsigned int duzina){
	int m;
	int b;
	if (duzina <= 0){
		printf("%s\n", nema_za_sak);
		return 1;
	}
	for (b = 0; b < 32; b++){
		m = duzina;
		m >>= 31-b;
		slika[b] = slika[b] - slika[b]%2 + m%2;
	}
	return 0;
}

//cita broj znakova iz "slika"
//vraca duzinu teksta u slici
int procitaj_duzinu(unsigned char *slika, float najvise){
	int m = 0;
	int b = 0, i;
	for (i = 0; i < 32; i++){
		m <<= 1;
		m += slika[b]%2;
		b++;
	}
	if (m <= 0 || m >= najvise){
		printf("%s\n", nema_sak);
		m = 0;
	}
	return m;
}

//racuna i vraca koliko znakova moze da stane u "slika"
float najvise_znakova(int x, int y, int bpp){
	return (x*y*(bpp/8.0)-4.0)/8.0;
	/*(broj piksela * (velicina piksela u bajtima) - broj bajta za velicinu sakrivenog podatka/
	    broj bajta slike potreban za saskrivanje jednog bajta podatka*/
}

//prosiruje kapacitet podatka 2 puta
//vraca novu adresu ako je uspesno, NULL ako nije
unsigned char *prosiri(unsigned char *podatak, int *br_prosirenja){
	int n;
	unsigned char *prosiren_podatak = NULL;
	prosiren_podatak = (char *)calloc(sizeof(char), MAXL*(*br_prosirenja)*2);
	if (prosiren_podatak != NULL){
		free(podatak);
		podatak = prosiren_podatak;
		(*br_prosirenja) *= 2;
		return podatak;
	}
	printf("%s\n", nije_prosiren);
	return NULL;
}

//oslobadja memoriju zauzetu slikom i podatkaom i deinicijalizuje FreeImage
int oslobodi(FIBITMAP *dib, unsigned char *podatak){
	if (dib){
		FreeImage_Unload(dib);
	}
	if (podatak){
		free(podatak);
	}
	FreeImage_DeInitialise();
	return 0;
}

//izvlaci ekstenziju iz imena datoteke
const char *get_filename_ext(const char *filename){
	const char *dot = strrchr(filename, '.');
	if(!dot || dot == filename)
		return "";
	return dot + 1;
}

//rukovanje greskama
void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message){
	printf("\n*** ");
	if(fif != FIF_UNKNOWN) {
		if (FreeImage_GetFormatFromFIF(fif))
			printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
	}
	puts(message);
	printf(" ***\n");
}

