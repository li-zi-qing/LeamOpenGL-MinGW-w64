import shutil
import subprocess
import sys
import json
import zipfile
import urllib.parse
import warnings
import platform
import os
from pathlib import Path

# 定义安装路径
project_root = Path(__file__).resolve().parent

VENV_NAME = '.venv'
REQUIREMENTS_FILE = 'requirements.txt'

PATH_FLAG = ":P"
APP_FLAG = ":A"
SP_FLAG = ":SP"
SKIP_CHECK_PATH_FLAG = ["output"]

CUSTOM_ENV = {
    "PATH": ''
}

# 将相对路径转化为绝对路径
def to_abs_path(path):
    return (project_root / path).resolve()

# 自动安装 requirements.txt 中的依赖
def install_requirements():
    """
    检查并安装 requirements.txt 中的依赖。
    """
    print("--------------------------------------------------")
    print("检查并安装 Python 依赖...")
    req_path = to_abs_path(REQUIREMENTS_FILE)
    if not req_path.exists():
        print("警告：找不到 requirements.txt 文件。跳过依赖安装。")
        return

    # 获取当前虚拟环境的 Python 解释器路径
    venv_python = sys.executable
    if not venv_python:
        print("错误：无法找到当前运行的 Python 解释器。")
        sys.exit(1)

    # 使用该解释器和 pip 安装依赖
    try:
        run_command([venv_python, "-m", "pip", "install", "-r", req_path])
        print("Python 依赖安装完成。")
    except Exception as e:
        print(f"错误：安装依赖失败 - {e}")
        sys.exit(1)

def check_conversion_paths(data, flag = ''):
    if isinstance(data, dict):
        temp_data = {}
        for name, value in data.items():
            flag = ''
            temp_name = name
            if PATH_FLAG in name:
                temp_name = str(name).replace(PATH_FLAG, "")
                flag = PATH_FLAG
            elif APP_FLAG in name:
                temp_name = str(name).replace(APP_FLAG, "")
                flag = APP_FLAG
            elif name in SKIP_CHECK_PATH_FLAG:
                flag = SKIP_CHECK_PATH_FLAG
            elif SP_FLAG in name:
                temp_name = str(name).replace(SP_FLAG, "")
                flag = SP_FLAG
            temp_data[temp_name] = check_conversion_paths(value, flag)
        return temp_data
    elif isinstance(data, list):
        return [check_conversion_paths(item) for item in data]
    else:
        if flag == PATH_FLAG:
            abs_path = to_abs_path(data)
            if not abs_path.exists():
                warnings.warn(f"路径 {abs_path} 不是一个有效的路径...请检查路径...")
            return str(abs_path)
        elif flag == APP_FLAG:
            abs_path = to_abs_path(data)
            app_name = abs_path.name.replace(".exe", "")
            if platform.system() == "Windows":
                abs_path = to_abs_path(abs_path.parent / (app_name + ".exe"))
            if abs_path.exists():
                return str(abs_path)
            elif shutil.which(app_name):
                warnings.warn(f"路径 {abs_path} 不是一个有效的应用程序路径...使用系统的该应用程序...")
                return str(app_name)
            else:
                warnings.warn(f"路径 {abs_path} 不是一个有效的应用程序路径且系统中不存在该应用程序...")
                sys.exit(1)
        elif APP_FLAG in data:
            data = str(data).replace(APP_FLAG, "")
            data = data.replace(".exe", "")
            if platform.system() == "Windows":
                data = f"{data}.exe"
            if "=" in data:
                data = data.split('=')
                abs_path = to_abs_path(data[-1])
                app_name = abs_path.name.replace(".exe", "")
                if abs_path.exists():
                    return f"{data[0]}={str(abs_path)}"
                elif shutil.which(app_name):
                    warnings.warn(f"路径 {abs_path} 不是一个有效的应用程序路径...使用系统的该应用程序...")
                    return f"{data[0]}={str(app_name)}"
                else:
                    warnings.warn(f"路径 {abs_path} 不是一个有效的应用程序路径且系统中不存在该应用程序...")
                    sys.exit(1)
            else:
                abs_path = to_abs_path(data)
                app_name = abs_path.name.replace(".exe", "")
                if abs_path.exists():
                    return str(abs_path)
                elif shutil.which(app_name):
                    warnings.warn(f"路径 {abs_path} 不是一个有效的应用程序路径...使用系统的该应用程序...")
                    return str(app_name)
                else:
                    warnings.warn(f"路径 {abs_path} 不是一个有效的应用程序路径且系统中不存在该应用程序...")
                    sys.exit(1)
        elif PATH_FLAG in data:
            data = str(data).replace(PATH_FLAG, "")
            if "=" in data:
                data = data.split('=')
                abs_path = to_abs_path(data[-1])
                if not abs_path.exists():
                    warnings.warn(f"路径 {abs_path} 不是一个有效的路径...请检查路径...")
                return f"{data[0]}={str(abs_path)}"
            else:
                abs_path = to_abs_path(data)
                if not abs_path.exists():
                    warnings.warn(f"路径 {abs_path} 不是一个有效的路径...请检查路径...")
                return str(abs_path)
        elif SP_FLAG in data:
            data = str(data).replace(SP_FLAG, "")
            return str(to_abs_path(data))
        elif flag == SKIP_CHECK_PATH_FLAG or flag == SP_FLAG:
            abs_path = to_abs_path(data)
            return str(abs_path)
        else:
            return str(data)

