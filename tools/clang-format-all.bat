@echo off
setlocal enabledelayedexpansion

for /r %%t in (*.cpp *.hpp *.c *.h) do (
  set "file=%%t"
  if "!file:Middlewares=!" == "%%t" if "!file:Drivers=!" == "%%t" clang-format -i -style=file "%%t"
)

endlocal
