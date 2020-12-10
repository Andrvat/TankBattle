//
// Created by user on 03.12.2020.
//

#pragma once

#include <string>

namespace TankBattle {

    const std::string SHOT_STEP = "shot";
    const std::string MOVE_STEP = "move";

    // the number must be a multiple of 5!
    static const unsigned int TANKS_BY_PLAYER_COUNT = 10;
    static const double LIGHT_TANKS_SHARE = 0.4;
    static const double MEDIUM_TANKS_SHARE = 0.4;
    static const double HEAVY_TANKS_SHARE = 0.2;

    static const unsigned int FIELD_HEIGHT = 25;
    static const unsigned int FIELD_WIDTH = 25;

    static const unsigned int STEPS_TO_CAPTURE_PLATE = 4;

    static const unsigned int MOVE_RADIUS_FACTOR = 3;

    static const unsigned int SHOT_POWER_FACTOR = 2;
    static const unsigned int SHOT_RADIUS_FACTOR = 3;

    static const unsigned int TANK_HP_FACTOR = 2;

}