# 解析 GLAD 的永久链接.
def parse_glad_url(glad_url):
    """
    解析 GLAD 永久 URL 以提取配置字典。
    参数：
        glad_url （str）：来自 GLAD 网站的永久 URL。
    返回：
        dict：包含 GLAD 配置的字典。
    """
    # 1.拆分 URL 以获取哈希部分
    parts = urllib.parse.urlparse(glad_url)
    if not parts.fragment:
        print("URL 不包含配置哈希.")
        return None

    # 2.从哈希片段解析查询字符串
    # parse_qs 自动处理 URL 解码和多个值
    query_params = urllib.parse.parse_qs(parts.fragment)

    # 3.清理字典以匹配所需的格式
    config = {}
    for key, value_list in query_params.items():
        if key in ['generator', 'version_string', 'spec_string']:
            # 这些字段是单个字符串
            config[key] = value_list[0]
        else:
            # 其他字段（api、profile、extensions、options）为列表
            # 我们需要拆分逗号分隔的值
            flat_list = []
            for item in value_list:
                flat_list.extend(item.split(','))
            config[key] = flat_list

    # 添加任何缺失的键以确保最终字典完整
    # 下载脚本期望这些密钥存在
    config.setdefault('extensions', [])
    config.setdefault('options', [])
    config.setdefault('profile', [])
    config.setdefault('api', [])

    return config

# 运行 CMake 命令.
def run_command(command, cwd=None):
    """
    运行一个 shell 命令并检查错误。
    参数:
        command (List[str]): 命令.
    """
    str_command = [str(item) for item in command]
    message_command = ' '.join(str_command)
    print(f"运行命令: {message_command}")

    custom_env = CUSTOM_ENV
    env = os.environ.copy()
    if custom_env:
        for name, value in custom_env.items():
            if name == 'PATH':
                if isinstance(value, list):
                    for path in value:
                        env[name] = f"{path}{os.pathsep}{env.get(name, '')}"
                else:
                    env[name] = f"{value}{os.pathsep}{env.get(name, '')}"
            else:
                # 否则，直接赋值
                env[name] = value

    try:
        subprocess.run(str_command, check=True, cwd=cwd, env=env, text=True, stdout=sys.stdout, stderr=sys.stderr)
    except subprocess.CalledProcessError as e:
        str_e = ' '.join(e.cmd)
        print(f"命令失败并出现错误: {str_e}", file=sys.stderr)
        sys.exit(1)

