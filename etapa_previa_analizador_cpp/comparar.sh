#!/usr/bin/env bash
# Compara la salida de la version C++ con la de flex/bison en los 3 archivos de prueba.
# Uso: ./comparar.sh   (antes corre ./compilar_linux.sh)
cd "$(dirname "$0")"
for f in prueba prueba_errores prueba_sintaxis; do
  echo "=== $f.c"
  ./analizador --sin-color "$f.c" > /tmp/salida_cpp.txt;   c1=$?
  ./analizador_bison       "$f.c" > /tmp/salida_bison.txt; c2=$?
  if diff -u /tmp/salida_cpp.txt /tmp/salida_bison.txt > /tmp/dif.txt; then
    echo "Salida IDENTICA  (codigos de salida: C++=$c1, bison=$c2)"
  else
    echo "Salidas DISTINTAS (codigos: C++=$c1, bison=$c2). Diferencias:"; cat /tmp/dif.txt
  fi
done
