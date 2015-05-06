#Steganograf v0.6 Copyright (C) 2013  Joakim Janjatovic <steganograf@outlook.com>
#GNU General Public License, version 3.0 (GPLv3)

CC = gcc
CFLAGS = -g
SOURCES = steganograf.c
LIBRARIES = -lfreeimage
SR = steg_sr.c
EN = steg_en.c

all: $(SOURCES)
	$(CC) $(SOURCES) $(SR) -o steganograf $(LIBRARIES)
debug: $(SOURCES)
	$(CC) $(SOURCES) $(SR) $(CFLAGS) -o steganograf $(LIBRARIES)
clean:
	rm -f core steganograf
english: $(SOURCES)
	$(CC) $(SOURCES) $(EN) -o steganograf $(LIBRARIES)
debug_english: $(SOURCES)
	$(CC) $(SOURCES) $(EN) $(CFLAGS) -o steganograf $(LIBRARIES)

