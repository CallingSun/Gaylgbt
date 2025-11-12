#include "manager/HotelManager.h"
#include <iostream>
#include <cstdlib>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    HotelManager hm("data");
    hm.runConsole();

    return 0;
}
//.\build\bin\HotelMini.exe   