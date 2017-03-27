
# Copyright (c) 2017 The Gupta Empire - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
#
# Written by Aryan Gupta <me@theguptaempire.net>
# 
# ==============================================================================
# @author 			Aryan Gupta
# @project 			Archespace
# @file 			Makefile
# @date				2017-03-06 (YYYY-MM-DD)
# @version			1.0.0
# @brief 			This is the Makefile for The Tic Tac Toe Project
# ==============================================================================
.DEFAULT_GOAL := all
# ==========================  CONST MACROS  ====================================
CC = "C:\Compiler\MinGW-w64\mingw32\bin\g++.exe"
7Z = "C:\Program Files (Portable)\7-Zip\7z.exe"
RES = "C:\Compiler\MinGW-w64\mingw32\bin\windres.exe"
DOXY = "C:\Compiler\doxygen\bin\doxygen.exe"
OBJ = .\obj
BINDIR = .\bin
DATDIR = .\dat
H   = .\inc

DEBUG = -g -DDEBUG=true

# ============================  SDL LIBS  ======================================
GRAPHICS = -w -Wl,-subsystem,windows
# Standard SDL libs
L_SDLC = -IC:\Compiler\SDL\include\SDL2 
L_SDLL = -LC:\Compiler\SDL\lib -lmingw32 -lSDL2main -lSDL2 \
							   -lSDL2_mixer  -lSDL2_ttf  -lSDL2_image
L_SDLS = -lmingw32 -lSDL2main -lSDL2  -mwindows  -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc

# ==============================  MACROS  ======================================
CFLAGS = $(DEBUG) -Wall -std=c++17 -c
LFLAGS = $(DEBUG) -Wall
OS = $(OBJ)\main.o $(OBJ)\res.o $(OBJ)\Ship.o $(OBJ)\Window.o \
		$(OBJ)\Resources.o $(OBJ)\Thing.o $(OBJ)\Player.o $(OBJ)\Bullet.o
#		$(OBJ)\Powerup.o

# ============================ RECEM_PIES ========================================

$(OBJ)\main.o: .\main.cpp $(H)\main.h $(H)\Thing.h $(H)\Ship.h $(H)\Player.h $(H)\Window.h $(H)\Resources.h
	$(CC) .\main.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Thing.o: .\Thing.cpp $(H)\Thing.h
	$(CC) .\Thing.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Ship.o: .\Ship.cpp $(H)\Ship.h $(H)\Thing.h
	$(CC) .\Ship.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Player.o: .\Player.cpp $(H)\Player.h $(H)\Ship.h $(H)\Thing.h
	$(CC) .\Player.cpp -o .\$@ $(CFLAGS) $(L_SDLC)
	
$(OBJ)\Window.o: .\Window.cpp $(H)\Window.h
	$(CC) .\Window.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Bullet.o: .\Bullet.cpp $(H)\Bullet.h $(H)\Thing.h
	$(CC) .\Bullet.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Powerup.o: .\Powerup.cpp $(H)\Powerup.h $(H)\Thing.h
	$(CC) .\Powerup.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Resources.o: .\Resources.cpp $(H)\Resources.h
	$(CC) .\Resources.cpp -o .\$@ $(CFLAGS) $(L_SDLC)
	
$(OBJ)\%.o: .\%.cpp
	$(CC) .\$^ -o .\$@ $(CFLAGS) 

$(OBJ)\res.o: .\res.rc .\info.h
	$(RES) .\res.rc  .\$@
	
# Link	
$(BINDIR)\main.exe: $(OS)
	$(CC) .\$^ -o .\$@ $(LFLAGS) $(L_SDLL)
	
# ============================= PHONY RECEM_PIES =================================
.PHONY: all
all: clean $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) $(L_SDLL) -o $(BINDIR)\final.exe

.PHONY: link
link:
	$(CC) .\$^ $(LFLAGS) $(L_SDLL) -o $(BINDIR)\main.exe	
	
.PHONY: clean
clean:
	del $(OBJ)\*.o
	del $(BINDIR)\*.exe
	del $(DATDIR)\*.dat

.PHONY: archive
archive:
	$(7Z) a -tzip .\arc\"%DATE:~-4%%DATE:~4,2%%DATE:~7,2%".zip * -xr!obj -xr!bin -xr!arc
	
.PHONY: doxy
doxygen doxy:
	$(DOXY) doxygen.ini