#include "../headers/shell.h"

bool shell::check_command(const std::string command, const std::vector<std::string> all_commands) {
	for (int i = 0; i < (all_commands.size()); i++) {
		if (command == all_commands.at(i)) {
			return true;
		}
	}
	return false;
}