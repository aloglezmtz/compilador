#!/usr/bin/env bash
# Verifica correcto.c (ACCEPT) y los 7 errores semánticos esperados de errores.c.
# Uso: ./probar.sh        (antes compila con ./compilar.sh o make)
cd "$(dirname "$0")" || exit 1
EXE=""; [ "$OS" = "Windows_NT" ] && EXE=".exe"
fallos=0; probados=0
for prog in slimc slimc_manual; do
  if [ ! -x "./$prog$EXE" ]; then echo "(se omite $prog: no está compilado)"; continue; fi
  probados=$((probados+1)); echo "=== $prog"
  salida=$("./$prog$EXE" correcto.c)
  if echo "$salida" | grep -qF "ACCEPT"; then echo "  PASS  correcto.c -> ACCEPT"
  else echo "  FAIL  correcto.c no fue aceptado"; fallos=$((fallos+1)); fi
  salida=$("./$prog$EXE" errores.c)
  while IFS= read -r esperado; do
    [ -z "$esperado" ] && continue
    if echo "$salida" | grep -qF "$esperado"; then echo "  PASS  $esperado"
    else echo "  FAIL  falta: $esperado"; fallos=$((fallos+1)); fi
  done < esperado_errores.txt
  n=$(echo "$salida" | grep -c "Error semántico")
  if [ "$n" -eq 7 ]; then echo "  PASS  exactamente 7 errores semánticos"
  else echo "  FAIL  se esperaban 7 errores semánticos y hubo $n"; fallos=$((fallos+1)); fi
done
echo
if [ "$probados" -eq 0 ]; then echo "Nada que probar: compila primero."; exit 2; fi
if [ "$fallos" -eq 0 ]; then echo "TODO BIEN: $probados versión(es) pasan las pruebas."; else echo "HAY $fallos FALLO(S)."; exit 1; fi
