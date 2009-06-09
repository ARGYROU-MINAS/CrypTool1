;Include Modern UI

  !include "MUI.nsh"
  !include "WordFunc.nsh"
  !insertmacro WordFind
  !insertmacro un.WordFind

;--------------------------------
;General

  ;Name and file
  !define ProgramName "CrypTool"
  !define VersionInfo "1.4.21"
  
  Name "${ProgramName} ${VersionInfo}"
  OutFile "SetupCrypTool_${LANGUAGE_STR}.exe"
  BrandingText "(c) 1998-2008 Contributors"
;  Icon "..\CrypTool\res\idr_main.ico" ; does not work for some reason

  ;Default installation folder
  InstallDir "$PROGRAMFILES\${ProgramName}"   ; "$PROGRAMFILES\$(^NameDA)"

  Var ShortCutName
  
;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  !define MUI_WELCOMEFINISHPAGE_BITMAP CrypTool.bmp
  !define MUI_UNWELCOMEFINISHPAGE_BITMAP CrypTool.bmp
  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP CrypToolH.bmp

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "setup-${LANGUAGE_STR}\license-${LANGUAGE_STR}.rtf"
  !define MUI_PAGE_CUSTOMFUNCTION_LEAVE mui.DirectoryLeave
  !insertmacro MUI_PAGE_DIRECTORY
  !define MUI_FINISHPAGE_NOAUTOCLOSE
  !insertmacro MUI_PAGE_INSTFILES
  !define MUI_FINISHPAGE_RUN CrypTool.exe
  !define MUI_FINISHPAGE_SHOWREADME ReadMe-${LANGUAGE_STR}.txt
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !define MUI_PAGE_CUSTOMFUNCTION_LEAVE un.mui.ConfirmLeave
  !insertmacro MUI_UNPAGE_CONFIRM
  !define MUI_UNFINISHPAGE_NOAUTOCLOSE
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Macros
 
  !macro RegUpdate value_old key_new value_new

  ReadRegDWORD $0 HKCU Software\Cryptool\Settings\${key_new} ${value_new}
  IfErrors 0 +5 
  ReadRegDWORD $0 HKCU Software\Cryptool\Settings ${value_old}
  IfErrors +3 
  WriteRegDWORD  HKCU Software\Cryptool\Settings\${key_new} ${value_new} $0
  DeleteRegValue HKCU Software\Cryptool\Settings ${value_old}

  !macroend

;--------------------------------
;Select Language  

!ifndef LANGUAGE_STR
   !echo "ERROR: Please define LANGUAGE_STR with /D option!" 
   Abort ; EXIT
!endif

!if ${LANGUAGE_STR} == 'de' 
   !insertmacro MUI_LANGUAGE "German"
   !define SCN_CRYPTOOL		"CrypTool"
   !define SCL_CRYPTOOL		"CrypTool.exe"
   !define SCN_CRYPTOOL_HELP    "CrypTool-Hilfe"
   !define SCL_CRYPTOOL_HELP	"CrypTool-${LANGUAGE_STR}.chm"
   !define SCN_NUMBERSHARK	"Zahlenhai"
   !define SCL_NUMBERSHARK	"Zahlenhai.exe"
   !define SCN_NUMBERSHARK_HELP "Zahlenhai-Hilfe"
   !define SCL_NUMBERSHARK_HELP "NumberShark-${LANGUAGE_STR}.chm"
   !define SCN_AES_TOOL		"AES-Tool"
   !define SCL_AES_TOOL		"aestool.exe"
   !define SCN_SCRIPT		"Skript"
   !define SCL_SCRIPT		"script-${LANGUAGE_STR}.pdf"
   !define SCN_PRESENTATION	"Pr�sentation"
   !define SCL_PRESENTATION	"CrypToolPresentation-${LANGUAGE_STR}.pdf"
   !define SCN_README		"ReadMe"
   !define SCL_README 		"ReadMe-${LANGUAGE_STR}.txt"
   !define SCN_UNINSTALL	"Deinstallieren"
   !define SCL_UNINSTALL	"Uninstall.exe"
   !define URL		"http://www.cryptool.de/"
   !define UNINSTALL_PROMPT	"ist bereits installiert.$\n$\nBitte 'OK' klicken, um die vorherige Installation zu ersetzen; oder 'Abbrechen', um ein anderes Installationsverzeichnis zu w�hlen."
   !define UNINSTALL_PROMPT2    "Das Verzeichnis existiert bereits.$\n$\nBitte w�hlen Sie ein anderes, oder deinstallieren Sie das Programm in diesem Verzeichnis."
   !define UNINSTALL_CONFIRM	"Bei der Deinstallation werden alle Dateien im Programmverzeichnis gel�scht - auch von Ihnen erzeugte asymmetrische Schl�ssel und gespeicherte Beispieldateien.$\n$\nWenn Sie die Deinstallation hier abbrechen, k�nnen Sie erzeugte Schl�ssel mit dem bisher installierten CrypTool exportieren.$\n$\nSoll CrypTool wirklich deinstalliert werden?"
   !define UNINSTALL_RMPROGDIR_FAILED "Das Programmverzeichnisses konnte nicht (vollst�ndig) gel�scht werden.$\n$\nBitte l�schen Sie es manuell."
