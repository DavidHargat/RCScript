@echo off

:start
  echo.
  pause
  cls
:compile
  C:\MinGW\bin\gcc.exe main.c -o main
:run
  main.exe
  goto start