#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/wait.h>
#endif

namespace env {
    std::string getEnv(const std::string&);
    std::string find_executable(const std::string&);
    int execute_command(std::string&);
}