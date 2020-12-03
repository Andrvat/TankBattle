//
// Created by user on 03.12.2020.
//

#include "PlayerPlate.h"

#include <stdexcept>

GameModel::PlayerPlate::PlayerPlate() {
    timer_ = 0;
    status_ = false;
}

unsigned int GameModel::PlayerPlate::getTimer() const {
    return timer_;
}

void GameModel::PlayerPlate::increaseTimer() {
    ++timer_;
    if (timer_ == STEPS_TO_CAPTURE_PLATE) {
        status_ = true;
    }
    if (timer_ > STEPS_TO_CAPTURE_PLATE) {
        throw std::runtime_error("STEPS TO CAPTURE PLATE OVERFLOW!");
        // TODO: Write own exception to process steps to capture plate overflow
    }
}

bool GameModel::PlayerPlate::isStatus() const {
    return status_;
}

void GameModel::PlayerPlate::startCapture() {
    status_ = true;
}

void GameModel::PlayerPlate::resetCapture() {
    timer_ = 0;
    status_ = false;
}

bool GameModel::PlayerPlate::isPlateCaptured() const {
    return status_;
}
