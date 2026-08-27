#include "../include/appearance.h"



#ifdef _WIN32
void appearance::enableVirtualTerminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
void appearance::enableVirtualTerminal() {}
#endif


configfile::configfile(const std::filesystem::path& p) : filePath(p) { load(); }
void configfile::load() {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream lineStream(line);
        std::string key, value;
        if (std::getline(lineStream, key, '=') && std::getline(lineStream, value)) {
            data[key] = value;
        }
    }
}
std::string configfile::get(const std::string& key, const std::string& defaultValue = "") {
    if (data.find(key) != data.end()) {
        return data[key];
    }
    return defaultValue;
}
void configfile::set(const std::string& key, const std::string& value) {
    data[key] = value;
}
void configfile::save() {
    std::ofstream file(filePath);
    for (const auto& [key, value] : data) {
        file << key << "=" << value << "\n";
    }
}
std::filesystem::path appearance::getExecutableDir() {
#if defined(_WIN32)
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return std::filesystem::path(buffer).parent_path();

#elif defined(__APPLE__)
    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0) {
        return std::filesystem::canonical(buffer).parent_path();
    }
    return std::filesystem::current_path();

#elif defined(__linux__)
    char buffer[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (count != -1) {
        buffer[count] = '\0';
        return std::filesystem::path(buffer).parent_path();
    }
    return std::filesystem::current_path();
#endif
}
std::filesystem::path appearance::getInstalledFilePath(const std::string& relativePath) {
    std::filesystem::path exeDir = getExecutableDir();
    return std::filesystem::weakly_canonical(exeDir / relativePath);
}