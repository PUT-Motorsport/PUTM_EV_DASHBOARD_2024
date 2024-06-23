@echo off
setlocal

for /f "tokens=*" %%i in ('git diff --cached --name-only --diff-filter=ACM') do (
    for /r %%t in (*.cpp *.hpp *.c *.h) do (
      set "file=%%t"
      if "!file:Middlewares=!" == "%%t" if "!file:Drivers=!" == "%%t" clang-format -i -style=file "%%t"
    )
    git add %%i
)

echo Files formatted using clang-format.exe

endlocal