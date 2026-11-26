#!/usr/bin/env bash
# Compila SlimC paso a paso (Linux/macOS o terminal MSYS2 UCRT64).  Uso: ./compilar.sh
cd "$(dirname "$0")" || exit 1
EXE=""; STATIC=""
if [ "$OS" = "Windows_NT" ]; then EXE=".exe"; STATIC="-static"; fi

echo "== 1. Versión Flex + Bison (la que se entrega)"
bison -d parser.y         || { echo "[ERROR] bison falló"; exit 1; }
flex lexer.l              || { echo "[ERROR] flex falló"; exit 1; }
gcc $STATIC -o slimc$EXE parser.tab.c lex.yy.c tabla_simbolos.c semantica.c || { echo "[ERROR] gcc falló"; exit 1; }
echo "[OK] slimc$EXE"

echo "== 2. Versión manual en C (respaldo y referencia)"
gcc $STATIC -Wall -o slimc_manual$EXE slimc_manual.c tabla_simbolos.c semantica.c || { echo "[ERROR] gcc falló"; exit 1; }
echo "[OK] slimc_manual$EXE"
echo
echo "Prueba:  ./slimc$EXE correcto.c      y      ./slimc$EXE errores.c"
echo "Todo:    ./probar.sh"
