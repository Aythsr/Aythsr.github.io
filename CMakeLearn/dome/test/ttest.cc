#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }
    int a;
    a = atoi(argv[1]);
    std::cout << a << std::endl;
    return a;
}