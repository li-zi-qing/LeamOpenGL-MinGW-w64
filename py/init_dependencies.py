import os
import subprocess
import shutil
import sys
import urllib.request
import json
import zipfile
import urllib.parse

def ensure_requests_is_installed():
    """
    检查 requests 库是否已安装，如果未安装，则自动下载并安装。
    """
    try:
        # 尝试导入 requests
        import requests
        print("requests 库已安装。")
    except ImportError:
        print("requests 库未找到，正在尝试安装...")
        try:
            # 使用 pip 安装 requests
            subprocess.check_call([sys.executable, "-m", "pip", "install", "requests"])
            print("requests 库安装成功！")
        except subprocess.CalledProcessError as e:
            print(f"安装 requests 失败: {e}")
            print("请手动运行 'pip install requests' 来安装。")

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

def run_command(command, cwd=None):
    """
    运行一个 shell 命令并检查错误。
    """
    print(f"运行命令: {' '.join(command)}")
    try:
        subprocess.run(command, check=True, cwd=cwd, text=True, stdout=sys.stdout, stderr=sys.stderr)
    except subprocess.CalledProcessError as e:
        print(f"命令失败并出现错误: {e}", file=sys.stderr)
        sys.exit(1)

def download_source(url, download_save_path):
    """
    使用 urllib.request 从指定 URL 下载文件并保存到本地。
    Args:
        url (str): 文件的下载链接.
        download_save_path (LiteralString | str | bytes): 保存到那个路径(包括文件名).
    """
    # 获取文件名
    filename = os.path.basename(download_save_path)

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
                path = os.path.dirname(download_save_path)
                os.makedirs(path, exist_ok=True)
                with open(download_save_path, 'wb') as f:
                    f.write(download_response.content)
                print(f"下载成功！文件已保存为 '{download_save_path}'")

            else:
                print("错误: 服务器未返回重定向响应。")
                print("响应状态码:", response.status_code)

        except requests.exceptions.RequestException as e:
            print(f"请求失败: {e}")
            print("请检查你的配置参数和网络连接。")
    else:
        try:
            print(f"正在从 '{url}' 下载...")
            path = os.path.dirname(download_save_path)
            os.makedirs(path, exist_ok=True)
            # 发送请求并下载文件
            urllib.request.urlretrieve(url, download_save_path)
            print(f"文件 '{download_save_path}' 下载成功！")
            print(f"文件大小：{os.path.getsize(download_save_path)} 字节")
        except Exception as e:
            print(f"下载失败：发生错误 - {e}")

def unzip_file(zip_path, extract_to):
    """
    解压 .zip 文件到指定目录。
    参数:
        zip_path (LiteralString | str | bytes): .zip 文件的完整路径。
        extract_to (LiteralString | str | bytes): 解压的目标目录。
    """
    try:
        # 确保目标目录存在，如果不存在则创建
        os.makedirs(extract_to, exist_ok=True)
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

    # 定义安装路径
    project_root = os.path.dirname(os.path.abspath(__file__))
    # 定义库文件的安装路径
    install_root = os.path.join(project_root, "../libGlobal")
    # 定义配置文件的路径
    json_file = os.path.join(project_root, "url.json")

    try:
        with open(json_file, 'r', encoding='utf-8') as f:
            json_data = json.load(f)
        # 确保安装目录存在
        os.makedirs(install_root, exist_ok=True)
        print(f"安装根目录: {install_root}")
        for name, config in json_data.items():
            if 'cmake_args' in config:
                print("-" * 50)
                print(f"处理库: {name}")

                # 定义源代码和构建目录
                source_dir = os.path.join(project_root, "_deps_source", name)
                build_dir = os.path.join(project_root, "_deps_build", name)

                # 定义每个库的独立安装前缀
                install_prefix = os.path.join(install_root, name)

                # 下载源代码
                if not os.path.exists(source_dir):
                    print(f"从 {config['repo']} 克隆 {name}...")
                    run_command(["git", "clone", "--depth", "1", "--branch", config['tag'], config['repo'], source_dir])
                else:
                    print(f"{name} 的源代码已经存在...跳过克隆.")

                # 清理并创建构建目录
                if os.path.exists(build_dir):
                    shutil.rmtree(build_dir)
                    os.makedirs(build_dir)

                # 运行 CMake 配置，并显式指定 Ninja 和 MinGW-w64 编译器
                cmake_command = [
                    "cmake",
                    "-S", source_dir,
                    "-B", build_dir,
                    "-G", "Ninja",  # 使用 Ninja 生成器
                    "-DCMAKE_C_COMPILER=gcc",  # 指定 C 编译器
                    "-DCMAKE_CXX_COMPILER=g++",  # 指定 C++ 编译器
                    f"-DCMAKE_INSTALL_PREFIX={install_prefix}",
                ]
                cmake_command.extend(config["cmake_args"])
                run_command(cmake_command)

                # 运行 CMake 构建
                run_command(["cmake", "--build", build_dir])

                # 运行 CMake 安装
                run_command(["cmake", "--install", build_dir])
                print(f"安装 {name} 到 {install_prefix} 成功!")
            elif 'format' in config:
                url = config['url']
                format_value = config['format']
                filename = name + format_value
                download_save_path = os.path.join(project_root, "_deps_source", name, filename)
                output_path = os.path.join(project_root, config['output'])
                if not os.path.exists(download_save_path):
                    download_source(url, download_save_path)
                if not os.path.exists(output_path):
                    unzip_file(download_save_path, output_path)
            else:
                print(f"配置项 ’{name}‘ 不是有效的配置项.")
    except FileNotFoundError:
        print(f"错误: 文件 '{json_file}' 未找到。")
    except json.JSONDecodeError:
        print(f"错误: 文件 '{json_file}' 格式不正确。")

    print("-" * 50)
    print("所有依赖项都已成功构建和安装.")

if __name__ == "__main__":
    ensure_requests_is_installed()
    import requests
    main()
