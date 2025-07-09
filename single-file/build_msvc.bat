@echo off
echo Building SmartStudent System with Visual Studio Compiler...

REM Check if cl.exe is available
where cl.exe >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: cl.exe not found!
    echo Please run this from a Visual Studio Developer Command Prompt
    echo or run vcvarsall.bat first.
    echo.
    echo To setup environment, run one of these:
    echo   "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    echo   "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
    pause
    exit /b 1
)

REM Compile modular version using cl.exe
echo.
echo Compiling with MSVC...
cl.exe /EHsc /std:c++11 /nologo main.cpp /Fe:SmartStudent.exe

if %errorlevel% neq 0 (
    echo Error compiling with MSVC!
    pause
    exit /b 1
)

REM Clean up intermediate files
echo.
echo Cleaning up intermediate files...
del *.obj >nul 2>&1

echo.
echo Build successful with Visual Studio Compiler!
echo SmartStudent.exe is ready to run.
echo.
pause
