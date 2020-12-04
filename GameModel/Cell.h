//
// Created by andrew on 18.11.2020.
//

#pragma once

#include <string>

#include "../GlobalParams.h"
#include "../CellCoordinates.h"

namespace GameModel {

//    enum class CellBorderType {
//        Left,
//        Up,
//        Right,
//        Down,
//        LeftDown,
//        RightDown,
//        LeftUp,
//        RightUp,
//        NoBorder
//    };

    class Cell {
    private:

       // CellBorderType cellBorderType;
        TankBattle::CellCoordinates cellCoordinates;

    public:
        void setCellCoordinates(unsigned int x, unsigned int y);

        [[nodiscard]] TankBattle::CellCoordinates getCellCoordinates() const;

        //void setBorderType(CellBorderType borderType);

        //[[nodiscard]] CellBorderType getBorderType() const;
    };
}
