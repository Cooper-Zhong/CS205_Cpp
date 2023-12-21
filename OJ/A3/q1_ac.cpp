#include <iostream>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <vector>

#define def "#define"
#define undef "#undef"
#define dup "ERROR DUP"
#define nf "ERROR NFOUND"


using namespace std;


struct {
    string name;
    int paraCnt;
    vector <string> parameters;
    vector <string> body_tokens;
} typedef functionMacro;

unordered_map <string, string> variableMap;
vector <functionMacro> functionMap;

void handle_code(const string &code) {
    istringstream iss(code);
    string s;
    vector <string> tokens;
    while (iss >> s) {
        tokens.push_back(s);
    }
    if (tokens.empty()) return;

    // replace function and variable
    bool isFunc = false;
    int paraCnt = 0;
    int bracketCnt = 0;
    vector <string> parameters;
    string para;
    int funcStart = 0;
    string func_name;

    for (int i = 0; i < tokens.size(); i++) {
        s = tokens[i];
//        cout << "debug: " << s << " " << bracketCnt << endl;
        if (isFunc) {
            if (s == "(") {
                bracketCnt++;
                para += s;
            } else if (s == ")") {
                bracketCnt--;
//                cout << "debug: " << bracketCnt << endl;
                if (bracketCnt != 0) {
                    para += s;
                } else { // end of function
                    // here !!!!! d( ) -> paraCnt = 1
                    if (!para.empty()) {
                        paraCnt++;
                        parameters.push_back(para);
                    }

//                    cout << "debug: " << func_name << " " << paraCnt << endl;

                    // find function
                    bool found = false;
                    for (functionMacro f: functionMap) {
                        if (f.name == func_name && f.paraCnt == paraCnt) {
                            // found
                            found = true;
                            vector <string> newbody_tokens = f.body_tokens;

                            for (int j = 0; j < f.body_tokens.size(); ++j) {
                                for (int k = 0; k < f.paraCnt; ++k) {
                                    string defpara = f.parameters[k];
                                    if (f.body_tokens[j] == defpara) {
                                        newbody_tokens[j] = parameters[k]; // replace
                                    }
                                }
                            }
                            string newbody = "";
                            for (string s: newbody_tokens) {
                                newbody += (s + " ");
                            }
                            cout << newbody << endl;
                            break;
                        }
                    }
                    if (!found) { // not found,print out original
                        for (int j = funcStart; j <= i; ++j) {
                            cout << tokens[j] << " ";
                        }
                    }
                    isFunc = false;

                }
            } else if (s == "," && bracketCnt == 1) { // mul( ( a , b ) , c ) only 2 parameters
                paraCnt++;
                parameters.push_back(para);
                para = "";
            } else {
                para += s;
            }
        } else if (s.find('(') != string::npos && s != "(") { // function
            isFunc = true;
            funcStart = i;
            func_name = s;
            paraCnt = 0;
            bracketCnt = 1;
            parameters = vector<string>();
            para = "";
//            cout << "debug: " << s << endl;

        } else {
            // variable
            if (variableMap.find(s) != variableMap.end()) {
                cout << variableMap[s] << " ";
            } else {
                cout << s << " ";
            }
        }
    }
}

void handle_def(const string &line) {
    string s;
    istringstream iss(line);
    vector <string> tokens;
    while (iss >> s) tokens.push_back(s);
    if (tokens.size() < 2) return; // no parameters

    string name = tokens[1];
    bool isFunc = false;
    if (name.find('(') != string::npos && name != "(") {
        isFunc = true;
    }

    if (isFunc) {
        int paraCnt = 0;
        int bracketCnt = 1;
        vector <string> parameters;
        string para;
        int funcStart = 0;
        string func_name;
        int i = 2;
        for (; i < tokens.size(); ++i) {
            string tmp = tokens[i];
            if (tmp == ",") {
                paraCnt++;
                parameters.push_back(para);
                para = "";
            } else if (tmp == ")") {
                bracketCnt--;
            } else if (tmp == "(") {
                bracketCnt++;
            } else {
                para += tmp;
            }
            if (bracketCnt == 0) { //parameters end
                paraCnt++;
                parameters.push_back(para);
                i++;
                break;
            }
        }
        for (functionMacro f: functionMap) {
            if (f.name == name && f.paraCnt == paraCnt) {
                cout << dup << endl;
                exit(0);
            }
        }
        auto *func = new functionMacro;
        func->name = name;
        func->paraCnt = paraCnt;
        // find body
        vector <string> body_tokens;
        while (i < tokens.size()) {
            body_tokens.push_back(tokens[i]);
            i++;
        }

        func->body_tokens = body_tokens;
        func->parameters = parameters;
        functionMap.push_back(*func);
//        cout << "debug" << " define: " << func->name << " " << func->paraCnt << " " << func->body << endl;


    } else {
        if (variableMap.find(name) != variableMap.end()) {
            cout << dup << endl;
            exit(0);
        } else variableMap[name] = tokens[2];
    }

}

void handle_undef(const string &line) {
    string s;
    istringstream iss(line);
    vector <string> tokens;
    while (iss >> s) {
        tokens.push_back(s);
    }
    if (tokens.size() < 2) { // no parameters
        return;
    }

    string name = tokens[1];
    bool isFunc = false;
    if (name.find('(') != string::npos && name != "(") {
        isFunc = true;
    }

    if (isFunc) {
        int paraCnt = 0;
        int bracketCnt = 1;
        vector <string> parameters;
        string para;
        int funcStart = 0;
        int i = 2;
        for (; i < tokens.size(); ++i) {
            string tmp = tokens[i];
            if (tmp == ",") {
                paraCnt++;
                parameters.push_back(para);
                para = "";
            } else if (tmp == ")") {
                bracketCnt--;
            } else if (tmp == "(") {
                bracketCnt++;
            } else {
                para += tmp;
            }
            if (bracketCnt == 0) { //parameters end
                paraCnt++;
                parameters.push_back(para);
                i++;
                break;
            }
        }
//        cout << "debug: undef " << name << " " << paraCnt << endl;
        bool found = false;
        for (int k = 0; k < functionMap.size(); k++) {
            functionMacro f = functionMap[k];
            if (f.name == name && f.paraCnt == paraCnt) {
                // found
                found = true;
                functionMap.erase(functionMap.begin() + k);
            }
        }
        if (!found) {
            cout << nf << endl;
            exit(0);
        }

    } else {
        if (variableMap.find(name) != variableMap.end()) {
            variableMap.erase(name);
        } else {
            cout << nf << endl;
            exit(0);
        }
    }
}


int main() {
    string line;
    string code;
    vector <string> lines;

    while (!cin.eof()) {
        getline(cin, line);
        lines.push_back(line);
    }

//    while (getline(cin, line)) {
//        if (line == "") break;
//        lines.push_back(line);
//    }


    for (int i = 0; i < lines.size(); ++i) {
        line = lines[i];
        if (line.substr(0, 1) == "#") { // #define, #undef
            handle_code(code);
            code = "";
            if (line.substr(0, 7) == def) {
                handle_def(line);
            } else { // #undef
                handle_undef(line);
            }
        } else { // normal code
            code += ("\n" + line + "\n");
            if (i == lines.size() - 1) handle_code(code);
        }
    }
    return 0;
}