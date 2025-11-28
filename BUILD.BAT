@echo off
tasm MAIN.ASM
if errorlevel 1 goto end
tlink MAIN.OBJ
if errorlevel 1 goto end
MAIN
:end
