@echo off
echo Running SmartStudent System...

if exist SmartStudent.exe (
    echo Starting SmartStudent...
    SmartStudent.exe
) else (
    echo SmartStudent.exe not found! Please build first using:
    echo - build_msvc.bat (for Visual Studio compiler)
    echo - build.bat (for g++ compiler)
    pause
)
