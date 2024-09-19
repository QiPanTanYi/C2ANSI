@echo off
setlocal

:: 检查是否提供了文件名参数
if "%~1"=="" (
    echo Usage: %0 filename.c
    exit /b 1
)

:: 获取当前日期和时间
for /f "delims=" %%i in ('powershell -Command "Get-Date -Format 'yyyy-MM-dd-HH:mm:ss"'') do set "dt=%%i"

:: 创建文件并写入日期时间注释和#include <stdio.h>
echo // 创建时间-- %dt% > "%~1"
echo #include ^<stdio.h^> >> "%~1"

:: 转换文件编码为 ANSI
ANSI.exe "%~1"

:: 使用 Vim 打开文件
vim "%~1"

endlocal
