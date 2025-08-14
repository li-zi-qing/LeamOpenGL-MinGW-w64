#include <iostream>
#include <filesystem>
#include <regex>
#include <ScanVariablesTools.h>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

int main(const int argc, char* argv[])
{
    if (argc >= 5)
    {
        const std::string shaderResourcesFolderPath = argv[1];
        const std::string configPath = argv[2];
        const std::string outputPath = argv[3];
        const std::string outputName = argv[4];
        if (shaderResourcesFolderPath.empty() || configPath.empty() || outputPath.empty() || outputName.empty())
        {
            printf("存在无效路径...");
            return 0;
        }
        const std::vector<std::string> vertFilePathList = getFileInDirectory(shaderResourcesFolderPath, ".vert");
        const std::vector<std::string> fragFilePathList = getFileInDirectory(shaderResourcesFolderPath, ".frag");
        if (vertFilePathList.empty() || fragFilePathList.empty())
        {
            printf("无法获取有效的 .frag | .vert 格式文件列表, 路径%s...", shaderResourcesFolderPath.c_str());
            return -1;
        }

        std::vector<std::pair<Uniform, std::unordered_set<Uniform>>> uniformList;
        for (const auto& filePath : vertFilePathList)
        {
            if (std::vector<std::pair<Uniform, std::unordered_set<Uniform>>> tempUniform = getUniform(filePath);
                !tempUniform.empty())
            {
                uniformList.insert(uniformList.begin(), tempUniform.begin(), tempUniform.end());
            }
        }

        for (const auto& filePath : fragFilePathList)
        {
            if (std::vector<std::pair<Uniform, std::unordered_set<Uniform>>> tempUniform = getUniform(filePath);
                !tempUniform.empty())
            {
                uniformList.insert(uniformList.begin(), tempUniform.begin(), tempUniform.end());
            }
        }

        std::vector<std::pair<Uniform, std::unordered_set<Uniform>>> tempUniformList;
        if (uniformList.empty())
        {
            tempUniformList.push_back(uniformList[0]);
        }
        for (const auto& uniform : uniformList)
        {
            bool isOn = false;
            for (const auto& [type, name, arrSize] : tempUniformList | std::views::keys)
            {
                if (name == uniform.first.name)
                {
                    isOn = true;
                }
            }
            if (!isOn)
            {
                tempUniformList.push_back(uniform);
            }
        }

        const fs::path fsOutputPath = outputPath;
        const fs::path fsOutputName = outputName;
        fs::create_directories(fsOutputPath);
        writeUniformsToHeader((fsOutputPath / fsOutputName).string() + ".h", tempUniformList, configPath);
    }
    else
    {
        printf("参数数量不足...");
        return -1;
    }
    return 0;
}
