//
// Created by andrew on 18.11.2020.
//

#pragma once

#include <string>
#include "GameFieldObjects/ITank.h"

namespace GameModel {

    struct CellCoordinates {
        unsigned int x;
        unsigned int y;
    };

    enum class CellBorderType {
        Left,
        Up,
        Right,
        Down,
        LeftDown,
        RightDown,
        LeftUp,
        RightUp,
        NoBorder
    };

    class Cell {
    private:

        CellBorderType cellBorderType;
        CellCoordinates cellCoordinates;

        ITank *tank_ = nullptr;

    public:
        void setCellCoordinates(unsigned int x, unsigned int y);

        [[nodiscard]] CellCoordinates getCellCoordinates() const;

        void setBorderType(CellBorderType borderType);

        [[nodiscard]] CellBorderType getBorderType() const;
    };
}
