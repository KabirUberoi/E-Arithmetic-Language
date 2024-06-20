#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include "evaluator.h"

#include "ulimitedint.cpp"
#include "ulimitedrational.cpp"
#include "entry.cpp"
#include "symtable.cpp"
#include "exprtreenode.cpp"
#include "evaluator.cpp"

int main() {
    std::string line; 
    std::regex tokenRegex("([a-zA-Z_][a-zA-Z0-9_]*|:=|\\(|\\)|\\+|\\-|\\*|\\/|\\d+)");
    Evaluator evaluator;

    std::cout << "Enter expressions to evaluate or type 'exit' to quit:" << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line == "exit") break;

        std::vector<std::string> tokens;
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), tokenRegex);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            tokens.push_back(i->str());
        }

        try {
            evaluator.parse(tokens);
            std::cout << evaluator.eval() << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}