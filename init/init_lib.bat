@echo off
setlocal

:: 获取当前脚本的绝对路径
set "SCRIPT_DIR=%~dp0"
set "PYTHON_DIR=%SCRIPT_DIR%py"
set "VENV_DIR=%PYTHON_DIR%\.venv"
set "PYTHON_SCRIPT=%PYTHON_DIR%\init_dependencies.py"

:: --- 创建虚拟环境 ---
:: 检查 'py' 目录是否存在，如果不存在则创建它
if not exist "%PYTHON_DIR%" (
    echo 目录 'py' 不存在，正在创建...
    mkdir "%PYTHON_DIR%"
)

:: 检查虚拟环境是否已存在
if exist "%VENV_DIR%" (
    echo 虚拟环境 '%VENV_DIR%' 已存在。跳过创建。
) else (
    :: 检查 python.exe 命令是否存在
    where python >nul 2>nul
    if %errorlevel% neq 0 (
        echo 错误：找不到 python。请先安装它。
        exit /b 1
    )

    echo 正在创建虚拟环境 '%VENV_DIR%'...
    python -m venv "%VENV_DIR%"
    if %errorlevel% neq 0 (
        echo 错误：无法创建虚拟环境。
        exit /b 1
    )
    echo 已成功创建虚拟环境 '%VENV_DIR%'。
)

:: --- 激活并运行脚本 ---
:: 检查 Python 脚本是否存在
if not exist "%PYTHON_SCRIPT%" (
    echo 错误：找不到 Python 脚本 '%PYTHON_SCRIPT%'。
    exit /b 1
)

:: 激活并运行脚本
echo 正在激活虚拟环境并运行 '%PYTHON_SCRIPT%'...
call "%VENV_DIR%\Scripts\activate.bat"
if %errorlevel% neq 0 (
    echo 错误：无法激活虚拟环境。
    exit /b 1
)

python "%PYTHON_SCRIPT%"

:: 脚本执行完毕后，取消激活虚拟环境
deactivate

echo 脚本执行完毕.
endlocal