!else if ${LANGUAGE_STR} == 'en'
   !insertmacro MUI_LANGUAGE "English"
   !define SCN_CRYPTOOL		"CrypTool"
   !define SCL_CRYPTOOL		"CrypTool.exe"
   !define SCN_CRYPTOOL_HELP    "CrypTool Help"
   !define SCL_CRYPTOOL_HELP	"CrypTool-${LANGUAGE_STR}.chm"
   !define SCN_NUMBERSHARK	"Number Shark"
   !define SCL_NUMBERSHARK	"Number Shark.exe"
   !define SCN_NUMBERSHARK_HELP "Number Shark Help"
   !define SCL_NUMBERSHARK_HELP "NumberShark-${LANGUAGE_STR}.chm"
   !define SCN_AES_TOOL		"AES-Tool"
   !define SCL_AES_TOOL		"aestool.exe"
   !define SCN_SCRIPT		"Script"
   !define SCL_SCRIPT		"script-${LANGUAGE_STR}.pdf"
   !define SCN_PRESENTATION	"Presentation"
   !define SCL_PRESENTATION	"CrypToolPresentation-${LANGUAGE_STR}.pdf"
   !define SCN_README		"ReadMe"
   !define SCL_README 		"ReadMe-${LANGUAGE_STR}.txt"
   !define SCN_UNINSTALL	"Uninstall"
   !define SCL_UNINSTALL	"Uninstall.exe"
   !define URL		"http://www.cryptool.org/"
   !define UNINSTALL_PROMPT	"is already installed. $\n$\nClick 'OK' to remove the \
  previous version or 'Cancel' to choose another installation directory."
   !define UNINSTALL_PROMPT2    "This directory already exists.$\n$\nPlease select another directory, or uninstall the program in this directory first."
   !define UNINSTALL_CONFIRM	"The uninstallation will delete all files in the installation directory - even asymmetric keys generated by you and saved example files.$\n$\nIf you cancel now you'll be able to export generated keys with your existing CrypTool installation.$\n$\nDo you really want to uninstall CrypTool?"
   !define UNINSTALL_RMPROGDIR_FAILED "The program directory could not be deleted (completely).$\n$\nPlease remove it manually."
!else if ${LANGUAGE_STR} == 'pl'
   !insertmacro MUI_LANGUAGE "Polish"
   !define SCN_CRYPTOOL		"CrypTool"
   !define SCL_CRYPTOOL		"CrypTool.exe"
   !define SCN_CRYPTOOL_HELP    "CrypTool Help"
   !define SCL_CRYPTOOL_HELP	"CrypTool-${LANGUAGE_STR}.chm"
   !define SCN_NUMBERSHARK	"Number Shark"
   !define SCL_NUMBERSHARK	"Numbershark.exe"
   !define SCN_NUMBERSHARK_HELP "Number Shark Help"
   !define SCL_NUMBERSHARK_HELP "Numbershark_${LANGUAGE_STR}.chm"
   !define SCN_AES_TOOL		"AES-Tool"
   !define SCL_AES_TOOL		"aestool.exe"
   !define SCN_SCRIPT		"Script"
   !define SCL_SCRIPT		"script-${LANGUAGE_STR}.pdf"
   !define SCN_PRESENTATION	"Presentation"
   !define SCL_PRESENTATION	"CrypToolPresentation-${LANGUAGE_STR}.pdf"
   !define SCN_README		"ReadMe"
   !define SCL_README 		"ReadMe-${LANGUAGE_STR}.txt"
   !define SCN_UNINSTALL	"[i18n]Uninstall"
   !define SCL_UNINSTALL	"Uninstall.exe"
   !define URL		"http://www.cryptool.pl/"
   !define UNINSTALL_PROMPT	"jest ju� zainstalowany. $\n$\nKliknij 'OK', �eby usun�� poprzedni� wersje \
 lub 'Anuluj', aby okre�li� inny katalog instalacji."
   !define UNINSTALL_PROMPT2    "Taki katalog ju� istnieje. $\n$\nWybierz inny katalog, albo odinstaluj program z tego katalogu."
   !define UNINSTALL_CONFIRM	"Odinstalowanie programu oznacza skasowanie wszystkich plik�w w katalogu instalacyjnym (tak�e wygenerowanych przez Ciebie kluczy asymetrycznych i zapisanych przyk�ad�w).$\n$\n Przerywaj�c ten proces mo�esz skopiowa� te pliki w bezpieczne miejsce.$\n$\nCzy chcesz kontynuowa� odinstalowywanie programu CrypTool?"
   !define UNINSTALL_RMPROGDIR_FAILED "[i18n]The program directory could not be deleted (completely).$\n$\nPlease remove it manually."
