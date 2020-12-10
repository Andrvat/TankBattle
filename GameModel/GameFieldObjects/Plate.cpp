//
// Created by user on 03.12.2020.
//

#include "Plate.h"

#include <stdexcept>

GameModel::Plate::Plate(GameModel::Cell positionCell) : positionCell(positionCell) {
    timer_ = 0;
    status_ = PlateStatus::NotCapture;
}

unsigned int GameModel::Plate::getTimer() const {
    return timer_;
}

void GameModel::Plate::increaseTimer() {
    ++timer_;
    if (timer_ == TankBattle::STEPS_TO_CAPTURE_PLATE) {
        status_ = PlateStatus::Captured;
    }
    if (timer_ > TankBattle::STEPS_TO_CAPTURE_PLATE) {
        throw std::runtime_error("STEPS TO CAPTURE PLATE OVERFLOW!");
    }
}

void GameModel::Plate::startCapture() {
    timer_ = 0;
    status_ = PlateStatus::Capturing;
}

void GameModel::Plate::resetCapture() {
    timer_ = 0;
    status_ = PlateStatus::NotCapture;
}

bool GameModel::Plate::isPlateCaptured() const {
    return status_ == PlateStatus::Captured;
}

bool GameModel::Plate::isPlateCapturing() const {
    return status_ == PlateStatus::Capturing;
}

GameModel::Cell GameModel::Plate::getPositionCell() const {
    return positionCell;
}
