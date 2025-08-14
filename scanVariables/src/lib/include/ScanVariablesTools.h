#ifndef SCAN_VARIABLES_TOOLS_H
#define SCAN_VARIABLES_TOOLS_H

#include <string>
#include <vector>
#include <unordered_set>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Uniform {
    std::string type;
    std::string name;
    std::string arrSize;

    bool operator==(const Uniform &other) const {
        return name == other.name && type == other.type && arrSize == other.arrSize;
    }
};

template<>
struct std::hash<Uniform> {
    size_t operator()(const Uniform &u) const noexcept {
        return std::hash<std::string>()(u.name);
    }
};

struct Macro
{
    std::string name;
    std::string value;
    bool operator==(const Macro &other) const
    {
        return name == other.name && value == other.value;
    }
};

template<>
struct std::hash<Macro>
{
    size_t operator()(const Macro &m) const noexcept
    {
        return std::hash<std::string>()(m.name) ^ std::hash<std::string>()(m.value) << 1;
    }
};

std::vector<std::string> getFileInDirectory(const std::string &folderPath, const std::string &extension);

std::vector<std::pair<Uniform, std::unordered_set<Uniform>>> getUniform(const std::string &filePath);

bool writeUniformsToHeader(
    const std::string &filename, const std::vector<std::pair<Uniform, std::unordered_set<Uniform>>> &uniforms, const std::string& configPath
);

std::string readFileContents(const std::string& filePath);

json getConfig(const std::string& filePath);

std::unordered_set<Macro> getMacros(const std::string& fileCode);

#endif //SCAN_VARIABLES_TOOLS_H
