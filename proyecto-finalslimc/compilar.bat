@echo off
rem Doble clic: compila SlimC usando MSYS2 UCRT64 (instalado en C:\msys64)
chcp 65001 >nul
cd /d "%~dp0"
set MSYSTEM=UCRT64
set CHERE_INVOKING=1
C:\msys64\usr\bin\bash.exe -lc "./compilar.sh"
pause
