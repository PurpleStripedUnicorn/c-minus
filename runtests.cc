/**
 * Run all tests in the "tests" folder
 * 
 * This is done by both compiling them with gcc and compiling them with the
 * custom compiler and comparing the results
 * 
 * This program assumes that the current working directory has "build" and
 * "build/tmp" folders in it
 * 
 * @warning THIS FILE USES LINUX COMMANDS DIRECTLY TO RUN TESTS. IT SHOULD ONLY
 * BE RUN IN A TRUSTED ENVIRONMENT! ALSO MAKE SURE THAT YOU ARE RUNNING IT
 * CORRECTLY TO PREVENT LOSS OF DATA OR CORRUPTION!
 */

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

namespace fs = std::filesystem;

const std::string prependC = R"!--!(
#include "stdio.h"

void print(int num) {
    printf("%d\n", num);
}
)!--!";

#ifdef _WIN32
#error "Windows is not supported for testing!"
#else
std::string colored(std::string txt, std::string color) {
    if (color == "red")
        return "\033[0;31;1m" + txt + "\033[0m";
    if (color == "green")
        return "\033[0;32;1m" + txt + "\033[0m";
    if (color == "cyan")
        return "\033[0;36;1m" + txt + "\033[0m";
    if (color == "grey")
        return "\033[0;90m" + txt + "\033[0m";
    return txt;
}
#endif

std::vector<std::string> getTestFiles(const std::string &testfolder) {
    std::vector<std::string> out;
    for (fs::recursive_directory_iterator it("tests/" + testfolder), end; it !=
    end; it++)
        if (!fs::is_directory(it->path()))
            out.push_back(it->path().relative_path().string());
    std::sort(out.begin(), out.end());
    return out;
}

std::string getFileContents(std::string filename) {
    std::ifstream file(filename);
    std::stringstream stream;
    stream << file.rdbuf();
    std::string content = stream.str();
    file.close();
    return content;
}

std::string stripWhitespace(std::string inp) {
    size_t start = 0;
    while (start < inp.size() && (inp[start] == '\n' || inp[start] == '\t' ||
    inp[start] == ' '))
        start++;
    size_t end = inp.size();
    while (end > start && (inp[end - 1] == '\n' || inp[end - 1] == '\t' ||
    inp[end - 1] == ' '))
        end--;
    return inp.substr(start, end - start);
}

int main(int argc, char *argv[]) {
    size_t pos = 0, neg = 0;
    bool fullout = false;
    std::string testfolder = "";
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-f")
            fullout = true;
        else
            testfolder = argv[i];
    }
    std::cout << std::endl;
    for (const std::string &filename : getTestFiles(testfolder)) {
        system("print > build/tmp/test_ref.c");
        std::ofstream refSrcFile("build/tmp/test_ref.c");
        std::ifstream inpFile(filename);
        refSrcFile << prependC << inpFile.rdbuf();
        refSrcFile.close();
        inpFile.close();
        // Run default GCC compiler
        int refStatus = system("gcc -o build/tmp/test_ref build/tmp/test_ref.c 2>"
        " build/tmp/err.txt");
        int refCode = WEXITSTATUS(refStatus);
        // Run the custom compiler
        int cmpStatus = system(("build/main " + filename + " > build/tmp/"
        "test_cmp.s 2> build/tmp/err.txt").c_str());
        int cmpCode = WEXITSTATUS(cmpStatus);
        system("gcc -o build/tmp/test_cmp build/tmp/test_cmp.s 2> build/tmp/"
        "err.txt");
        // Run both generated programs and compare the outputs
        system("build/tmp/test_ref > build/tmp/test_ref_result"
        ".txt 2> build/tmp/err.txt");
        system("build/tmp/test_cmp > build/tmp/test_cmp_result"
        ".txt 2> build/tmp/err.txt");
        std::string ref = getFileContents("build/tmp/test_ref_result.txt");
        std::string cmp = getFileContents("build/tmp/test_cmp_result.txt");
        bool success = (refCode == 0 && cmpCode == 0 && ref == cmp) || (refCode
        != 0 && cmpCode != 0);
        if (success) {
            pos++;
            std::cout << colored("[ SUCCESS ] ", "green") << filename <<
            std::endl;
        } else {
            neg++;
            std::cout << colored("[ FAILURE ] ", "red") << filename <<
            std::endl;
        }
        if (!success || fullout) {
            std::cout << "Expected output:  " << stripWhitespace(ref) <<
            std::endl;
            std::cout << colored("   Exit code:     " + std::to_string(refCode),
            "grey") << std::endl;
            std::cout << "Instead got:      " << stripWhitespace(cmp) <<
            std::endl;
            std::cout << colored("   Exit code:     " + std::to_string(cmpCode),
            "grey") << std::endl;
        }
    }
    std::cout << std::endl << colored("=======================================",
    neg == 0 ? (testfolder == "" ? "green" : "cyan") : "red") << std::endl;
    if (neg == 0)
        std::cout << colored("ALL " + std::to_string(pos) + " TEST(S) PASSED",
        testfolder == "" ? "green" : "cyan");
    else
        std::cout << colored(std::to_string(pos) + " TEST(S) PASSED, " +
        std::to_string(neg) + " TEST(S) FAILED", "red");
    std::cout << std::endl << std::endl;
    if (neg == 0)
        return 0;
    else
        return 1;
}