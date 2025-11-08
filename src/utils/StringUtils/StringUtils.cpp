#include "StringUtils.h"
#include <sstream>
#include <algorithm>
#include <fstream>

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> out;
    
    std::string cur;
    
    std::stringstream ss(s);
    
    while (std::getline(ss, cur, delim)) {
        out.push_back(cur);
    }
    
    return out;
}

std::string trim(const std::string &s) {
    std::size_t a = s.find_first_not_of(" \t\r\n");
    
    if (a == std::string::npos) return "";
    
    std::size_t b = s.find_last_not_of(" \t\r\n");
    
    return s.substr(a, b - a + 1);
}
