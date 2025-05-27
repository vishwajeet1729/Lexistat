#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <set>
#include <vector>
#include <stack>

using namespace std;

struct Symbol {
    string name;
    string type;
    string value;
    int scopeLevel;
    int declaredLine;
    vector<int> references;
    set<string> usageTypes;
};

unordered_map<string, Symbol> symbolTable;
vector<string> errors;

set<string> keywords = {
    "int", "float", "char", "double", "void", "bool", "return",
    "if", "else", "for", "while", "do", "switch", "case",
    "break", "continue", "const", "static", "struct", "class"
};

set<string> operators = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", "<=", ">", ">=", "&&", "||",
    "&", "|", "^", "~", "<<", ">>", "!", "++", "--"
};

set<char> separators = { ';', ',', '(', ')', '{', '}', '[', ']' };

bool isKeyword(const string& s) {
    return keywords.find(s) != keywords.end();
}

bool isOperator(const string& s) {
    return operators.find(s) != operators.end();
}

bool isValidIdentifier(const string& s) {
    if (s.empty() || isdigit(s[0]) || (!isalpha(s[0]) && s[0] != '_'))
        return false;
    for (char c : s) {
        if (!isalnum(c) && c != '_')
            return false;
    }
    return true;
}

bool isInteger(const string& s) {
    return regex_match(s, regex("^[0-9]+$"));
}

bool isFloat(const string& s) {
    return regex_match(s, regex("^[0-9]*\\.[0-9]+$"));
}

bool isCharLiteral(const string& s) {
    return regex_match(s, regex("^'.'$"));
}

bool isStringLiteral(const string& s) {
    return regex_match(s, regex("^\".*\"$"));
}

void preprocess(string& line) {
    static bool inBlockComment = false;
    if (inBlockComment) {
        size_t end = line.find("*/");
        if (end != string::npos) {
            line = line.substr(end + 2);
            inBlockComment = false;
        } else {
            line.clear();
            return;
        }
    }

    size_t start = line.find("/*");
    while (start != string::npos) {
        size_t end = line.find("*/", start + 2);
        if (end != string::npos) {
            line.erase(start, end - start + 2);
            start = line.find("/*");
        } else {
            line.erase(start);
            inBlockComment = true;
            return;
        }
    }

    size_t comment = line.find("//");
    if (comment != string::npos) {
        line = line.substr(0, comment);
    }
}

int scopeLevel = 0;
string currentType = "";

void tokenize(const string& line, int lineNumber) {
    istringstream stream(line);
    string token;

    while (stream >> token) {
        if (token == "{") {
            scopeLevel++;
        } else if (token == "}") {
            scopeLevel = max(0, scopeLevel - 1);
        }

        if (isKeyword(token)) {
            cout << "[Keyword] " << token << endl;
            currentType = token;
        } else if (isOperator(token)) {
            cout << "[Operator] " << token << endl;
        } else if (token.size() == 1 && separators.count(token[0])) {
            cout << "[Separator] " << token << endl;
        } else if (isInteger(token) || isFloat(token) || isCharLiteral(token) || isStringLiteral(token)) {
            cout << "[Constant] " << token << endl;
        } else if (isValidIdentifier(token)) {
            cout << "[Identifier] " << token << endl;

            if (!currentType.empty()) {
                if (symbolTable.find(token) == symbolTable.end()) {
                    symbolTable[token] = {token, currentType, "", scopeLevel, lineNumber, {}, {"declaration"}};
                }
                currentType = "";
            } else {
                if (symbolTable.find(token) == symbolTable.end()) {
                    symbolTable[token] = {token, "unknown", "", scopeLevel, -1, {lineNumber}, {"usage"}};
                } else {
                    symbolTable[token].references.push_back(lineNumber);
                    symbolTable[token].usageTypes.insert("usage");
                }
            }
        } else {
            cout << "[Error] Invalid token: " << token << endl;
            errors.push_back("Line " + to_string(lineNumber) + ": Invalid token '" + token + "'");
        }
    }
}

int main() {
    ifstream file("input.cpp");
    if (!file) {
        cerr << "Error opening input.cpp" << endl;
        return 1;
    }

    string line;
    int lineNumber = 1;
    while (getline(file, line)) {
        preprocess(line);
        tokenize(line, lineNumber);
        lineNumber++;
    }

    file.close();

    cout << "\nSymbol Table\n------------\n";
    for (const auto& entry : symbolTable) {
        const Symbol& s = entry.second;
        cout << "Name: " << s.name
             << ", Type: " << s.type
             << ", Scope: " << s.scopeLevel
             << ", Declared: " << (s.declaredLine >= 0 ? to_string(s.declaredLine) : "Undeclared")
             << ", Usage: ";
        for (const auto& u : s.usageTypes) cout << u << " ";
        if (!s.references.empty()) {
            cout << ", Referenced at: ";
            for (int r : s.references) cout << r << " ";
        }
        cout << endl;
    }

    if (!errors.empty()) {
        cout << "\nErrors\n------\n";
        for (const auto& e : errors) cout << e << endl;
    } else {
        cout << "\nNo lexical errors found.\n";
    }

    return 0;
}
