//
// Created by user on 03.12.2020.
//

#include "HeavyTank.h"

GameModel::HeavyTank::HeavyTank() {
    hp_ = TANK_HP_FACTOR * HEAVY_TANK_TANK_HP_MULTIPLIER;

    shotRadius_ = SHOT_RADIUS_FACTOR * HEAVY_TANK_SHOT_RADIUS_MULTIPLIER;
    shotPower_ = SHOT_POWER_FACTOR * HEAVY_TANK_SHOT_POWER_MULTIPLIER;

    moveRadius_ = MOVE_RADIUS_FACTOR * HEAVY_TANK_MOVE_RADIUS_MULTIPLIER;

    tankCode_ = "H";
}
