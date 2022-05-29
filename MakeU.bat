@echo off
build\tasm32 /ml /m3 /z patch
rem brcc32 patcheur
build\tlink32 -x /Tpe /aa /c /V4.0 /o patch,patch,, build\import32.lib,,compil
del *.obj
del *.ilc
del *.ild
del *.ilf
del *.ils
del *.tds
build\upx -9 .\patch.exe
%1