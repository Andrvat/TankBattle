//
// Created by andrew on 18.11.2020.
//

#include "Cell.h"

GameModel::CellBorderType GameModel::Cell::getBorderType() const {
    return cellBorderType;
}

void GameModel::Cell::setBorderType(const GameModel::CellBorderType borderType) {
    cellBorderType = borderType;
}

GameModel::CellCoordinates GameModel::Cell::getCellCoordinates() const {
    return cellCoordinates;
}

void GameModel::Cell::setCellCoordinates(const unsigned int x, const unsigned int y) {
    cellCoordinates.x = x;
    cellCoordinates.y = y;
}