!else
  !echo "ERROR: ...!"
  Abort ; EXIT
!endif

;--------------------------------
;Installer Sections

Section "CrypTool" 
; FileSystem:
; 	$INSTDIR == ...\$ShortCutName ; $ShortCutName is set in mui.DirectoryLeave 
; 	$SMPROGRAM\$ShortCutName ; in %allusersprofile% if writable, otherwise in the %userprofile%
; Registry:
;	HKLM\Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName
;	HKCR\aes
;	HKCR\AESToolFile

  SetOutPath "$INSTDIR"

  ${WordFind} $INSTDIR "\" "-1*}" $ShortCutName  ; FIXME '\' at the string end

  ;Files to install
  File /r setup-${LANGUAGE_STR}\*.*

  ;Allow all users to write into pse and examples directory
  ExecWait 'cacls "$INSTDIR\pse"  /t /e /g USERS:w' 
  ExecWait 'cacls "$INSTDIR\examples"  /t /e /g USERS:w' 

  SetShellVarContext all
  ClearErrors
  Call populateStartMenu
  IfErrors 0 startMenuDone
  ;SetShellVarContext all does not work -> try current
  RMDir /r "$SMPROGRAMS\$ShortCutName"
  SetShellVarContext current
  Call populateStartMenu
startMenuDone:

  ;File association for AES tool
  WriteRegStr HKCR ".aes" "" "AESToolFile"
  WriteRegStr HKCR "AESToolFile" "" "AES Tool File"
  WriteRegStr HKCR "AESToolFile\DefaultIcon" "" "$INSTDIR\aestool.exe,0"
  WriteRegStr HKCR "AESToolFile\shell" "" "open"
  WriteRegStr HKCR "AESToolFile\shell\open\command" "" '$INSTDIR\aestool.exe "%1"'
  ; open with:
  WriteRegStr HKCR "Applications\aestool.exe\shell\open\command" "" '$INSTDIR\aestool.exe "%1"'

  ; Add CrypTool to "Add or Remove Programs" in appwiz.cpl
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
                 "DisplayName" "$ShortCutName ${VersionInfo}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
                 "DisplayVersion" "${VersionInfo}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
                 "URLUpdateInfo" "${URL}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
                 "UninstallString" "$INSTDIR\uninstall.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
                 "DisplayIcon" "$INSTDIR\CrypTool.exe,0"  

  !insertmacro RegUpdate NoTipps Options\StartingOptions NoTipps
  !insertmacro RegUpdate SampleTextFile Options\StartingOptions SampleTextFile
  !insertmacro RegUpdate ADFGVX_IntroDialogue Cryptool\Settings\ADFGVX ShowIntro
  !insertmacro RegUpdate CRT_IntroDialogue Cryptool\Settings\CrtSecretSharing ShowIntro
  !insertmacro RegUpdate firstPosNull Cryptool\Settings\Hill OrdChrOffset
  !insertmacro RegUpdate useFirstCharFromAlph Cryptool\Settings\Hill PaddingDefaultChr
  !insertmacro RegUpdate ownCharForPadding Cryptool\Settings\Hill PaddingOwnChr
  !insertmacro RegUpdate alphCode Cryptool\Settings\Hill EditKeyChrMatrix
  !insertmacro RegUpdate DH_IntroDialogue Cryptool\Settings\DiffieHellman ShowIntro
  !insertmacro RegUpdate DH_InfoDialogue Crytool\Settings\DiffieHellman ShowInfo
  !insertmacro RegUpdate SignatureAttackHashAlgorithmID Cryptool\Settings\SignatureAttack HashAlgorithmID
  !insertmacro RegUpdate SignatureAttackSignificantBitLength Cryptool\Settings\SignatureAttack SignificantBitLength
  !insertmacro RegUpdate SignatureAttackModificationMethod Cryptool\Settings\SignatureAttack ModificationMethod
  !insertmacro RegUpdate SignatureAttackCheck1 Cryptool\Settings\SignatureAttack ModfiyBlankEOL
  !insertmacro RegUpdate SignatureAttackCheck3 Cryptool\Settings\SignatureAttack ModifyDoubleBlank
  !insertmacro RegUpdate SignatureAttackAttMethod Cryptool\Settings\SignatureAttack ModifyCharSet
  !insertmacro RegUpdate SignatureAttackTestMode Cryptool\Settings\SignatureAttack PerformTestRun
  !insertmacro RegUpdate SignificantBitLengthMIN Cryptool\Settings\SignatureAttack SignificantBitLengthMin
  !insertmacro RegUpdate SignificantBitLengthMAX Cryptool\Settings\SignatureAttack SignificantBitLengthMax
  !insertmacro RegUpdate SignificantBitLengthJump Cryptool\Settings\SignatureAttack SignificantBitLengthJump
  !insertmacro RegUpdate HashAlgorithmIDMIN Cryptool\Settings\SignatureAttack HashAlgorithmIDMin
  !insertmacro RegUpdate HashAlgorithmIDMAX Cryptool\Settings\SignatureAttack HashAlgorithmIDMax
  !insertmacro RegUpdate Attempts Cryptool\Settings\SignatureAttack Attempts
  !insertmacro RegUpdate AttemptsMAX Cryptool\Settings\SignatureAttack AttemptsMax 
  !insertmacro RegUpdate SignatureAttackHarmlessFile Cryptool\Settings\SignatureAttack HarmlessFile
  !insertmacro RegUpdate SignatureAttackDangerousFile Cryptool\Settings\SignatureAttack DangerousFile
  !insertmacro RegUpdate PQM_GL_MinimumLength Cryptool\Settings\PasswordGuidelines MinimumLength
  !insertmacro RegUpdate PQM_GL_MinimumDigits Cryptool\Settings\PasswordGuidelines MinimumDigits 
  !insertmacro RegUpdate PQM_GL_MinimumSpecial Cryptool\Settings\PasswordGuidelines MinimumSpecial
  !insertmacro RegUpdate PQM_GL_SpecialGroup Cryptool\Settings\PasswordGuidelines SpecialGroup
  !insertmacro RegUpdate RANDOM_GENERATOR_DATASIZE Cryptool\Settings\RandomGenerator GenerateBytes
  !insertmacro RegUpdate RANDOM_GENERATOR_ICG_N Cryptool\Settings\RandomGenerator ParamICG_N
  !insertmacro RegUpdate RANDOM_GENERATOR_ICG_P1 Cryptool\Settings\RandomGenerator ParamICG_P1
  !insertmacro RegUpdate RANDOM_GENERATOR_ICG_P2 Cryptool\Settings\RandomGenerator ParamICG_P2
  !insertmacro RegUpdate RANDOM_GENERATOR_OUTPUT_INTERNALSTATE Cryptool\Settings\RandomGenerator ShowInternalRandState
  !insertmacro RegUpdate RANDOM_GENERATOR_SEED Cryptool\Settings\RandomGenerator RandSeed
  !insertmacro RegUpdate RANDOM_GENERATOR_TYPE_ID Cryptool\Settings\RandomGenerator SelGenerator
  !insertmacro RegUpdate RANDOM_GENERATOR_LCG_P1 Cryptool\Settings\RandomGenerator ParamLCG_P1
  !insertmacro RegUpdate RANDOM_GENERATOR_LCG_P2 Cryptool\Settings\RandomGenerator ParamLCG_P2
  !insertmacro RegUpdate RANDOM_GENERATOR_LCG_N Cryptool\Settings\RandomGenerator ParamLCG_N
  !insertmacro RegUpdate RANDOM_GENERATOR_X2MODN_N Cryptool\Settings\RandomGenerator ParamX2MODN_N
  !insertmacro RegUpdate SecretSharing_Intro CrypTool\Settings\SecretSharing ShowIntro
  !insertmacro RegUpdate HybridEncryptionSCASignificantBits Cryptool\Settings\SideChannelAttack BitlengthSecret
  !insertmacro RegUpdate SCA_Keyword Cryptool\Settings\SideChannelAttack Keyword
  !insertmacro RegUpdate CreateReport_Top Cryptool\Settings\SizingDialog CreateReportTop
  !insertmacro RegUpdate CreateReport_Left Cryptool\Settings\SizingDialog CreateReportLeft
  !insertmacro RegUpdate CreateReport_Bottom Cryptool\Settings\SizingDialog CreateReportBottom
  !insertmacro RegUpdate CreateReport_Right Cryptool\Settings\SizingDialog CreateReportRight
  !insertmacro RegUpdate ShowPermutationKey Cryptool\Settings\Permutation ShowPermutationKey

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  ; LangString DESC_SecInst ${LANG_POLISH} "Install section."

  ;Assign language strings to sections
  ; !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  ; !insertmacro MUI_DESCRIPTION_TEXT ${SecInst} $(DESC_SecInst)
  ; !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  
