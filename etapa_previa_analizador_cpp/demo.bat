@echo off
chcp 65001 >nul
color 0F
echo ===== 1. Programa correcto =====
analizador.exe prueba.c
echo.
echo ===== 2. Errores de directivas y funcion =====
analizador.exe prueba_errores.c
echo.
echo ===== 3. Errores lexicos y sintacticos =====
analizador.exe prueba_sintaxis.c
echo.
echo ===== 4. Interfaz completa =====
analizador.exe --ui prueba_errores.c
pause
