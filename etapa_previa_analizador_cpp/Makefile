# Uso en Linux/macOS:  make        -> compila las dos versiones
#                      make probar -> corre las 3 pruebas en cada una
CXX ?= g++
CC  ?= gcc

all: analizador analizador_bison

analizador: analizador.cpp
	$(CXX) -std=c++17 -O2 -Wall -Wextra analizador.cpp -o analizador

analizador_bison: flex_bison/lexer.l flex_bison/parser.y
	cd flex_bison && bison -d parser.y && flex lexer.l && $(CC) parser.tab.c lex.yy.c -o ../analizador_bison

probar: all
	@for v in ./analizador ./analizador_bison; do \
	  echo "################ $$v"; \
	  for f in prueba prueba_errores prueba_sintaxis; do \
	    echo "=== $$f.c"; $$v $$f.c; echo "(codigo de salida: $$?)"; \
	  done; \
	done

limpiar:
	rm -f analizador analizador_bison flex_bison/lex.yy.c flex_bison/parser.tab.c flex_bison/parser.tab.h
