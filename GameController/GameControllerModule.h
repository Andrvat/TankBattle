//
// Created by user on 03.12.2020.
//

#pragma once

#include <string>
#include <iostream>

#include "../GlobalParams.h"
#include "../CellCoordinates.h"

namespace GameController {

    class GameControllerModule {
    public:
        int getPlayersNumber();

        std::string getHumanName();

        TankBattle::CellCoordinates getStepCoordinates();

        std::string getStepAction();

    };
}

