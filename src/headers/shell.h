#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <ranges>

namespace shell {
    bool check_command(const std::string&, const std::vector<std::string>&);
    void extract_words(const std::string&, std::vector<std::string>&);
    void clear_screen();
}