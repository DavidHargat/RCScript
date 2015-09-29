@echo off

:start
  echo.
  pause
  cls
:compile
  C:\MinGW\bin\gcc.exe ./src/main.c -o ./build/main
:run
  "./build/main.exe"
  goto start
  