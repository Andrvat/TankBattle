//
// Created by andrew on 18.11.2020.
//

#pragma once

#include "ITank.h"

namespace GameModel {

    static const unsigned int HEAVY_TANK_MOVE_RADIUS_MULTIPLIER = 1;

    static const unsigned int HEAVY_TANK_SHOT_POWER_MULTIPLIER = 3;
    static const unsigned int HEAVY_TANK_SHOT_RADIUS_MULTIPLIER = 3;

    static const unsigned int HEAVY_TANK_TANK_HP_MULTIPLIER = 5;


    class HeavyTank : public ITank {
    public:
        HeavyTank();
    };

}
