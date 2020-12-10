//
// Created by user on 03.12.2020.
//

#pragma once

#include <vector>

#include "Cell.h"
#include "../GlobalParams.h"

namespace GameModel {

    class Board {
    private:
        std::vector<std::vector<Cell>> cellsBoard_;
    public:

        void initCellsBoard();

        Cell getCell(unsigned int row, unsigned int column);
    };

}
