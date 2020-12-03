//
// Created by user on 03.12.2020.
//

#include "LightTank.h"

GameModel::LightTank::LightTank() {
    hp_ = TANK_HP_FACTOR * LIGHT_TANK_TANK_HP_MULTIPLIER;

    shotRadius_ = SHOT_RADIUS_FACTOR * LIGHT_TANK_SHOT_RADIUS_MULTIPLIER;
    shotPower_ = SHOT_POWER_FACTOR * LIGHT_TANK_SHOT_POWER_MULTIPLIER;

    moveRadius_ = MOVE_RADIUS_FACTOR * LIGHT_TANK_MOVE_RADIUS_MULTIPLIER;

    tankCode_ = "L";


}
