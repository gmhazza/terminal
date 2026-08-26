#include "../include/env.h"

std::string env::getEnv(const std::string& name)
{
    const char* value = std::getenv(name.c_str());

    if (value == nullptr)
        return "";

    return value;
}

std::string env::find_executable(const std::string& command)
{
    std::string path = env::getEnv("PATH");

#ifdef _WIN32
    const char separator = ';';
#else
    const char separator = ':';
#endif

    std::stringstream stream(path);
    std::string directory;

    while (std::getline(stream, directory, separator))
    {
#ifdef _WIN32
        std::string executable = directory + "\\" + command + ".exe";
#else
        std::string executable = directory + "/" + command;
#endif

#ifdef _WIN32
        DWORD attributes = GetFileAttributesA(executable.c_str());

        if (attributes != INVALID_FILE_ATTRIBUTES &&
            !(attributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            return executable;
        }
#else
        if (access(executable.c_str(), X_OK) == 0)
        {
            return executable;
        }
#endif
    }

    return "";
}

int env::execute_command(std::string& input)
{
    std::string exe = env::find_executable(input.substr(0 , input.find(" ")));

    if (exe.empty())
    {
        std::cerr << input.substr(0 , input.find(" ")) << ": command not found\n";
        return 127;
    }

#ifdef _WIN32
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};

    si.cb = sizeof(si);

    std::vector<char> commandLine(input.begin(), input.end());
    commandLine.push_back('\0');

    BOOL success = CreateProcessA(
        nullptr,
        commandLine.data(),
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &si,
        &pi
    );

    if (!success)
    {
        std::cerr << "Failed to execute " << input.substr(0 , input.find(" ")) << "\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return static_cast<int>(exitCode);

#else

    pid_t pid = fork();

    if (pid == -1)
    {
        std::cerr << "Failed to fork\n";
        return 1;
    }

    if (pid == 0)
    {
        execl(exe.c_str(), input.c_str(), nullptr);

        // Only reached if execl() fails
        std::cerr << "Failed to execute " << input.substr(0 , input.find(" ")) << "\n";
        std::exit(1);
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        return WEXITSTATUS(status);

    return 1;

#endif
}