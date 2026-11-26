# Makefile de SlimC  (Linux, macOS o MSYS2 UCRT64 en Windows)
#   make          compila slimc (Flex + Bison) y slimc_manual (respaldo en C)
#   make probar   corre correcto.c y errores.c en cada versión compilada
#   make limpiar  borra lo generado
CC := gcc
ifeq ($(OS),Windows_NT)
  EXE := .exe
  STATIC := -static
endif
FUENTES := tabla_simbolos.c semantica.c
CABECERAS := tabla_simbolos.h semantica.h

all: slimc$(EXE) slimc_manual$(EXE)

slimc$(EXE): parser.y lexer.l $(FUENTES) $(CABECERAS)
	bison -d parser.y
	flex lexer.l
	$(CC) $(STATIC) -o $@ parser.tab.c lex.yy.c $(FUENTES)

slimc_manual$(EXE): slimc_manual.c $(FUENTES) $(CABECERAS)
	$(CC) $(STATIC) -Wall -o $@ slimc_manual.c $(FUENTES)

probar: all
	bash probar.sh

limpiar:
	rm -f slimc slimc.exe slimc_manual slimc_manual.exe parser.tab.c parser.tab.h lex.yy.c

.PHONY: all probar limpiar
