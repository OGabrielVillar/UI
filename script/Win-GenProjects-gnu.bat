@echo off
pushd %~dp0\..\
call premake\bin\premake5.exe gmake2
popd
PAUSE
