@echo off
setlocal enabledelayedexpansion

for /r %t in (*.cpp *.hpp *.c *.h) do clang-format -i -style=file "%t"

endlocal


