#include "./headers/shell.h"

int main() {
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;
	std::vector<std::string> all_commands = {"echo", "exit", "type", "clear"};
	while (true) {
		std::string cwd = "";
		std::string command;
		std::cout << cwd << " $ ";
		std::getline(std::cin, command);
		std::vector<std::string> words;
		shell::extract_words(command, words);
		if(words.empty()) continue;
		if (shell::check_command(words.at(0), all_commands)) {
			if (words.at(0) == "exit") {
				break;
			} else if(words.at(0) == "clear") {
				shell::clear_screen();
			} else if (command.substr(0, 5) == "echo ") {
				std::cout << command.substr(5) << std::endl;
			} else if (command.substr(0, 5) == "type ") {
				if (shell::check_command(command.substr(5), all_commands)) {
					std::cout << command.substr(5) << " is a shell builtin" << std::endl;
				} else {
					std::cout << command.substr(5) << ": not found" << std::endl;
				}
			} 
		}
		else {
			std::cout << command.substr(0, command.find(" ")) << ": command not found" << std::endl;
		}
	}
}