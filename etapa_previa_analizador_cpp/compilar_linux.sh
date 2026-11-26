#!/usr/bin/env bash
# Compila las dos versiones en Linux (Debian/Ubuntu/WSL). Uso: ./compilar_linux.sh
set -e
cd "$(dirname "$0")"

faltan=()
for h in g++ gcc flex bison; do command -v "$h" >/dev/null || faltan+=("$h"); done
if [ ${#faltan[@]} -gt 0 ]; then
  echo "Faltan: ${faltan[*]}"
  echo "Instala con:  sudo apt update && sudo apt install -y build-essential flex bison"
fi

if command -v g++ >/dev/null; then
  g++ -std=c++17 -O2 -Wall -Wextra analizador.cpp -o analizador
  echo "[OK] Version C++    -> ./analizador"
fi
if command -v flex >/dev/null && command -v bison >/dev/null && command -v gcc >/dev/null; then
  ( cd flex_bison && bison -d parser.y && flex lexer.l && gcc parser.tab.c lex.yy.c -o ../analizador_bison )
  echo "[OK] Version bison  -> ./analizador_bison"
fi
echo
echo "Prueba:  ./analizador prueba.c      y      ./analizador_bison prueba.c"
