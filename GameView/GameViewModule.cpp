//
// Created by user on 03.12.2020.
//

#include "GameViewModule.h"

GameView::GameViewModule::GameViewModule(GameModel::GameModelModule &gameModel) : gameModel_(gameModel) {
    this->gameModel_.attachObserver(this);
}

void GameView::GameViewModule::removeThisFromObserversList() {
    this->gameModel_.detachObserver(this);
}

void GameView::GameViewModule::update() {
    initFieldMap();

    for (size_t i = 0; i < gameModel_.getFirstPlayer()->getAliveTanksCounter(); i++) {
        TankBattle::CellCoordinates tankCoordinates = gameModel_.getFirstPlayer()->getTank(
                i)->getPositionCell().getCellCoordinates();
        std::string tankType = gameModel_.getFirstPlayer()->getTank(i)->getTankCode();
        tankType += "*";
        fieldMap_[tankCoordinates.getX() + 1][tankCoordinates.getY() + 2 * tankCoordinates.getY() + 1 +
                                              3] = tankType[0];
        fieldMap_[tankCoordinates.getX() + 1][tankCoordinates.getY() + 2 * tankCoordinates.getY() + 2 +
                                              3] = tankType[1];
    }

    for (size_t i = 0; i < gameModel_.getSecondPlayer()->getAliveTanksCounter(); i++) {
        TankBattle::CellCoordinates tankCoordinates = gameModel_.getSecondPlayer()->getTank(
                i)->getPositionCell().getCellCoordinates();
        std::string tankType = gameModel_.getSecondPlayer()->getTank(i)->getTankCode();
        tankType += "+";
        std::swap(tankType[0], tankType[1]);
        fieldMap_[tankCoordinates.getX() + 1][tankCoordinates.getY() + 2 * tankCoordinates.getY() + 1 +
                                              3] = tankType[0];
        fieldMap_[tankCoordinates.getX() + 1][tankCoordinates.getY() + 2 * tankCoordinates.getY() + 2 +
                                              3] = tankType[1];
    }

    printFieldMapInConsole();
}

void GameView::GameViewModule::initFieldMap() {
    fieldMap_.clear();
    std::string currentFieldMapLine;
    currentFieldMapLine += "XY _";
    for (unsigned int i = 0; i < TankBattle::FIELD_WIDTH; i++) {
        currentFieldMapLine += std::to_string(i);
        if (i >= 10) {
            currentFieldMapLine += "_";
        } else {
            currentFieldMapLine += "__";
        }
    }
    // Deleted unnecessary _ in line
    currentFieldMapLine.pop_back();
    fieldMap_.push_back(currentFieldMapLine);

    for (unsigned int i = 0; i < TankBattle::FIELD_HEIGHT; i++) {
        currentFieldMapLine.clear();
        currentFieldMapLine += std::to_string(i);
        if (i >= 10) {
            currentFieldMapLine += " ";
        } else {
            currentFieldMapLine += "  "; // two whitespaces
        }
        for (unsigned int j = 0; j < TankBattle::FIELD_WIDTH; j++) {
            currentFieldMapLine += "|";
            currentFieldMapLine += "__";
        }
        currentFieldMapLine += "|";
        fieldMap_.push_back(currentFieldMapLine);
    }

    // TODO: field map doesn't work with big sizes of height and width
    fieldMap_[TankBattle::FIELD_HEIGHT / 2 + 1][4] = '#';
    fieldMap_[TankBattle::FIELD_HEIGHT / 2 + 1][5] = '#';

    fieldMap_[TankBattle::FIELD_HEIGHT / 2 + 1][3 + TankBattle::FIELD_WIDTH * 3 - 1] = '#';
    fieldMap_[TankBattle::FIELD_HEIGHT / 2 + 1][3 + TankBattle::FIELD_WIDTH * 3 - 2] = '#';
}

void GameView::GameViewModule::printFieldMapInConsole() const {
    for (const auto &i : fieldMap_) {
        std::cout << i << std::endl;
    }
}

void GameView::GameViewModule::printStartMessage() {
    std::cout << "Welcome to the Tank Battle by Andrew Valitov" << std::endl
              << "There are some game's rules:" << std::endl
              << "If you go to win, you need to kill all enemy's tanks or capture the plate" << std::endl
              << "Both players have own plates on the middle of their sides" << std::endl
              << "You need to move your tank at this plate's cell and stay it during in "
              << TankBattle::STEPS_TO_CAPTURE_PLATE << " steps" << std::endl
              << "Every player has " << TankBattle::TANKS_BY_PLAYER_COUNT << " tanks" << std::endl
              << "Every your steps you will see the current game map" << std::endl
              << "To make a step, follow next example:" << std::endl
              << "First, you will choose coordinates of your available tanks" << std::endl
              << "Second, you will choose the type of action which you want to do. It can be move or shot action"
              << std::endl
              << "After that, you finally will choose coordinates in which you want to make your step" << std::endl
              << "Good luck!" << std::endl;
}

void GameView::GameViewModule::askCoordinates() {
    std::cout << "Enter your XY coordinates: ";
}

void GameView::GameViewModule::askCoordinates(const std::string &forWhichAction) {
    std::cout << "Enter your XY coordinates for " << forWhichAction << ": ";
}

void GameView::GameViewModule::askPlayersName(const bool playerNumber) {
    if (playerNumber) {
        std::cout << "Enter first player name:";
    } else {
        std::cout << "Enter second player name:";
    }
}

void GameView::GameViewModule::askPlayersNumber() {
    std::cout << "Enter how much players will be playing (1 - your enemy is BOT, 2 - your friend):";
}

void GameView::GameViewModule::printWhatPlayerIsGoing() {
    if (gameModel_.whichPlayerIsGoing() == FIRST_PLAYER_GOES) {
        std::cout << gameModel_.getFirstPlayer()->getName() << " is going. Enter your step..." << std::endl;
    } else if (gameModel_.whichPlayerIsGoing() == SECOND_PLAYER_GOES) {
        std::cout << gameModel_.getSecondPlayer()->getName() << " is going. Enter your step..." << std::endl;
    }
}

void GameView::GameViewModule::printAboutUnreachableCoordinates() {
    std::cout << "Your entered coordinates are not reachable! Try to choose correct coordinates again!.." << std::endl;
}

void GameView::GameViewModule::printAboutInvalidAction() {
    std::cout << "Your entered coordinates action is not valid! Choose action between " << TankBattle::MOVE_STEP
              << " and " << TankBattle::SHOT_STEP << " again!.." << std::endl;
}

void GameView::GameViewModule::printAboutTheWinner() const {
    std::cout << "Player " << gameModel_.getTheWinnersName() << " is the winner! Game is finished..." << std::endl;
}

void GameView::GameViewModule::printInfoAboutNegativeCoordinates() {
    std::cout << "Entered coordinates must be zero or positive! Try to enter again: ";
}

void GameView::GameViewModule::askAction() {
    std::cout << "Enter the action (move or shot):";
}



