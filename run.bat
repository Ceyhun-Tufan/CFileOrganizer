@echo off
set filename=%1
set outname=%2
gcc %filename% -o %outname% 
.\%outname%.exe
