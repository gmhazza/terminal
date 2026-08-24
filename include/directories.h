#pragma once

#include <iostream>
#include <filesystem>
#include <system_error>
#include <string>

namespace directories {
    void get_folder(std::string&);
    void get_cwd(std::string&);
    void update_cwd(const std::string&);
    void list_directory(const std::string&);
    void make_directory(const std::string&);
}