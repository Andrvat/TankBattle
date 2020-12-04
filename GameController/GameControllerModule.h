//
// Created by user on 03.12.2020.
//

#pragma once

#include <string>

#include "../GlobalParams.h"
#include "../CellCoordinates.h"

namespace GameController {

    class GameControllerModule {
    public:
        size_t getPlayersNumber();

        std::string getHumanName();

        TankBattle::CellCoordinates getStepCoordinates();

        std::string getStepAction();

    };
}

