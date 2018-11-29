REM make sure GCC and following tools are added to %PATH%
REM -windres
REM -strip

SET TCL=.\tcl8.6\windows\32
SET SRC=.\source
SET OUT=.\output\windows\32
SET PRJ=kitmom
SET DIRS=%SRC%

SETLOCAL EnableDelayedExpansion

ECHO cleaning
if exist %OUT% goto 10
mkdir %OUT%
goto 20
:10
del %OUT%\*.o %OUT%\*.res %OUT%\*.dll
:20

REM build compiler include paths
SET INCS=-I"%TCL%\include"
FOR %%d IN (%DIRS%) DO (
    SET INCS=!INCS! -I"%%d"
)

SET CCFLAGS=-m32 -DUSE_TCL_STUBS %INCS% -Wall -Wextra -Os
SET LDFLAGS=-mwindows -L"%TCL%\lib" -static -static-libgcc -ffunction-sections -gc-sections -Wl,--add-stdcall-alias

REM compile all .c files and put generated .o files into %OUT% directory
SET OBJS=
FOR %%d IN (%DIRS%) DO (
    FOR %%f IN (%%d\*.c) DO (
        ECHO compiling: %%f
        gcc %CCFLAGS% -c %%f -o %OUT%\%%~nf.o
        SET OBJS=!OBJS! %OUT%\%%~nf.o
    )
)

ECHO generating resource files
windres --target pe-i386 -I"%TCL%\include" --input "%SRC%\%PRJ%.rc" --output "%OUT%\%PRJ%.res" --output-format=coff

ECHO generating target
gcc %CCFLAGS% %LDFLAGS% -shared %OBJS% "%OUT%\%PRJ%.res" "%SRC%\%PRJ%.def" -o "%OUT%\%PRJ%.dll" -lkernel32 -lsetupapi -ltclstub86
strip --strip-all "%OUT%\%PRJ%.dll"

ECHO updating
if exist ".\lib\%PRJ%" goto 30
mkdir ".\lib\%PRJ%"
:30
copy "%OUT%\%PRJ%.dll" ".\lib\%PRJ%\%PRJ%32.dll"
copy ".\%PRJ%\*" ".\lib\%PRJ%"
