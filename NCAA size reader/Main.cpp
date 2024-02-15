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


//reads emmbedded stack count

//int main() {
//    SetConsoleTitleA("NCAA size reader");
//
//    std::unordered_map<std::string, int> opcode_sizes = {
//    {"pushvalue", 1},
//    {"pushvalue_val", 2},
//    {"getnamedmember", 2},
//    {"pushwordconstant", 3},
//    {"getmember", 1},
//    {"pushone", 1},
//    {"pushzero", 1},
//    {"pushregister", 2},
//    {"pushconstant", 3},
//    {"callmethod", 1},
//    {"callnamedmethodpop", 2},
//    {"newequals", 1},
//    {"logicalnot", 1},
//    {"branchiftrue", 4},
//    {"setmember", 1},
//    {"callmethodpop", 1},
//    {"pushfalse/", 1},
//    {"pushtrue/", 1},
//    {"pushbyte", 2},
//    {"newadd/", 1},
//    {"trace/", 1},
//    {"getmember/", 1},
//    {"pushone/", 1},
//    {"pushzero/", 1},
//    {"callmethod/", 1},
//    {"callmethodpop/", 1},
//    {"setmember/", 1},
//    {"getnamedmember/", 2},
//    {"newequals/", 1},
//    {"logicalnot/", 1},
//    {"return/", 1},
//    {"pop/", 1},
//    {"subtract/", 1},
//    {"branchalways",3},
//    {"newmethod/", 2},
//    {"initobject/", 3},
//    {"pushshort", 3},
//    {"setregister", 2},
//    {"strictequals/", 2},
//    {"pushlong", 5},
//    {"pushstring", 3},
//    {"newobject", 2}
//    };
//
//    std::string code_string = R"(
//<pushregister val="1"/>
//                            <pushwordconstant val="514"/>
//                            <getmember/>
//                            <pushregister val="1"/>
//                            <getnamedmember val="180"/>
//                            <pushbyte val="2"/>
//                            <pushvalue val="56"/>
//                            <getnamedmember val="57"/>
//                            <getnamedmember val="94"/>
//                            <callnamedmethodpop val="95"/>
//    )";
//
//    int size = 0;
//    for (size_t i = 0; i < code_string.length(); i++) {
//        if (code_string[i] == '<') {
//            size_t j = code_string.find('>', i);
//            if (j != std::string::npos) {
//                std::string opcode = code_string.substr(i + 1, j - i - 1);
//                if (opcode.find(" ") != std::string::npos) {
//                    opcode = opcode.substr(0, opcode.find(" "));
//                }
//                if (opcode_sizes.count(opcode) > 0) {
//                    size += opcode_sizes[opcode];
//                    if (opcode == "pushvalue") {
//                        size_t k = code_string.find("val=", i);
//                        if (k != std::string::npos && k < j) {
//                            // pushvalue with value specified
//                            size += opcode_sizes["pushvalue_val"];
//                        }
//                    }
//                }
//                else {
//                    std::cout << "Unknown opcode: " << opcode << std::endl;
//                }
//                i = j; // skip to the end of the opcode
//            }
//        }
//        else {
//            continue; // skip anything that isn't a '<' character
//        }
//    }
//
//
//    std::cout << "The byte size of this code string is " << size << std::endl;
//
//    return 0;
//}

//reads external txt stack count file

int main() {

    SetConsoleTitleA("NCAA size reader");


    std::unordered_map<std::string, int> opcode_sizes = {

        {"pushvalue", 1},

        {"pushvalue_val", 2},

        {"getnamedmember", 3},

        {"pushwordconstant", 3},

        {"getmember", 1},

        {"pushone", 1},

        {"pushzero", 1},

        {"pushregister", 2},

        {"pushconstant", 1}, //was 2

        {"callmethod", 1},

        {"callnamedmethodpop", 2},

        {"newequals", 1},

        {"logicalnot", 1},

        {"branchiftrue", 4},

        {"setmember", 1},

        {"callmethodpop", 1}, //was 1

        {"pushfalse/", 1},

        {"pushtrue/", 1},

        {"pushbyte", 2},

        {"newadd/", 1},

        {"trace/", 1},

        {"getmember/", 1},

        {"pushone/", 1},

        {"pushzero/", 1},

        {"callmethod/", 1},

        {"callmethodpop/", 1},

        {"setmember/", 1},

        {"getnamedmember/", 3},

        {"newequals/", 1},

        {"logicalnot/", 1},

        {"return/", 1},

        {"pop/", 1},

        {"subtract/", 1},

        {"branchalways",3},

        {"newmethod/", 2},

        {"initobject/", 3},

        {"pushshort", 3},

        {"setregister", 2},

        {"strictequals/", 2},

        {"pushlong", 5},

        {"pushstring", 3},

        {"newobject", 2},

        {"new/", 1}, // i assume one?

        {"divide/", 1}, // i assume one?

        {"pushundefined/", 1}

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

                    size += opcode_sizes[opcode];

                    if (opcode == "pushvalue") {

                        size_t k = code_string.find("val=", i);

                        if (k != std::string::npos && k < j) {

                            // pushvalue with value specified

                            size += opcode_sizes["pushvalue_val"];

                        }

                    }

                }

                else {

                    std::cout << "Unknown opcode: " << opcode << std::endl;

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