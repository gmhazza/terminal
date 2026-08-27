#include "../include/shell.h"
#include "../include/directories.h"
#include "../include/env.h"

const std::string APP_NAME = "termi";
const std::string APP_VERSION = "0.0.2";

int main() {
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;
	std::vector<std::string> all_commands = {"echo", "exit", "type", "clear", "cwd", "cd", "ls", "mkdir", "mkfile", "rm"};
	while (true) {
		std::string folder = "";
		directories::get_folder(folder);
		std::string command;
		std::cout << folder << " $ ";
		std::getline(std::cin, command);
		std::vector<std::string> words;
		shell::extract_words(command, words);
		if(words.empty()) continue;
		if (shell::check_command(words.at(0), all_commands)) {
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
				if (shell::check_command(words.at(1), all_commands)) {
					std::cout << words.at(1) << " is a shell builtin" << std::endl;
				} else {
					std::cout << words.at(1) << ": not found" << std::endl;
				}
			}
		}
		else {
			if (words.at(0) == APP_NAME) {
				if (words.size() > 1) {
					if ((words.at(1) == "--version") || (words.at(1) == "--version")) {
						std::cout << APP_NAME << " version: " << APP_VERSION << std::endl;
					} else {
						std::cout << "termi: no option found" << std::endl;
					}
				} else {
					std::cout << "termi Usage: " << std::endl;
					std::cout << "termi [Option]" << std::endl;
					std::cout << "Options: " << std::endl;
					std::cout << "--version" << std::endl;
				}
			} else {
				env::execute_command(command);
			}
			
			//std::cout << command.substr(0, command.find(" ")) << ": command not found" << std::endl;
		}
	}
}