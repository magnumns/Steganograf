//Steganograf v0.6 Copyright (C) 2013  Joakim Janjatovic <steganograf@outlook.com>
//GNU General Public License, version 3.0 (GPLv3)
//srpski

#include "steg_lang.h"
#define NAZIV_DATOTEKE 50

char verzija[] = "\n Steganograf v0.6\n (C) 2013  Joakim Janjatovic\n This program uses FreeImage library wich is used under terms of\n GNU General Public License, version 3.0 (GPLv3).\n This program is free: you can copy and/or change it\n under terms of GNU General Public License, version 3.0 (GPLv3).\n Report bugs to: steganograf@outlook.com\n Downloadable from: https://sourceforge.net/projects/c-steganograf\n";
char formati[] = "\n Supported image formats:\n  BMP\t\t\t\tWindows or OS/2 Bitmap\n  JPG/JIF/JPEG/JPE\t\tJPEG - JFIF Compliant; output converted to PNG\n  PNG\t\t\t\tPortable Network Graphics\n  TIF/TIFF\t\t\tTagged Image File Format\n";
char uputstvo[] = "\n Usage: ./steganograf [OPTION]... [FILE]...\n Basic options:\n  -w picture_name\t\tfor hiding data\n  -r picture_name\t\tfor unhiding data\n  -v\t\t\t\tversion, licence\n  -h\t\t\t\thelp\n Additional options:\n  -f input/output file\t\tdefault is screen i.e. stdin/stdout (end of input Ctrl+d)\n  -o output_picture\t\tdefault is exit.[bmp|png|tif]\n";
char izlaz_slika[NAZIV_DATOTEKE] = "exit";	//default value
char opcija[] = "Option";
char zahteva_arg[] = "requires argument.";
char r_opcija[] = "Can not define output picture with -r option";
char nepoz_op[] = "Unknown option";
char nepoz_ozn_op[] = "Unknown option mark";
char neispravan_poz[] = "Invalid call!";
char za_uputstvo[] = "For help enter:";
char arg_nije_op[] = "Argument which is not an option";
char nije_ulaz_s[] = "Unable to open input picture!";
char form_nepodrzan[] = "picture format not supported.";
char form_nepodrzan_ost[] = "picture format not supported or corrupt.";
char ucitan[] = "Loaded";
char svb[] = "width/hight/bpp";
char kapacitet[] = "capacity";
char nije_niz[] = "Unable to make an array for data!";
char sakriveno[] = "Hidden";
char otkriveno[] = "Unhidden";
char snimljen[] = "Saved";
char nije_snimljen[] = "Unable to save";
char velicina[] = "Data size is";
char kapacitetje[] = "Picture capacity is";
char pov_kapacitet[] = "Expanded data capacity. Enter text again:";
char nije_ulaz_d[] = "Unable to open input file!";
char nije_izlaz_d[] = "Unable to open output file!";
char nema_za_sak[] = "No data to hide.";
char nema_sak[] = "No hidden data in the picture.";
char nije_prosiren[] = "Error while expanding data capacity!";

