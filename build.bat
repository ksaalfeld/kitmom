echo off
cls

REM Adjust this path for your build environment!
PATH = D:\Programme\TDM-GCC-64\bin;%PATH%

CALL kitmom_win32.bat
CALL kitmom_win64.bat

echo done.
pause>nul
