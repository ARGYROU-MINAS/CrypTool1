@echo off
if not x%1==x set LANG=%1
if x%LANG%==x set LANG=de

if x%OUTDIR%==x set OUTDIR=Debug

set HLP=hlp-%LANG%
set HM=%HLP%\multipad.hm

if exist makehelp.no goto :skip
if exist "%HLP%\makehelp.no" goto :skip

REM -- Zuerst Zuordnungsdatei der mit Microsoft Visual C++ erzeugten resource.h erstellen
echo // Von MAKEHELP.BAT erzeugte Hilfe-Zuordnungsdatei. Wird verwendet von multipad.HPJ. >%HM%
echo. >>%HM%
echo // Befehle (ID_* and IDM_*) >>%HM%
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>%HM%
echo. >>%HM%
echo // Eingabeaufforderungen (IDP_*) >>%HM%
makehm IDP_,HIDP_,0x30000 resource.h >>%HM%
echo. >>%HM%
echo // Ressourcen (IDR_*) >>%HM%
makehm IDR_,HIDR_,0x20000 resource.h >>%HM%
echo. >>%HM%
echo // Dialogfelder (IDD_*) >>%HM%
makehm IDD_,HIDD_,0x20000 resource.h >>%HM%
echo. >>%HM%
echo // Rahmen-Steuerelemente (IDW_*) >>%HM%
makehm IDW_,HIDW_,0x50000 resource.h >>%HM%
REM -- Hilfe erstellen f�r Projekt multipad

REM replace relative path with absolute one
find /V "mfc\include\Afxhelp.hm" <"%HLP%\multipad.hpj" >"%HLP%\multipad.tmp"
echo "#include %MSVCDir%\mfc\include\Afxhelp.hm" >>"%HLP%\multipad.tmp"

echo Creating Win32 Help File... Create empty "makehelp.no" or "%HLP%\makehelp.no" to skip

start /wait hcw /C /E /M "%HLP%\multipad.tmp"
if errorlevel 1 goto :Error
if not exist "%HLP%\CrypTool.hlp" goto :ErrorDatei
if not exist "%HLP%\CrypTool.cnt" goto :ErrorDatei
echo.

if exist %OUTDIR%\nul copy "%HLP%\CrypTool.hlp" %OUTDIR%\CrypTool-%LANG%.hlp >nul
if exist %OUTDIR%\nul copy "%HLP%\CrypTool.cnt" %OUTDIR%\CrypTool-%LANG%.cnt >nul
echo.
goto :done

:Error
echo %HLP%\multipad.hpj(1) : error: Problem beim Erstellen der Hilfedatei festgestellt: Hilfecompiler konnte nicht fehlerfrei compilieren
goto :done

:ErrorDatei
echo %HLP%\multipad.hpj(1) : error: Problem beim Erstellen der Hilfedatei festgestellt: Mindestens eine Datei wurde nicht erstellt
goto :done

:skip
echo Skipping help file generation. Remove "makehelp.no" and "%HLP%\makehelp.no" if this is not what you want
goto :done

:done
echo.
