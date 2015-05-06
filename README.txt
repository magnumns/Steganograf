	s/////////////////////////////////////////////////////////////////s
	s////////////////////////Steganograf v0.6/////////////////////////s
	s/////////////////////////////////////////////////////////////////s
 Na srpskom i engleskom/In Serbian and English
 
 Steganograf је program koji ucitava sliku, otkriva podatak ili sakriva podatak
 u slici i snima sliku. Sakriva po jedan bit podatka u poslednjem bitu svakog bajta slike.
 Dostupan na: https://sourceforge.net/projects/c-steganograf
 
 Steganograf is a program which loads a picture, unhides or hides data in the picture
 and saves picture. Hides one bit of data in the last bit of every byte of the picture.
 Downloadable from: https://sourceforge.net/projects/c-steganograf
	s/////////////////////////////////////////////////////////////////s
			>>PODRZANI FORMATI/SUPPORTED FORMATS<<
				 
  BMP				Windows or OS/2 Bitmap
  JPG/JIF/JPEG/JPE	JPEG - JFIF Compliant; izlaz konvertovan u PNG/output converted to PNG
  PNG				Portable Network Graphics
  TIF/TIFF			Tagged Image File Format
	s/////////////////////////////////////////////////////////////////s
		>>INSTALACIJA (Kompajliranje)/INSTALLATION (Compiling)<<
	
	WINDOWS
	SR
 Ovaj program je vec kompajliran za Windows. Mozete ga pokrenuti iz CMD.
 Iz start menija otvorite Command Prompt i predjite u diraktorijum:
 Steganograf_v0.6/Windows
 Odatle mozete da pokrenete program po uputstvu POKRETANJE PROGRAMA ali koristeci:
 steganograf_sr umesto steganograf
 
 Program mozete i sami da kompajlirate. Sve potrebne datoteke su u direktorijumu:
 Steganograf_v0.6/Windows/Source
 Potrebno je neko od razvojnih okruzenja sa kompajlerom npr. DevC++
 U prazan DevC++ projekat dodati:
 strganograf.c
 cteg_lang.h
 steg_sr.c
 Podesiti kompajler.
 Opcija za linker: -lfreeimage
 Putanja za Libraries
 Steganograf_v0.6/Windows/Source/FreeImage
 Putanje za C Includes:
 Steganograf_v0.6/Windows/Source
 Steganograf_v0.6/Windows/Source/FreeImage
 NAPOMENA: steganograf.exe i FreeImage.dll moraju da budu u istom direktorijumu.
 
	EN
 This program is already compiled for Windows. You can run it from CMD.
 From the start menu open Command Prompt and go to directory:
 Steganograf_v0.6/Windows
 From there you can start the program as described in STARTING PROGRAM but using:
 steganograf_en instead of steganograf
 
 You can also compile it yourself. All necessary files are in directory:
 Steganograf_v0.6/Windows/Source
 You will need IDE with compiler eg. DevC++
 In empty DevC++ prject add:
 strganograf.c
 cteg_lang.h
 steg_en.c
 Setup compiler.
 Linker option: -lfreeimage
 Path for Libraries:
 Steganograf_v0.6/Windows/Source/FreeImage
 Paths for C Includes:
 Steganograf_v0.6/Windows/Source
 Steganograf_v0.6/Windows/Source/FreeImage
 NOTICE: steganograf.exe and FreeImage.dll must be in the same directory.

	LINUX
	SR
 Ovaj program zahteva prethodno instaliranu FreeImage biblioteku.
 http://freeimage.sourceforge.net/
 Na ubuntu sistemu FreeImage biblioteka moze da se instalira komandom:
 sudo apt-get install libfreeimage-dev

 Predjite u direktorijum:
 Steganograf_v0.6/Linux
 U terminalu ukucajte:
 make (za instalaciu)
 make debug (za instalaciju sa opcijom za otklanjanje gresaka)
 make clean (za brisanje instalacije)
 
 Neophodne datoteke:
 Makefile
 seganograf.c
 steg_lang.h
 steg_sr.c
 
	EN
 This program requires previously installed FreeImage library.
 http://freeimage.sourceforge.net/
 On ubuntu system FreeImage library can be installed using command:
 sudo apt-get install libfreeimage-dev
 
 Go to directory:
 Steganograf_v0.6/Linux
 Type in the terminal:
 make english (for installation)
 make debug_english (for installation with debugging option)
 make clean (for deleting installation)
 
 Necessary files:
 Makefile
 seganograf.c
 steg_lang.h
 steg_en.c
	s/////////////////////////////////////////////////////////////////s
			>>POKRETANJE PROGRAMA/STARTING PROGRAM<<

 ./steganograf [OPCIJA/OPTION]... [DATOTEKA/FILE]...

 Osnovne opcije/Basic options:
  -w ime_slike/picture_name		za sakrivanje podatka/for hiding data
  -r ime_slike/picture_name		za otkrivanje podatka/for unhiding data
  -v					verzija, licenca/version, licence
  -h					uputstvo/help
 Dodatne opcije:
  -f ulazno/izlazna_datoteka		podrazumevan ekran tj. stdin/stdout (prekid unosa Ctrl+d)/
									default is screen i.e. stdin/stdout (end of input Ctrl+d)
  -o izlazna_slika/output_picture	podrazumevan izlaz.ekstenzija/default is exit.extension
 
 U windows verziji kraj unosa sa tastature oznacava Return/Enter taster.
 In windows version end of kayboard input is marked by Return/Enter key.

 primeri/examples:
 ./steganograf -w bmp_24.bmp -f ulaz.txt -o izlaz.bmp
 Ucitava sliku "bmp_24.bmp", u nju sakriva podatak iz "ulaz.txt" i snima ga u "izlaz.bmp".
 Loads picture "bmp_24.bmp", hides data from "ulaz.txt" in it and saves it to "izlaz.bmp".

 ./steganograf -r izlaz.bmp -f izlaz.txt
 Ucitava sliku "izlaz.bmp", u njoj otkriva podatak i snima ga u "izlaz.txt".
 Loads picture "izlaz.bmp", unhides data in it and saves it to "izlaz.txt".

 Neophodne datoteke/Necessary files:
 slika (sa ekstenzijom)/picture (with extension)
 stegaograf
	s/////////////////////////////////////////////////////////////////s
		>>SADRZAJ/CONTENTS OF Steganograf_v0.6.tar.gz:<<
			     
 Linux/
	Makefile
	steg_en.c
	steg_lang.h
	steg_sr.c
	steganograf.c
 Windows/
	Source/
		FreeImage/
			FreeImage.c
			FreeImage.lib
		FreeImage.dll
		steg_en.c
		cteg_lang.h
		steg_sr.c
		steganograf.c
	FreeImage.dll
	Steganograf_en
	Steganograf_sr
 bmp_24.bmp
 LICENCE.txt
 README.txt
 Steganograf.pdf (v0.5)
	s/////////////////////////////////////////////////////////////////s
				>>NAPOMENA/NOTICE<<

 Program je isproban na 32-bitnom Ubuntu 13.04 sistemu sa gcc kompajlerom
 i na Windows 7 sistemu sa DevC++ 4.9.9.2 razvojnim okruzenjem!
 Program tested on 32-bit Ubuntu 13.04 system with gcc compiler and
 Windows  7 system with DevC++ 4.9.9.2 IDE!
 	s/////////////////////////////////////////////////////////////////s
			>>SPISAK PROMENA/CHANGELOG<<

 v0.5 prvi objavljen/first released
 v0.6 manja poboljsanja/minor improvements
      preveden na engleski/translated to English
	s/////////////////////////////////////////////////////////////////s
				>>LICENCE<<
				     
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
