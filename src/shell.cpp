#include "../include/shell.h"

bool shell::check_command(const std::string& command, const std::vector<std::string>& all_commands) {
	for (int i = 0; i < (all_commands.size()); i++) {
		if (command == all_commands.at(i)) {
			return true;
		}
	}
	return false;
}

void shell::extract_words(const std::string& command, std::vector<std::string>& words) {
    for (auto word : std::views::split(command, ' ')) {
        if (word.empty()) continue; 
        words.emplace_back(word.begin(), word.end());
    }
}

void shell::clear_screen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}