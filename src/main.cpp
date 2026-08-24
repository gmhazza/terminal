#include "../include/shell.h"
#include "../include/directories.h"

int main() {
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;
	std::vector<std::string> all_commands = {"echo", "exit", "type", "clear", "cwd", "cd", "ls", "mkdir"};
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
			} else if (words.at(0) == "type") {
				if (shell::check_command(words.at(1), all_commands)) {
					std::cout << words.at(1) << " is a shell builtin" << std::endl;
				} else {
					std::cout << words.at(1) << ": not found" << std::endl;
				}
			} 
		}
		else {
			std::cout << command.substr(0, command.find(" ")) << ": command not found" << std::endl;
		}
	}
}