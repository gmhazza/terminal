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
void directories::list_directory(const std::string& d) {
    std::error_code ec;
    if (!std::filesystem::exists(d, ec) || !std::filesystem::is_directory(d, ec)) {
        std::cout << "ls: cannot access '" << d << "': No such file or directory" << std::endl;
        return;
    }
    for (auto& entry : std::filesystem::directory_iterator(d, ec)) {
        if (entry.is_directory()) {
            std::cout << "dir     "<< entry.path().filename().string() << "/" << std::endl;
        } else {
            std::cout << "file    " << entry.path().filename().string() << std::endl;
        }
    }
}
void directories::make_directory(const std::string& d) {
    std::error_code ec;
    const std::string path = "./" + d;
    std::filesystem::create_directory(path, ec);
    if(ec) {
        std::cout << "could complete the proccess: " << ec.message() << std::endl;
    }
}