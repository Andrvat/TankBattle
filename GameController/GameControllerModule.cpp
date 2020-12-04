//
// Created by user on 03.12.2020.
//

#include "GameControllerModule.h"

size_t GameController::GameControllerModule::getPlayersNumber() {
    return 0;
}

std::string GameController::GameControllerModule::getHumanName() {
    return std::__cxx11::string();
}

TankBattle::CellCoordinates GameController::GameControllerModule::getStepCoordinates() {
    return TankBattle::CellCoordinates();
}

std::string GameController::GameControllerModule::getStepAction() {
    return std::__cxx11::string();
}
