@echo off
chcp 65001 >nul
if not exist C:\msys64\usr\bin\bash.exe (
  echo No se encontro MSYS2 en C:\msys64. Instalalo desde msys2.org y lee LEEME_PRIMERO.txt
  pause
  exit /b 1
)
cd /d "%~dp0proyecto-finalslimc"
set MSYSTEM=UCRT64
set CHERE_INVOKING=1
C:\msys64\usr\bin\bash.exe -lc "./compilar.sh && ./probar.sh"
echo.
pause
