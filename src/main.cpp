#include <iostream>
#include <cstdlib> 

int main() {
    int result = system("node ../api/test.js");
    if (result != 0) {
        std::cerr << "loi khi goi API!" << std::endl;
    }
    return 0;
}
