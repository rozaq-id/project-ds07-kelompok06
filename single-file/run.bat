@echo off
echo Running Single-File SmartStudent System...

if exist SmartStudent-SingleFile.exe (
    echo Starting SmartStudent...
    SmartStudent-SingleFile.exe
) else (
    echo SmartStudent-SingleFile.exe not found! Please build first using:
    echo - build.bat
    pause
)
