@echo off
goto check_Permissions

:check_Permissions
       net session >nul 2>&1
    if %errorLevel% == 0 (
        goto make_sym_link
    ) else (
        echo Se necesita ejecutar este script en modo administrador.
		goto end
    )
	
:make_sym_link
set /p project_main_folder="Ruta de la carpeta principal del proyecto: "
mklink /d "%project_main_folder%\Content\StarterContent" "%~dp0\StarterContent"

:end
pause