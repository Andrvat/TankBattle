//
// Created by andrew on 18.11.2020.
//

#pragma once

#include "ITank.h"

namespace GameModel {

    static const unsigned int MEDIUM_TANK_MOVE_RADIUS_MULTIPLIER = 2;

    static const unsigned int MEDIUM_TANK_SHOT_POWER_MULTIPLIER = 3;
    static const unsigned int MEDIUM_TANK_SHOT_RADIUS_MULTIPLIER = 4;

    static const unsigned int MEDIUM_TANK_TANK_HP_MULTIPLIER = 3;


    class MediumTank : public ITank {
    public:
        explicit MediumTank(GameModel::Cell positionCell);
    };

}
