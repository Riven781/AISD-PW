#include <iostream>
#include "test.h"

int main(int argc, char const *argv[])
{
    if (testDoubleList() == 0){
        std::cout << "Testy zostaly zakonczone pomyslnie" << std::endl;
    }
    return 0;
}
