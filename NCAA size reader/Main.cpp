#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <tchar.h>
#include <conio.h>
#include <strsafe.h>
#include <regex>
#include <unordered_map>


//reads external txt stack count file

int main() {

    SetConsoleTitleA("NCAA size reader");


    std::unordered_map<std::string, int> opcode_sizes = {

        {"pushvalue", 1},
        {"pushvalue_val", 2}, // Ensure your logic differentiates when 'val=' is present
        {"getnamedmember", 3},
        {"pushwordconstant", 3},
        {"getmember", 1},
        {"pushone", 1},
        {"pushzero", 1},
        {"pushregister", 2},
        {"pushconstant", 1}, // Correctly set to 1 as noted
        {"callmethod", 1},
        {"callnamedmethodpop", 2},
        {"newequals", 1},
        {"logicalnot", 1},
        {"branchiftrue", 4},
        {"setmember", 1},
        {"callmethodpop", 1},
        {"pushfalse", 1}, // Removed trailing slash
        {"pushtrue", 1},  // Removed trailing slash
        {"pushbyte", 2},
        {"newadd", 1},    // Removed trailing slash
        {"trace", 1},     // Removed trailing slash
        {"getmember", 1}, // Removed trailing slash, duplicate removed
        {"pushone", 1},   // Duplicate, already included above
        {"pushzero", 1},  // Duplicate, already included above
        {"callmethod", 1},// Duplicate, already included above
        {"callmethodpop", 1}, // Duplicate, already included above
        {"setmember", 1}, // Duplicate, already included above
        {"getnamedmember", 3}, // Duplicate, already included above
        {"newequals", 1}, // Duplicate, already included above
        {"logicalnot", 1}, // Duplicate, already included above
        {"return", 1},    // Removed trailing slash
        {"pop", 1},       // Removed trailing slash
        {"subtract", 1},  // Removed trailing slash
        {"branchalways", 3},
        {"newmethod", 2}, // Removed trailing slash
        {"initobject", 3},// Removed trailing slash
        {"pushshort", 3},
        {"setregister", 2},
        {"strictequals", 2}, // Removed trailing slash
        {"pushlong", 5},
        {"pushstring", 3},
        {"newobject", 2},
        {"new", 1},       // Removed trailing slash, assumed size
        {"divide", 1},    // Removed trailing slash, assumed size
        {"pushundefined", 1} // Removed trailing slash

    };


    std::string file_name = "opcode.txt"; 
    std::ifstream file(file_name);

    if (!file.is_open()) {

        std::cerr << "Unable to find file: " << file_name << " perhaps you are missing it?" << std::endl;

        system("pause"); // keep console open if file is missing

        return 1;

    }


    std::string code_string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());


    int size = 0;

    for (size_t i = 0; i < code_string.length(); i++) {

        if (code_string[i] == '<') {

            size_t j = code_string.find('>', i);

            if (j != std::string::npos) {

                std::string opcode = code_string.substr(i + 1, j - i - 1);

                if (opcode.find(" ") != std::string::npos) {

                    opcode = opcode.substr(0, opcode.find(" "));

                }

                if (opcode_sizes.count(opcode) > 0) {
                    if (opcode == "pushvalue") {
                        size_t k = code_string.find("val=", i);
                        if (k != std::string::npos && k < j) {
                            // pushvalue with value specified
                            size += opcode_sizes["pushvalue_val"]; // Only add the size for pushvalue_val
                            std::cout << "Opcode: " << opcode << " with val=, Size added: " << opcode_sizes["pushvalue_val"] << std::endl;
                        }
                        else {
                            // pushvalue without val
                            size += opcode_sizes[opcode]; // Add the size for pushvalue
                            std::cout << "Opcode: " << opcode << ", Size added: " << opcode_sizes[opcode] << std::endl;
                        }
                    }
                    else {
                        size += opcode_sizes[opcode]; // For all other opcodes
                        std::cout << "Opcode: " << opcode << ", Size added: " << opcode_sizes[opcode] << std::endl;
                    }
                }
                else {
                    // Attempt to handle opcodes with a trailing slash
                    if (!opcode.empty() && opcode.back() == '/') {
                        opcode.pop_back(); // Remove the last character, which is the slash
                        if (opcode_sizes.count(opcode) > 0) {
                            size += opcode_sizes[opcode]; // Add the size for the corrected opcode
                            std::cout << "Opcode (after removing slash): " << opcode << ", Size added: " << opcode_sizes[opcode] << std::endl;
                        }
                        else {
                            std::cout << "Unknown opcode after removing trailing slash: " << opcode << std::endl;
                        }
                    }
                    else {
                        std::cout << "Unknown opcode: " << opcode << std::endl;
                    }
                }

                i = j; // skip to the end of the opcode

            }

        }

        else {

            continue; // skip anything that isn't a '<' character

        }

    }


    std::cout << "The byte size of this code string is " << size << std::endl;

    system("pause"); // keep console open, needed for final builds

    return 0;



}