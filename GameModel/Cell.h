//
// Created by andrew on 18.11.2020.
//

#pragma once

#include <string>

#include "../GlobalParams.h"
#include "../CellCoordinates.h"

namespace GameModel {

    class Cell {
    private:

        TankBattle::CellCoordinates cellCoordinates;

    public:
        void setCellCoordinates(unsigned int x, unsigned int y);

        [[nodiscard]] TankBattle::CellCoordinates getCellCoordinates() const;
    };
}
