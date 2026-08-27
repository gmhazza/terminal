#include "../include/shell.h"
#include "../include/directories.h"
#include "../include/env.h"
#include "../include/appearance.h"

const std::string APP_NAME = "termi";
const std::string APP_VERSION = "0.0.3";
const std::string SETTING_PATH = "../configs/settings.ini";

const std::vector<std::string> THEMES = {"dark", "dark-solar", "dracula"};
const std::vector<std::string> COMMANDS = {"echo", "exit", "type", "clear", "cwd", "cd", "ls", "mkdir", "mkfile", "rm"};


int main() {
	std::error_code ec;
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;
	appearance::enableVirtualTerminal();
	const std::filesystem::path p = appearance::getInstalledFilePath(SETTING_PATH);
	if (!std::filesystem::exists(p, ec)) {
		std::cerr << "No Config file founded" << std::endl;
	}
	configfile setting(p);
	std::string theme = setting.get("theme");
	while (true) {
		std::string folder = "";
		directories::get_folder(folder);
		std::string command;
		std::cout << folder << " $ ";
		std::getline(std::cin, command);
		std::vector<std::string> words;
		shell::extract_words(command, words);
		if(words.empty()) continue;
		if (shell::check_command(words.at(0), COMMANDS)) {
			if (words.at(0) == "exit") {
				break;
			} else if(words.at(0) == "clear") {
				shell::clear_screen();
			} else if(words.at(0) == "cwd") {
				std::string cwd = "";
				directories::get_cwd(cwd);
				std::cout << "Current Working Directory: " << cwd << std::endl;
			} else if (words.at(0) == "ls") {
				directories::list_directory((words.size() > 1) ? words.at(1) : "./");
			} else if (words.at(0) == "mkdir") {
				if (words.size() > 1) directories::make_directory(words.at(1));
				else continue;
			} else if (words.at(0) == "cd") {
				directories::update_cwd((words.size() > 1) ? words.at(1) : "./");
			} else if (words.at(0) == "echo") {
				std::cout << command.substr(5) << std::endl;
			} else if (words.at(0) == "mkfile") {
				if (words.size() > 1) directories::make_file(words.at(1));
				else std::cerr << "mkfile: parameters issue\n";
			} else if (words.at(0) == "rm") {
				if ( words.size() > 1) {
					if (words.at(1) == "-r") {
						directories::remove((words.size() > 2) ? words.at(2) : "  ", true);
					} else {
						directories::remove(words.at(1), false);
					}
				}
			} else if (words.at(0) == "type") {
				if (shell::check_command(words.at(1), COMMANDS)) {
					std::cout << words.at(1) << " is a shell builtin" << std::endl;
				} else {
					std::cout << words.at(1) << ": not found" << std::endl;
				}
			}
		}
		else {
			if (words.at(0) == APP_NAME) {
				if (words.size() > 1) {
					if ((words.at(1) == "--version") || (words.at(1) == "-v")) {
						std::cout << APP_NAME << " version: " << APP_VERSION << std::endl;
					} else if ((words.at(1) == "--theme") || (words.at(1) == "-t")) {
						bool found = false;
						for (auto& t : THEMES) {
							if (words.at(2) == t) {
								setting.set("theme", words.at(2));
								setting.save();
								found = true;
								exit;
							}
						}
						if (!found) std::cerr << words.at(0) << " " << words.at(1) << ": " << words.at(2) << " not found" << std::endl;
					} else {
						std::cout << "termi: no option found" << std::endl;
					}
				} else {
					std::cout << "termi Usage: " << std::endl;
					std::cout << "  " << "termi [Option]" << std::endl;
					std::cout << "    " << "Options: " << std::endl;
					std::cout << "      " << "--version" << std::endl;
					std::cout << "      " << "--theme <type>" << std::endl;
					std::cout << "          " << "type: ";
					for (auto& t : THEMES) std::cout << t << ", ";
					std::cout << std::endl;
 				}
			} else {
				env::execute_command(command);
			}
			
			//std::cout << command.substr(0, command.find(" ")) << ": command not found" << std::endl;
		}
	}
}