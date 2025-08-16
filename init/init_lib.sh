#!/bin/bash

# 获取当前脚本的绝对路径
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# 定义虚拟环境目录和Python脚本的路径
VENV_DIR="$SCRIPT_DIR/py/.venv"
PYTHON_SCRIPT="$SCRIPT_DIR/py/init_dependencies.py"

# --- 创建虚拟环境 ---
# 检查 'py' 目录是否存在，如果不存在则创建它
if [ ! -d "$SCRIPT_DIR/py" ]; then
    echo "目录 'py' 不存在，正在创建..."
    mkdir -p "$SCRIPT_DIR/py"
fi

# 检查虚拟环境是否已存在
if [ -d "$VENV_DIR" ]; then
    echo "虚拟环境 '$VENV_DIR' 已存在。跳过创建。"
else
    # 检查 python3 命令是否存在
    if ! command -v python3 &> /dev/null; then
        echo "错误：找不到 python3。请先安装它。"
        exit 1
    fi

    echo "正在创建虚拟环境 '$VENV_DIR'..."
    python3 -m venv "$VENV_DIR"

    # 检查创建是否成功
    # shellcheck disable=SC2181
    if [ $? -ne 0 ]; then
        echo "错误：无法创建虚拟环境。"
        exit 1
    fi
    echo "已成功创建虚拟环境 '$VENV_DIR'。"
fi

# --- 激活并运行脚本 ---
# 根据操作系统确定正确的激活脚本
if [ -f "$VENV_DIR/Scripts/activate" ]; then
    # 适用于 Windows (Git Bash/MinGW)。
    ACTIVATE_SCRIPT="$VENV_DIR/Scripts/activate"
elif [ -f "$VENV_DIR/bin/activate" ]; then
    # 适用于 Linux 和 macOS。
    ACTIVATE_SCRIPT="$VENV_DIR/bin/activate"
else
    echo "错误：找不到虚拟环境激活脚本。"
    exit 1
fi

echo "正在激活虚拟环境..."
# shellcheck disable=SC1090
source "$ACTIVATE_SCRIPT"

# 检查 Python 脚本是否存在
if [ ! -f "$PYTHON_SCRIPT" ]; then
    echo "错误：找不到 Python 脚本 '$PYTHON_SCRIPT'。"
    # 在退出前取消激活
    deactivate
    exit 1
fi

# 使用已激活的虚拟环境中的 Python 解释器来运行脚本
echo "正在使用虚拟环境运行 '$PYTHON_SCRIPT'..."
python "$PYTHON_SCRIPT"

# 脚本执行完毕后，取消激活虚拟环境
deactivate

echo "脚本执行完毕."