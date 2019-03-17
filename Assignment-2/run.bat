@echo off
setlocal enabledelayedexpansion
g++ -std=c++11 .\main.cpp .\graph.cpp
.\a.exe 10000 100 0 140