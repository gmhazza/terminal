#include "../include/directories.h"

void directories::get_cwd(std::string& cwd) {
    cwd = std::filesystem::current_path().string();
}