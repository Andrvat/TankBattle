//
// Created by andrew on 18.11.2020.
//

#include "Cell.h"

TankBattle::CellCoordinates GameModel::Cell::getCellCoordinates() const {
    return cellCoordinates;
}

void GameModel::Cell::setCellCoordinates(const unsigned int x, const unsigned int y) {
    cellCoordinates.setX(x);
    cellCoordinates.setY(y);
}
