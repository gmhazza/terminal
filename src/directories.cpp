#include "../include/directories.h"


void directories::get_folder(std::string& current_folder) {
    current_folder = std::filesystem::current_path().filename().string();
}
void directories::get_cwd(std::string& cwd) {
    cwd = std::filesystem::current_path().string();
}
void directories::update_cwd(const std::string& d) {
    std::error_code ec;
    std::filesystem::current_path(d, ec);
    if (ec) {
        std::cerr << d << ": no directory founded" << std::endl;
    }
}
void directories::list_directory(const std::string& d) {
    std::error_code ec;
    if (!std::filesystem::exists(d, ec) || !std::filesystem::is_directory(d, ec)) {
        std::cerr << "ls: cannot access '" << d << "': No such file or directory" << std::endl;
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
        std::cerr << "could complete the proccess: " << ec.message() << std::endl;
    }
}
void directories::make_file(const std::string& filename) {
    std::string cwd;
    directories::get_cwd(cwd);
    std::string path = cwd + "\\" + filename;
    std::ofstream file(path);
    if(file.is_open()) {
        std::cout << "File created Successfully on: " << path << std::endl;
        file.close();
    }
    else {
        std::cerr << "Unable to make a file on: " << path << std::endl;
    }
}
void directories::remove(const std::string& d, bool r) {
    std::error_code ec;
    if (!std::filesystem::exists(d, ec)) {
        std::cerr << "rm: No file or directory found" << std::endl;
    }
    if (r) {
        std::filesystem::remove_all(d, ec);
    } else {
        std::filesystem::remove(d, ec);
    }
    if (ec) {
        std::cerr << "rm: " << ec.message() << std::endl;
    }
}