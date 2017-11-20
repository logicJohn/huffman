
echo off
title My Test Batch File
::see the title at top.
echo Test file executed.
echo I am too lazy to write commands again and again
pause

g++ -g -w -o hello.exe trace.cpp

pause

echo  **************Compiling Complete****************

pause

hello.exe -t

pause
pause

