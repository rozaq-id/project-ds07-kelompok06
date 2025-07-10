@echo off
echo Running Single-File SmartStudent System...

if exist SmartStudent.exe (
    echo Starting SmartStudent...
    SmartStudent.exe
) else (
    echo SmartStudent.exe not found! Please build first using:
    echo - build.bat
    pause
)
