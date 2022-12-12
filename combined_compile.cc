/**
 * Run the compiler (which should already be built), and then gcc on the
 * generated assembly
 * 
 * @warning THIS FILE USES LINUX SYSTEM CALLS AND SHOULD ONLY BE EXECUTED IN
 * A TRUSTED ENVIRONMENT!
 */

#include <iostream>
#include <string>

#ifdef _WIN32
#error "Windows is not supported for compiling!"
#else
std::string colored(std::string txt, std::string color) {
    if (color == "red")
        return "\033[0;31m" + txt + "\033[0m";
    if (color == "green")
        return "\033[0;32m" + txt + "\033[0m";
    if (color == "grey")
        return "\033[0;90m" + txt + "\033[0m";
    if (color == "cyan")
        return "\033[0;36;1m" + txt + "\033[0m";
    return txt;
}
#endif

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }
    int status = system(("build/main " + std::string(argv[1])).c_str());
    int ret = WEXITSTATUS(status);
    std::cout << colored("EXIT CODE: " + std::to_string(ret), "cyan") <<
    std::endl;
    return ret;
}