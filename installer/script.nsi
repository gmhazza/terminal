!include "MUI2.nsh"

!addplugindir "C:\Program Files (x86)\NSIS\EnVar_plugin\Plugins\x86-unicode"

!define APP_NAME "Termi"
!define APP_VERSION "0.0.2"

Name "${APP_NAME}"
OutFile "termi-${APP_VERSION}.exe"
InstallDir "$PROGRAMFILES\${APP_NAME}"

!define MUI_ABORTWARNING

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "license.txt"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section "Install"
    SetOutPath "$INSTDIR"
    File "..\README.md"

    ;SetOutPath "$INSTDIR\docs"
    ;File "..\docs\*"

    SetOutPath "$INSTDIR\bin"
    File "..\bin\*.exe"

    WriteUninstaller "Uninstall.exe"

    EnVar::AddValue "PATH" "$INSTDIR\bin"

SectionEnd

Section "Uninstall" 
    EnVar::DeleteValue "PATH" "$INSTDIR\bin"

    Delete "$INSTDIR\README.md"
    
    Delete "$INSTDIR\Uninstall.exe"

    ;Delete "$INSTDIR\docs\*"
    ;RMDir "$INSTDIR\docs"

    Delete "$INSTDIR\bin\*"
    RMDir "$INSTDIR\bin"

    RMDir "$INSTDIR"
SectionEnd