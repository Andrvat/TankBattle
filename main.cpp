#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <ctime>

#include "TankBattleLauncher.h"

int main() {
    srand(std::time(NULL));
    try {
        TankBattle::TankBattleLauncher::startGame();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    system("pause");
    return 0;
}
