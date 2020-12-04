//
// Created by user on 03.12.2020.
//

#include "Board.h"

GameModel::Cell &GameModel::Board::getCell(const unsigned int row, const unsigned int column) {
    return cellsBoard_[row][column];
}

void GameModel::Board::initCellsBoard() {
    for (unsigned int i = 0; i < TankBattle::FIELD_HEIGHT; i++) {
        std::vector<Cell> vector;
        cellsBoard_.push_back(vector);
        for (unsigned int j = 0; j < TankBattle::FIELD_WIDTH; j++) {
            Cell cell{};
            vector.push_back(cell);
        }
    }
}
