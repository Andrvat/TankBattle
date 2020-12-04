//
// Created by user on 03.12.2020.
//

#include "Plate.h"

#include <stdexcept>

GameModel::Plate::Plate(GameModel::Cell &positionCell) : positionCell(positionCell) {
    timer_ = 0;
    status_ = false;
}

unsigned int GameModel::Plate::getTimer() const {
    return timer_;
}

void GameModel::Plate::increaseTimer() {
    ++timer_;
    if (timer_ == TankBattle::STEPS_TO_CAPTURE_PLATE) {
        status_ = true;
    }
    if (timer_ > TankBattle::STEPS_TO_CAPTURE_PLATE) {
        throw std::runtime_error("STEPS TO CAPTURE PLATE OVERFLOW!");
        // TODO: Write own exception to process steps to capture plate overflow
    }
}

bool GameModel::Plate::isStatus() const {
    return status_;
}

void GameModel::Plate::startCapture() {
    status_ = true;
}

void GameModel::Plate::resetCapture() {
    timer_ = 0;
    status_ = false;
}

bool GameModel::Plate::isPlateCaptured() const {
    return status_;
}