; *******************
  
  ${un.WordFind} $INSTDIR "\" "-1*}" $ShortCutName

  ClearErrors
  RMDir /r "$INSTDIR"
  IfErrors 0 rmdirDone
  MessageBox MB_OK|MB_ICONEXCLAMATION "${UNINSTALL_RMPROGDIR_FAILED}"
rmdirDone:
  StrCmp $ShortCutName "" failSafe 0

  SetShellVarContext all
  IfFileExists $SMPROGRAMS\$ShortCutName\*.* 0 rmdirSMCurrent
  ClearErrors
  RMDir /r "$SMPROGRAMS\$ShortCutName" 
  IfErrors 0 rmdirSMDone
rmdirSMCurrent:
  SetShellVarContext current
  RMDir /r "$SMPROGRAMS\$ShortCutName" 
rmdirSMDone:
  ; Remove CrypTool to "Add or Remove Programs" in appwiz.cpl
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName"
failSafe:
  DeleteRegKey HKCR ".aes"
  DeleteRegKey HKCR "AESToolFile" 
  DeleteRegKey HKCR "Applications\aestool.exe"
SectionEnd

Function mui.DirectoryLeave
  
  ${WordFind} $INSTDIR "\" "-1*}" $ShortCutName
  ReadRegStr $R0 HKLM \
  "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
  "UninstallString"
  StrCmp $R0 "" done
 
  MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
  "$ShortCutName ${UNINSTALL_PROMPT}" \
  IDOK uninst
  Abort
  
