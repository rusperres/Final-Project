tasm TEST.ASM
if errorlevel 1 goto end
tlink TEST.OBJ
if errorlevel 1 goto end
TEST
:end