# 下载资源文件.
def download_source(url, download_save_path):
    """
    使用 urllib.request 从指定 URL 下载文件并保存到本地。
    Args:
        url (str): 文件的下载链接.
        download_save_path (LiteralString | str | bytes): 保存到那个路径(包括文件名).
    """
    # 获取文件名
    filename = str(Path(download_save_path).name)

    if 'glad' in filename:
        generate_url = "https://gen.glad.sh/generate"
        print("正在模拟表单提交，向服务器发送配置...")
        try:
            form_data = parse_glad_url(url)

            # 发送 POST 请求，但禁用自动重定向，以便我们手动处理
            response = requests.post(generate_url, data=form_data, timeout=60, allow_redirects=False)
            response.raise_for_status()

            # 检查是否收到了重定向响应 (状态码 301, 302, 303, 307, 308)
            if response.is_redirect:
                redirect_url = response.url.replace('/generate', '') + response.headers.get('Location')
                final_download_url = f"{redirect_url}glad.zip"
                print(f"服务器已响应，正在从以下链接下载文件: {final_download_url}")

                # 使用最终的下载 URL 发送 GET 请求
                download_response = requests.get(final_download_url, timeout=60)
                download_response.raise_for_status()

                # 将文件内容写入本地
                path = Path(download_save_path).parent
                path.mkdir(parents=True, exist_ok=True)
                with open(download_save_path, 'wb') as f:
                    f.write(download_response.content)
                print(f"下载成功！文件已保存为 '{download_save_path}'")
                print(f"文件大小：{Path(download_save_path).stat().st_size / 1024 / 1024} MB")
            else:
                print("错误: 服务器未返回重定向响应。")
                print("响应状态码:", response.status_code)

        except requests.exceptions.RequestException as e:
            print(f"请求失败: {e}")
            print("请检查你的配置参数和网络连接。")

    else:
        print(f"正在从 '{url}' 下载...")
        # 确保保存文件的目录存在
        path = Path(download_save_path).parent
        path.mkdir(parents=True, exist_ok=True)
        try:
            # 发送 GET 请求，启用流式下载，以便处理大文件
            response = requests.get(url, stream=True, timeout=60)

            # 检查响应状态码是否成功 (200 OK)
            response.raise_for_status()

            # 将文件内容分块写入本地文件
            with open(download_save_path, 'wb') as f:
                for chunk in response.iter_content(chunk_size=8192):
                    f.write(chunk)
            print(f"文件 '{download_save_path}' 下载成功！")
            print(f"文件大小：{Path(download_save_path).stat().st_size / 1024 / 1024} MB")
        except Exception as e:
            print(f"下载失败：发生错误 - {e}")
            shutil.rmtree(download_save_path)

# 解压资源文件
def unzip_file(zip_path, extract_to):
    """
    解压 .zip 文件到指定目录。
    参数:
        zip_path (str): .zip 文件的完整路径。
        extract_to (str): 解压的目标目录。
    """
    try:
        # 确保目标目录存在，如果不存在则创建
        Path(extract_to).mkdir(parents=True, exist_ok=True)
        print(f"正在解压 {zip_path} 到 {extract_to}...")
        # 使用 with 语句确保文件被正确关闭
        with zipfile.ZipFile(zip_path, 'r') as zip_ref:
            zip_ref.extractall(extract_to)
        print("文件解压成功！")

    except zipfile.BadZipFile:
        print(f"错误：'{zip_path}' 不是一个有效的 .zip 文件。")
    except FileNotFoundError:
        print(f"错误：文件或目录未找到。请检查路径。")
    except Exception as e:
        print(f"解压时发生未知错误: {e}")

