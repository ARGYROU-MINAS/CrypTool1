;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;General

  ;Name and file
  Name "CrypTool"
  OutFile "CrypTool_pl_installer.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\CrypTool"

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "LicenceGPL-pl.txt"
;  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "Polish"

;--------------------------------
;Installer Sections

Section "CrypTool" SecInst

  SetOutPath "$INSTDIR"
  
  ;Files to install
  File /r *.*

  CreateDirectory "$SMPROGRAMS\CrypTool" 
  CreateShortCut "$SMPROGRAMS\CrypTool\CrypTool.lnk" "$INSTDIR\CrypTool.exe"
  CreateShortCut "$SMPROGRAMS\CrypTool\Unistall.lnk" "$INSTDIR\Uninstall.exe"
  CreateShortCut "$SMPROGRAMS\CrypTool\NumberShark.lnk" "$INSTDIR\Number Shark.exe"
  CreateShortCut "$SMPROGRAMS\CrypTool\Animal.lnk" "$INSTDIR\animal.bat"
  CreateShortCut "$SMPROGRAMS\CrypTool\AESTool.lnk" "$INSTDIR\aestool.exe"

  ;Store installation folder
  WriteRegStr HKCU "Software\CrypTool" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecInst ${LANG_POLISH} "Install section."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecInst} $(DESC_SecInst)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  RMDir /r "$INSTDIR"
  RMDir /r "$SMPROGRAMS\CrypTool" 

  DeleteRegKey HKCU "Software\CrypTool"

SectionEnd
