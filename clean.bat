@echo off
echo Cleaning build files...

REM Remove executable files
if exist SmartStudent.exe (
    del SmartStudent.exe
    echo Deleted SmartStudent.exe
)

REM Remove Visual Studio object files
if exist *.obj (
    del *.obj
    echo Deleted *.obj files
)

if exist *.pdb (
    del *.pdb
    echo Deleted *.pdb files
)

if exist *.ilk (
    del *.ilk
    echo Deleted *.ilk files
)

echo.
echo Clean completed!
pause
