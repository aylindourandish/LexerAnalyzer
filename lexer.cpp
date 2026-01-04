#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <cstdlib> 


std::unordered_set<std::string> validKeywords = { "if", "else", "for", "while", "return", "int", "float", "double", "char", "void", "bool", "main", "include", "cin", "cout" };

class LexerAnalyzer {
public:
    LexerAnalyzer(const std::string& input) : input_(input) {}

    void analyze() {
     
        int identifierCount = 0;
        int separatorCount = 0;
        int numberCount = 0;
        int stringCount = 0;
        int keywordCount = 0;
        int constantCount = 0;
        int logicalOperatorCount = 0;
        int arithmeticOperatorCount = 0;
        int commentCount = 0;
        int spaceCount = 0;

        std::vector<std::string> errors;

    
        std::regex identifierRegex("\\b[a-zA-Z_][a-zA-Z0-9_]*\\b");
        std::regex separatorRegex("[,;:.]");
        std::regex numberRegex("\\b\\d+\\b");
        std::regex stringRegex("\"[^\"]*\"");
        std::regex keywordRegex("\\b(if|else|while|for|switch|case|break|continue|return|cin|cout)\\b");
        std::regex constantRegex("\\b(true|false|null)\\b");
        std::regex logicalOperatorRegex("\\b(and|or|not)\\b");
        std::regex arithmeticOperatorRegex("[+\\-*%]");
        std::regex commentRegex("//.*|/\\*(.|\\n)*?\\*/");
        std::regex spaceRegex("\\s");

    
        input_ = std::regex_replace(input_, commentRegex, "");

      
        auto countMatches = [&](std::regex& reg, int& count) {
            auto iter = std::sregex_iterator(input_.begin(), input_.end(), reg);
            auto end = std::sregex_iterator();
            while (iter != end) {
                count++;
                ++iter;
            }
        };


        countMatches(separatorRegex, separatorCount);
        countMatches(numberRegex, numberCount);
        countMatches(stringRegex, stringCount);
        countMatches(keywordRegex, keywordCount);
        countMatches(constantRegex, constantCount);
        countMatches(logicalOperatorRegex, logicalOperatorCount);
        countMatches(arithmeticOperatorRegex, arithmeticOperatorCount);
        countMatches(spaceRegex, spaceCount);

        
        auto iter = std::sregex_iterator(input_.begin(), input_.end(), identifierRegex);
        auto end = std::sregex_iterator();
        while (iter != end) {
            std::string match = iter->str();
            if (validKeywords.find(match) == validKeywords.end()) {
                identifierCount++;
            }
            ++iter;
        }

     
        std::regex allRegex(
                "\\b[a-zA-Z_][a-zA-Z0-9_]*\\b|[,;:.]|\\b\\d+\\b|\"[^\"]*\"|\\b(if|else|while|for|switch|case|break|continue|return|cin|cout)\\b|\\b(true|false|null)\\b|\\b(and|or|not)\\b|[+\\-*/%]|<<|>>\\s");

        iter = std::sregex_iterator(input_.begin(), input_.end(), allRegex);
        size_t pos = 0;
        while (iter != end) {
            if (pos < iter->position()) {
                std::string errorSegment = input_.substr(pos, iter->position() - pos);
                if (!std::all_of(errorSegment.begin(), errorSegment.end(), isspace)) {
                    errors.push_back(errorSegment);
                }
            }
            pos = iter->position() + iter->str().length();
            ++iter;
        }

        if (pos < input_.length()) {
            std::string errorSegment = input_.substr(pos);
            if (!std::all_of(errorSegment.begin(), errorSegment.end(), isspace)) {
                errors.push_back(errorSegment);
            }
        }

        
        int errorCount = errors.size();

    
        std::cout << "Number of identifiers: " << identifierCount << std::endl;
        std::cout << "Number of separators: " << separatorCount << std::endl;
        std::cout << "Number of numbers: " << numberCount << std::endl;
        std::cout << "Number of strings: " << stringCount << std::endl;
        std::cout << "Number of keywords: " << keywordCount << std::endl;
        std::cout << "Number of constants: " << constantCount << std::endl;
        std::cout << "Number of logical operators: " << logicalOperatorCount << std::endl;
        std::cout << "Number of arithmetic operators: " << arithmeticOperatorCount << std::endl;
        std::cout << "Number of comments: " << commentCount << std::endl;
        std::cout << "Number of spaces: " << spaceCount << std::endl;
        std::cout << "Number of errors: " << errorCount << std::endl;

        if (errorCount > 0) {
            std::cout << "Errors:" << std::endl;
            for (const auto& error : errors) {
                std::cout << error << std::endl;
            }
        }
    }

private:
    std::string input_;
};

int main() {
    std::string filePath;

    std::cout << "Enter path to program.txt file: ";
    std::getline(std::cin, filePath);

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filePath << std::endl;
        return 1;
    }

    std::string input(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    LexerAnalyzer analyzer(input);
    analyzer.analyze();

    return 0;
}
