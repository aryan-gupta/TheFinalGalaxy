
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
DRIVE = C
CC = "$(DRIVE):\Compiler\MinGW-w64\mingw32\bin\g++.exe"
7Z = "$(DRIVE):\Program Files (Portable)\7-Zip\7z.exe"
RES = "$(DRIVE):\Compiler\MinGW-w64\mingw32\bin\windres.exe"
DOXY = "$(DRIVE):\Compiler\doxygen\bin\doxygen.exe"
OBJ = .\obj
BINDIR = .\bin
DATDIR = .\dat
H   = .\inc

DEBUG = -g -DDEBUG=true

# ============================  SDL LIBS  ======================================
GRAPHICS = -w -Wl,-subsystem,windows
# Standard SDL libs
L_SDLC = -I$(DRIVE):\Compiler\SDL\include\SDL2 
L_SDLL = -L$(DRIVE):\Compiler\SDL\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
# -lSDL2_mixer  -lSDL2_ttf
L_SDLS = -lmingw32 -lSDL2main -lSDL2  -mwindows  -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc

# ==============================  MACROS  ======================================
CFLAGS = $(DEBUG) -Wall -std=c++17 -c
LFLAGS = $(DEBUG) -Wall
OS = $(OBJ)\main.o $(OBJ)\res.o $(OBJ)\Window.o $(OBJ)\Enemy.o $(OBJ)\Asteroid.o \
		$(OBJ)\Resources.o $(OBJ)\Thing.o $(OBJ)\Player.o $(OBJ)\Bullet.o
#		$(OBJ)\Powerup.o

# ============================ RECEM_PIES ========================================

$(OBJ)\main.o: .\main.cpp $(H)\main.h $(H)\Thing.h $(H)\Ship.h $(H)\Player.h $(H)\Window.h $(H)\Resources.h
	$(CC) .\main.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Thing.o: .\Thing.cpp $(H)\Thing.h $(H)\main.h
	$(CC) .\Thing.cpp -o .\$@ $(CFLAGS) $(L_SDLC)
	
$(OBJ)\Asteroid.o: .\Asteroid.cpp $(H)\Asteroid.h $(H)\main.h
	$(CC) .\Asteroid.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Player.o: .\Player.cpp $(H)\Player.h $(H)\main.h $(H)\Ship.h $(H)\Thing.h
	$(CC) .\Player.cpp -o .\$@ $(CFLAGS) $(L_SDLC)
	
$(OBJ)\Enemy.o: .\Enemy.cpp $(H)\Enemy.h $(H)\main.h $(H)\Ship.h $(H)\Thing.h
	$(CC) .\Enemy.cpp -o .\$@ $(CFLAGS) $(L_SDLC)
	
$(OBJ)\Window.o: .\Window.cpp $(H)\Window.h $(H)\main.h
	$(CC) .\Window.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Bullet.o: .\Bullet.cpp $(H)\Bullet.h $(H)\main.h $(H)\Thing.h
	$(CC) .\Bullet.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Powerup.o: .\Powerup.cpp $(H)\Powerup.h $(H)\main.h $(H)\Thing.h
	$(CC) .\Powerup.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJ)\Resources.o: .\Resources.cpp $(H)\Resources.h $(H)\main.h
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