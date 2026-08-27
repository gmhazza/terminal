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

namespace style {
    const std::string RESET     = "\033[0m";
    const std::string BOLD      = "\033[1m";
    const std::string DIM       = "\033[2m";
    const std::string ITALIC    = "\033[3m";
    const std::string UNDERLINE = "\033[4m";

    const std::string RED       = "\033[31m";
    const std::string GREEN     = "\033[32m";
    const std::string YELLOW    = "\033[33m";
    const std::string BLUE      = "\033[34m";
    const std::string MAGENTA   = "\033[35m";
    const std::string CYAN      = "\033[36m";

    const std::string BRIGHT_BLUE = "\033[94m";
    const std::string BRIGHT_CYAN = "\033[96m";

    inline std::string rgbtext(int, int, int);
    inline std::string rgbbg(int, int, int);
}

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
    std::string get(const std::string&);
    void set(const std::string&, const std::string&);
    void save();
};