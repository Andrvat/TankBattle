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
        static int getPlayersNumber();

        static std::string getHumanName();

        static TankBattle::CellCoordinates getStepCoordinates();

        static std::string getStepAction();

    };
}