;Run the uninstaller
uninst:
  ClearErrors
  ;We need to copy the uninstaller to a temp file manually, because 
  ; - ExecWait '$R0 _?=$INSTDIR' fails to delete the (running) installer
  ; - ExecWait '$R0' copies the installer to a temp file, but does not wait until it is finished
  ${WordFind} $R0 "\" "-1{" $R2 ; extract path from $R0 to $R2
  GetTempFileName $R1 ; create a temporary file $R1
  CopyFiles $R0 $R1.exe
  ExecWait '"$R1.exe" _?=$R2' ; call copy of uninstaller with target directory $R2

  IfErrors 0 done
  Abort ; Abort if uninstall failed

done:
  Delete $R1 ; delete (empty) file
  Delete $R1.exe ; delete temporary uninstaller copy
  IfFileExists $INSTDIR\*.* 0 install
  MessageBox MB_OK \
  "${UNINSTALL_PROMPT2}" \
  IDOK 0
  Abort
  
install:
 
FunctionEnd

Function un.mui.ConfirmLeave

  MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
  "${UNINSTALL_CONFIRM}" \
  IDOK continue
  Abort
 
continue:

FunctionEnd

Function populateStartMenu
  CreateDirectory "$SMPROGRAMS\$ShortCutName"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_CRYPTOOL}.lnk" 	 "$INSTDIR\${SCL_CRYPTOOL}"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_CRYPTOOL_HELP}.lnk" 	 "$INSTDIR\${SCL_CRYPTOOL_HELP}"	
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_NUMBERSHARK}.lnk" 	 "$INSTDIR\${SCL_NUMBERSHARK}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_NUMBERSHARK_HELP}.lnk" "$INSTDIR\${SCL_NUMBERSHARK_HELP}"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_AES_TOOL}.lnk" 	 "$INSTDIR\${SCL_AES_TOOL}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_SCRIPT}.lnk" 		 "$INSTDIR\${SCL_SCRIPT}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_PRESENTATION}.lnk" 	 "$INSTDIR\${SCL_PRESENTATION}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_README}.lnk" 		 "$INSTDIR\${SCL_README}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_UNINSTALL}.lnk" 	 "$INSTDIR\${SCL_UNINSTALL}"		
FunctionEnd
