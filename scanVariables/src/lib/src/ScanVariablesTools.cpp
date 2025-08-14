#include <ScanVariablesTools.h>
#include <iostream>
#include <filesystem>
#include <regex>
#include <fstream>

namespace fs = std::filesystem;

std::string readFileContents(const std::string& filePath)
{
    std::string fileContents;
    std::ifstream fileIFStream;
    fileIFStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        fileIFStream.open(filePath);
        std::stringstream fileStringStream;
        fileStringStream << fileIFStream.rdbuf();
        fileContents = fileStringStream.str();
        fileIFStream.close();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::FILE_NOT_SUCCESSFULLY_READ" << e.what() << std::endl;
    }

    return fileContents;
}

json getConfig(const std::string& filePath)
{
    std::string configContents = readFileContents(filePath);
    json parsed_data;
    try
    {
        parsed_data = json::parse(configContents);
    }
    catch (const std::exception& e)
    {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
    return parsed_data;
}

std::vector<std::string> getFileInDirectory(const std::string& folderPath, const std::string& extension)
{
    std::vector<std::string> fileList;
    try
    {
        for (const auto& entry : fs::directory_iterator(folderPath))
        {
            if (entry.is_regular_file())
            {
                if (const fs::path& filePath = entry.path();
                    filePath.extension() == extension)
                {
                    fileList.push_back(filePath.string());
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return fileList;
}

std::vector<std::pair<Uniform, std::unordered_set<Uniform>>> getUniform(const std::string& filePath)
{
    std::string fileCode = readFileContents(filePath);
    std::vector<std::pair<Uniform, std::unordered_set<Uniform>>> result;
    std::unordered_set<Macro> macros = getMacros(fileCode);

    std::regex regexUniform(R"(uniform\s+(.+?)\s+([a-zA-Z_]\w*)\s*(?:\[([a-zA-Z_\d]\w*)\])?\s*;)");
    auto words_begin = std::sregex_iterator(fileCode.begin(), fileCode.end(), regexUniform);
    auto words_end = std::sregex_iterator();
    std::unordered_set<Uniform> uniformList;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        const std::smatch& match = *i;
        Uniform uniform;
        uniform.type = match[1].str();
        uniform.name = match[2].str();
        if (!match[3].str().empty())
        {
            std::string varValue;
            for (const auto& [name, value] : macros)
            {
                if (name == match[3].str())
                {
                    varValue = value;
                    break;
                }
            }
            if (!varValue.empty())
            {
                uniform.arrSize = varValue;
            }
        }
        uniformList.insert(uniform);
    }

    std::regex regexStruct(R"(struct\s*(\w+)\s*\{([\s\S]*?)\};)");
    auto struct_begin = std::sregex_iterator(fileCode.begin(), fileCode.end(), regexStruct);
    auto struct_end = std::sregex_iterator();
    std::vector<std::pair<std::string, std::unordered_set<Uniform>>> structList;
    for (std::sregex_iterator i = struct_begin; i != struct_end; ++i)
    {
        const std::smatch& structMatch = *i;
        std::pair<std::string, std::unordered_set<Uniform>> structPair;
        structPair.first = structMatch[1].str();
        std::string members = structMatch[2].str();

        std::regex memberRegex(R"(([a-zA-Z_]\w*)\s+([a-zA-Z_]\w*);)");
        auto members_begin = std::sregex_iterator(members.begin(), members.end(), memberRegex);
        auto members_end = std::sregex_iterator();
        std::unordered_set<Uniform> memberList;
        for (std::sregex_iterator j = members_begin; j != members_end; ++j)
        {
            const std::smatch& memberMatch = *j;
            Uniform uniform;
            uniform.type = memberMatch[1].str();
            uniform.name = memberMatch[2].str();
            memberList.insert(uniform);
        }
        structPair.second = memberList;
        structList.push_back(structPair);
    }

    for (const auto& [type, name, arrSize] : uniformList)
    {
        std::pair<Uniform, std::unordered_set<Uniform>> tempPair;
        tempPair.first = Uniform(type, name, arrSize);
        for (auto& [first, second] : structList)
        {
            if (first == type)
            {
                tempPair.second = second;
                break;
            }
        }
        result.push_back(tempPair);
    }

    return result;
}

std::unordered_set<Macro> getMacros(const std::string& fileCode)
{
    std::unordered_set<Macro> result;
    const std::regex macroRegex(R"(#define\s+([a-zA-Z_]\w*)\s+([0-9]+)\b)");

    const auto words_begin = std::sregex_iterator(fileCode.begin(), fileCode.end(), macroRegex);
    const auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        const std::smatch& match = *i;
        Macro macro;
        macro.name = match[1].str();
        macro.value = match[2].str();
        result.insert(macro);
    }

    return result;
}

bool writeUniformsToHeader(const std::string& filename,
                           const std::vector<std::pair<Uniform, std::unordered_set<Uniform>>>& uniforms,
                           const std::string& configPath)
{
    std::ofstream outFile(filename, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file '" << filename << "' for writing." << std::endl;
        return false;
    }
    json config = getConfig(configPath);
    std::string headerGuard = fs::path(filename).filename().string();
    for (char& c : headerGuard)
    {
        if (!std::isalnum(c))
        {
            c = '_';
        }
        c = static_cast<char>(std::toupper(c));
    }
    std::unordered_set<Uniform> arrUniforms;
    outFile << "#ifndef " << headerGuard << "\n";
    outFile << "#define " << headerGuard << "\n";
    outFile << "#include <packGlm.h>\n#include <string>\n#include <glm/glm.hpp>\n\n";
    outFile << "inline struct Uniform {\n";
    for (const auto& [first, second] : uniforms)
    {
        if (second.empty())
        {
            if (first.type.find("vec") != std::string::npos || first.type.find("mat") != std::string::npos)
            {
                if (first.arrSize.empty())
                {
                    outFile << "\t" << "packGlm<glm::" << first.type << "> " << first.name << "{\"" << first.name <<
                    "\"};\n";
                } else
                {
                    outFile << "\t" << "packGlm<glm::" << first.type << "> " << first.name << "[" << first.arrSize <<
                    "];\n";
                }
            }
            else if (!config[first.type].empty())
            {
                if (first.arrSize.empty())
                {
                    outFile << "\t" << "packGlm<" << config[first.type].get<std::string>() << "> " << first.name << "{\"" <<
                    first.name << "\"};\n";
                } else
                {
                    outFile << "\t" << "packGlm<" << config[first.type].get<std::string>() << "> " << first.name << "[" <<
                    first.arrSize << "];\n";
                }
            }
            else
            {
                if (first.arrSize.empty())
                {
                    outFile << "\t" << "packGlm<" << first.type << "> " << first.name << "{\"" << first.name << "\"};\n";
                } else
                {
                    outFile << "\t" << "packGlm<" << first.type << "> " << first.name << "[" << first.arrSize << "];\n";
                }
            }
        }
        else
        {
            outFile << "\t" << "struct " << first.type << " : templateStruct {\n";
            outFile << "\t\t" << "std::string path{\"" << first.name << "\"};\n";
            for (const auto& [type, name, arrSize] : second)
            {
                if (type.find("vec") != std::string::npos || type.find("mat") != std::string::npos)
                {
                    outFile << "\t\t" << "packGlm<glm::" << type << "> " << name << "{this->path + \"." << name <<
                        "\"};\n";
                }
                else if (!config[type].empty())
                {
                    outFile << "\t\t" << "packGlm<" << config[type].get<std::string>() << "> " << name <<
                        "{this->path + \"." << name << "\"};\n";
                }
                else
                {
                    outFile << "\t\t" << "packGlm<" << type << "> " << name << "{this->path + \"." << name << "\"};\n";
                }
            }
            if (first.arrSize.empty())
            {
                outFile << "\t" << "} " << first.name << "{};\n";
            } else
            {
                arrUniforms.insert(first);
                outFile << "\t\t" << "explicit " << first.type << "(const int& index) : path{\"" + first.name + "[\" + std::to_string(index) + \"]\"}{}\n";
                outFile << "\t\t" << first.type << "() = default;\n";
                outFile << "\t" << "} " << first.name << "[" + first.arrSize + "];\n";
            }
        }
    }
    if (!arrUniforms.empty())
    {
        outFile << "\tUniform()\n\t{\n";
        for (const auto& [type, name, arrSize] : arrUniforms)
        {
            outFile << "\t\t" << "for(int i = 0; i < " << arrSize << "; i++)\n\t\t{\n\t\t\t" << name << "[i] = " << type << "(i);\n" << "\t\t}\n";
        }
        outFile << "\t}\n";
    }
    outFile << "} uniform;\n\n#endif";
    outFile.close();
    return true;
}
