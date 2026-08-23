#include <iostream>

#include "./headers/shell.h"

int main() {
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;
	std::vector<std::string> all_commands = {"echo", "exit", "type"};
	while (true) {
		std::string command;
		std::cout << "$ ";
		std::getline(std::cin, command);
		if (shell::check_command(command.substr(0, command.find(" ")), all_commands)) {
			if (command == "exit") {
				break;
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