def main():
    """
    主函数，用于下载、构建和安装依赖库。
    """

    # 定义配置文件的路径
    json_file = to_abs_path("config.json")

    try:
        with open(str(json_file), 'r', encoding='utf-8') as f:
            json_data = json.load(f)
    except FileNotFoundError:
        print(f"错误: 文件 '{json_file}' 未找到。")
        sys.exit(1)
    except json.JSONDecodeError:
        print(f"错误: 文件 '{json_file}' 格式不正确。")
        sys.exit(1)

    json_data = check_conversion_paths(json_data)

    # 默认配置
    cmake_generator = 'Ninja'
    cmake_path = "cmake"
    cmake_defines = {
        "CMAKE_C_COMPILER": "gcc",
        "CMAKE_CXX_COMPILER": "g++",
        "CMAKE_INSTALL_PREFIX": f"{str(project_root / Path("../../libGlobal").resolve())}",
        "CMAKE_MAKE_PROGRAM": ''
    }

    if 'build_config' in json_data:
        # 读取 build_config.
        build_config = json_data.get('build_config')

        # 替换默认值并插入新值
        if "generator" in build_config:
            cmake_generator = str(build_config.get("generator"))
        if "cmake_path" in build_config:
            cmake_path = build_config.get("cmake_path")
        if "custom_env" in build_config:
            custom_env = build_config.get("custom_env")
            for name, value in custom_env.items():
                CUSTOM_ENV[name] = value

        # 插入自定义配置项
        for name, value in build_config.get('define').items():
            cmake_defines[name] = value

        # 删除 json_data 中 build_config
        del json_data['build_config']

    # 定义库文件的安装路径.
    install_root = to_abs_path(cmake_defines.get("CMAKE_INSTALL_PREFIX"))
    print(f"install_root: {install_root}")
    del cmake_defines["CMAKE_INSTALL_PREFIX"]

    # 转换 cmake_defines 为 cmake_defines_list.
    cmake_defines_list = []
    for name in cmake_defines.keys():
        cmake_defines_list.append(f"-D{name}={cmake_defines[name]}")

    # 确保安装目录存在
    install_root.mkdir(parents=True, exist_ok=True)
    print(f"安装根目录: {install_root}")

    for name, config in json_data.items():
        # 定义源代码和构建目录
        source_dir = to_abs_path(project_root / "_deps_source" / name)
        build_dir = to_abs_path(project_root / "_deps_build" / name)

        # 定义每个库的独立安装前缀
        install_prefix = install_root / name

        print("-" * 50)
        print(f"处理库 | 资源文件: {name}")

        if 'cmake_args' in config or 'copy_file_list' in config:

            # 下载源代码
            if not source_dir.exists():
                print(f"从 {config['repo']} 克隆 {name}...")
                run_command(["git", "clone", "--depth", "1", "--branch", config['tag'], config['repo'], source_dir])
            else:
                print(f"{name} 的源代码已经存在...跳过克隆.")

            if 'cmake_args' in config:

                # 处理 cmake_args 参数.
                cmake_args = config.get("cmake_args")
                for index, arg in enumerate(cmake_args):
                    if "-D" in arg:
                        cmake_args[index] = arg
                    else:
                        cmake_args[index] = f"-D{arg}"

                if not install_prefix.exists():
                    # 运行 CMake 配置，并显式指定 Ninja 和 MinGW-w64 编译器
                    cmake_command = [
                        f"{str(cmake_path)}",
                        "-G", str(cmake_generator),
                        "-S", str(source_dir),
                        "-B", str(build_dir),
                        f"-DCMAKE_INSTALL_PREFIX={str(install_prefix)}",
                    ]
                    cmake_command.extend(cmake_defines_list)
                    cmake_command.extend(cmake_args)
                    run_command(cmake_command)

                    # 运行 CMake 构建
                    run_command(["cmake", "--build", str(build_dir)])

                    # 运行 CMake 安装
                    install_prefix.mkdir(parents=True, exist_ok=True)
                    run_command(["cmake", "--install", str(build_dir)])
                    print(f"安装 {name} 到 {install_prefix} 成功!")

                else:
                    print(f"库 ‘{name}’ 库文件已存在...跳过构建和安装.")
            else:
                if not install_prefix.exists():
                    print(f"{name} 是一个仅标头库，跳过 CMake 构建...")
                    install_prefix.mkdir(parents=True, exist_ok=True)
                    for file in config.get('copy_file_list'):
                        # 拷贝资源文件
                        if "name" in file:
                            copy_file_path = to_abs_path(source_dir / file.get("name"))
                            include_path = to_abs_path(install_prefix / "include" / file.get("name"))
                            include_path.parent.mkdir(parents=True, exist_ok=True)
                            shutil.copyfile(copy_file_path, include_path)
                            print(f"已成功将 {copy_file_path} 复制到 {include_path}")
                        else:
                            warnings.warn(f"{name} 库的指定文件不存在")
                            break

                        # 生成cpp文件
                        if "cpp_template" in file:
                            src_path = to_abs_path(install_prefix / "src" / file.get("name").replace(".h", ".cpp"))
                            to_abs_path(src_path.parent).mkdir(parents=True, exist_ok=True)
                            with open(src_path, "w") as f:
                                f.write(str(file.get('cpp_template')))
                            print(f"已成功生成 stb_image.cpp 到 {src_path.parent}")
                else:
                    print(f"库 ‘{name}’ 已存在...跳过拷贝")
        elif 'format' in config:
            url = config['url']
            format_value = config['format']
            filename = name + format_value
            download_save_path = project_root / "_deps_source" / name / filename
            output_path = project_root / config['output']

            if not download_save_path.exists():
                download_source(url, download_save_path)
            else:
                print(f"{name} 的压缩包已经存在...跳过下载.")

            if not output_path.exists():
                unzip_file(download_save_path, output_path)
            else:
                print(f"{name} 库已经存在...跳过解压.")
        else:
            print(f"配置项 ’{name}‘ 不是有效的配置项.")

    print("-" * 50)
    print("所有依赖项都已成功构建和安装.")


if __name__ == "__main__":
    install_requirements()
    import requests
    main()
