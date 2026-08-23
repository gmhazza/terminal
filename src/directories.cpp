#include "../include/directories.h"

void directories::get_cwd(std::string& cwd) {
    cwd = std::filesystem::current_path().string();
}
void directories::update_cwd(const std::string& d) {
    std::error_code ec;
    std::filesystem::current_path(d, ec);
    if (ec) {
        std::cout << d << ": no directory founded" << std::endl;
    }
}