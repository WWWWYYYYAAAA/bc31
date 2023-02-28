@echo off
FORFILES /P .\ /M *.swp /C "cmd /c del /F /s /q @file"
