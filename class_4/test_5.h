#include <iostream>
#include <string>
#include <regex>

int test_5() {
    std::string text = "123-456-7890 and 987-654-3210";
    std::regex pattern(R"((\d+))");

    std::smatch matches;
    while (std::regex_search(text, matches, pattern)) {
        std::cout << "Found: " << matches[0] << std::endl;
        text = matches.suffix().str();
    }

    text = "123-456-7890 and 987-654-3210";
    std::string replacement = "*";
    std::string result = std::regex_replace(text, pattern, replacement);

    std::cout << "Original: " << text << std::endl;
    std::cout << "Modified: " << result << std::endl;

    return 0;
}