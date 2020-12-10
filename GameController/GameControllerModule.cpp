//
// Created by user on 03.12.2020.
//

#include "GameControllerModule.h"
#include "../GameView/GameViewModule.h"

int GameController::GameControllerModule::getPlayersNumber() {
    int playersNumber;
    std::cin >> playersNumber;
    return playersNumber;
}

std::string GameController::GameControllerModule::getHumanName() {
    std::string name;
    std::cin >> name;
    return name;
}

TankBattle::CellCoordinates GameController::GameControllerModule::getStepCoordinates() {
    TankBattle::CellCoordinates coordinates{};
    int x = -1, y = -1;
    std::cin >> x >> y;
    while (x < 0 && y < 0) {
        GameView::GameViewModule::printInfoAboutNegativeCoordinates();
        std::cin >> x >> y;
    }
    coordinates.setX(x);
    coordinates.setY(y);
    return coordinates;
}

std::string GameController::GameControllerModule::getStepAction() {
    std::string action;
    std::cin >> action;
    return action;
}
