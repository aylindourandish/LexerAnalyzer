#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <regex>
#include <algorithm>
#include <cstdlib>

using namespace std;


unordered_set<string> keywords = {
    "if", "else", "for", "while", "return",
    "int", "float", "double", "char",
    "void", "bool", "main", "cin", "cout"
};

class Lexer {
public:
    Lexer(const string& text) {
        input = text;
    }

    void analyze() {
        int identifiers = 0;
        int numbers = 0;
        int strings = 0;
        int keywordsCount = 0;
        int separators = 0;
        int arithmeticOps = 0;
        int logicalOps = 0;
        int spaces = 0;

        vector<string> errors;

        regex idRegex("\\b[a-zA-Z_][a-zA-Z0-9_]*\\b");
        regex numberRegex("\\b\\d+\\b");
        regex stringRegex("\"[^\"]*\"");
        regex keywordRegex("\\b(if|else|for|while|return|cin|cout)\\b");
        regex separatorRegex("[,;:.]");
        regex arithmeticRegex("[+\\-*%]");
        regex logicalRegex("\\b(and|or|not)\\b");
        regex spaceRegex("\\s");
        regex commentRegex("//.*|/\\*(.|\\n)*?\\*/");


        input = regex_replace(input, commentRegex, "");

        countMatches(numberRegex, numbers);
        countMatches(stringRegex, strings);
        countMatches(keywordRegex, keywordsCount);
        countMatches(separatorRegex, separators);
        countMatches(arithmeticRegex, arithmeticOps);
        countMatches(logicalRegex, logicalOps);
        countMatches(spaceRegex, spaces);

        auto it = sregex_iterator(input.begin(), input.end(), idRegex);
        auto end = sregex_iterator();
        while (it != end) {
            if (keywords.find(it->str()) == keywords.end()) {
                identifiers++;
            }
            ++it;
        }

        cout << "Identifiers: " << identifiers << endl;
        cout << "Keywords: " << keywordsCount << endl;
        cout << "Numbers: " << numbers << endl;
        cout << "Strings: " << strings << endl;
        cout << "Separators: " << separators << endl;
        cout << "Arithmetic operators: " << arithmeticOps << endl;
        cout << "Logical operators: " << logicalOps << endl;
        cout << "Spaces: " << spaces << endl;
    }

private:
    string input;

    void countMatches(regex& reg, int& counter) {
        auto it = sregex_iterator(input.begin(), input.end(), reg);
        auto end = sregex_iterator();
        while (it != end) {
            counter++;
            ++it;
        }
    }
};

int main() {
    string path = getenv("USERPROFILE");
    path += "\\Desktop\\program.txt";

    ifstream file(path);
    if (!file) {
        cout << "Could not open input file." << endl;
        return 1;
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    Lexer lexer(content);
    lexer.analyze();

    return 0;
}
