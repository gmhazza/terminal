#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <unordered_map>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <climits>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#endif

namespace appearance {
    void enableVirtualTerminal();
    std::filesystem::path getExecutableDir();
    std::filesystem::path getInstalledFilePath(const std::string&);
}

class configfile {
    std::filesystem::path filePath;
    std::unordered_map<std::string, std::string> data;

    public:
    configfile(const std::filesystem::path&);
    void load();
    std::string get(const std::string&, const std::string&);
    void set(const std::string&, const std::string&);
    void save();
};