@echo off
chcp 65001 >nul
cd /d "%~dp0proyecto-finalslimc\interfaz"
echo Abriendo la interfaz en http://127.0.0.1:8765  (no cierres esta ventana)
where py >nul 2>nul && (py servidor.py) || (python servidor.py)
pause
