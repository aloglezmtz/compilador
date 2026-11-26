@echo off
chcp 65001 >nul
g++ -std=c++17 -O2 analizador.cpp -o analizador.exe
if errorlevel 1 (echo [ERROR] No se pudo compilar. Revisa que g++ este en el PATH. & exit /b 1)
echo [OK] Compilado: analizador.exe
