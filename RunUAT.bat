@echo off
setlocal

:: Detect Unreal Engine installation path by checking drives
set EnginePath=
for %%D in (C D E F G H) do (
    if exist "%%D:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\Build.bat" (
        set EnginePath=%%D:\Program Files\Epic Games\UE_5.4\Engine
        goto PathFound
    )
)

:PathFound
if "%EnginePath%"=="" (
    echo Unreal Engine installation not found. Please ensure it is installed under Program Files\Epic Games\UE_5.4\Engine.
    pause
    exit /b
)

:: The name of your project file (without the .uproject extension)
set ProjectName=Scraproots

::echo Pulling latest changes...
:: git pull origin main

echo Compiling C++ code if there are changes...
call "%EnginePath%\Build\BatchFiles\Build.bat" "%ProjectName%" Win64 Development "%CD%\%ProjectName%.uproject"

echo Running the project...
start "" "%EnginePath%\Binaries\Win64\UnrealEditor.exe" "%CD%\%ProjectName%.uproject"

endlocal