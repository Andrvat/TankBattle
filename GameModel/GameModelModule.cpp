//
// Created by user on 03.12.2020.
//
#include "GameModelModule.h"

void GameModel::GameModelModule::attachObserver(GameView::IObserver *observer) {
    observersList_.push_back(observer);
}

void GameModel::GameModelModule::detachObserver(GameView::IObserver *observer) {
    observersList_.remove(observer);
}

void GameModel::GameModelModule::notifyObservers() {
    auto iterator = observersList_.begin();
    while (iterator != observersList_.end()) {
        (*iterator)->update();
        ++iterator;
    }
}

size_t GameModel::GameModelModule::getObserversListSize() const {
    return observersList_.size();
}

void GameModel::GameModelModule::launchGameModel(GameController::GameControllerModule *controller) {
    modelBoard_.initCellsBoard();
    size_t playersNumber = controller->getPlayersNumber();
    std::string humanName;
    switch (playersNumber) {
        case 1: {
            humanName = controller->getHumanName();
            firstPlayer_ = new HumanPlayer(humanName);
            secondPlayer_ = new BotPlayer();
        }
            break;

        case 2:
            humanName = controller->getHumanName();
            firstPlayer_ = new HumanPlayer(humanName);
            humanName = controller->getHumanName();
            secondPlayer_ = new HumanPlayer(humanName);
            break;

        default:
            throw std::runtime_error("Doesn't work with less than one and more than two players!");
    }

    notifyObservers();
}

void GameModel::GameModelModule::placeGameFieldObjects() {
    initPlayersObjects(firstPlayer_, 0);
    initPlayersObjects(secondPlayer_, TankBattle::FIELD_WIDTH - 1);
    notifyObservers();
}

void GameModel::GameModelModule::initPlayersObjects(GameModel::IPlayer *player, const unsigned int playerSide) {
    if (TankBattle::TANKS_BY_PLAYER_COUNT > TankBattle::FIELD_HEIGHT) {
        throw std::logic_error("Couldn't place all game objects at the field with this FIELD_HEIGHT!");
    }
    if (TankBattle::LIGHT_TANKS_SHARE + TankBattle::MEDIUM_TANKS_SHARE + TankBattle::HEAVY_TANKS_SHARE != 1) {
        throw std::runtime_error("Wrong radio of tanks!");
    }

    /*
     * Start of place tanks
     */
    std::vector<unsigned int> randomTanksPositions;
    for (unsigned int i = 0; i < TankBattle::TANKS_BY_PLAYER_COUNT; i++) {
        randomTanksPositions.push_back((unsigned int) rand() % TankBattle::FIELD_HEIGHT);
    }

    unsigned int placedTanksCounter = 0;
    for (unsigned int i = 0;
         i < (unsigned int) TankBattle::TANKS_BY_PLAYER_COUNT * TankBattle::LIGHT_TANKS_SHARE; i++) {
        player->addNewTank(
                new GameModel::LightTank(modelBoard_.getCell(randomTanksPositions[placedTanksCounter], playerSide)));
        placedTanksCounter++;
    }
    for (unsigned int i = 0;
         i < (unsigned int) TankBattle::TANKS_BY_PLAYER_COUNT * TankBattle::MEDIUM_TANKS_SHARE; i++) {
        player->addNewTank(
                new GameModel::MediumTank(modelBoard_.getCell(randomTanksPositions[placedTanksCounter], playerSide)));
        placedTanksCounter++;
    }
    for (unsigned int i = 0;
         i < (unsigned int) TankBattle::TANKS_BY_PLAYER_COUNT * TankBattle::HEAVY_TANKS_SHARE; i++) {
        player->addNewTank(
                new GameModel::HeavyTank(modelBoard_.getCell(randomTanksPositions[placedTanksCounter], playerSide)));
        placedTanksCounter++;
    }
    /*
     * End of place tanks
    */

    player->addNewPlate(new GameModel::Plate(modelBoard_.getCell(TankBattle::FIELD_HEIGHT / 2, playerSide)));
}

bool GameModel::GameModelModule::isSomebodyWon() const {
    return firstPlayer_->isWon() || secondPlayer_->isWon();
}

void GameModel::GameModelModule::setFirstPlayerStep() {
    whichPlayerIsGoing_ = FIRST_PLAYER_GOES;
    notifyObservers();
}

void GameModel::GameModelModule::setSecondPlayerStep() {
    whichPlayerIsGoing_ = SECOND_PLAYER_GOES;
    notifyObservers();
}

bool
GameModel::GameModelModule::isCellCoordinatesAvailableForCurrentPlayer(TankBattle::CellCoordinates coordinates) const {
    bool isFound = false;
    if (whichPlayerIsGoing_ == FIRST_PLAYER_GOES) {
        for (unsigned int i = 0; i < firstPlayer_->getAliveTanksCounter(); i++) {
            if (firstPlayer_->getTank(i)->getPositionCell().getCellCoordinates() == coordinates) {
                isFound = true;
            }
        }
    } else if (whichPlayerIsGoing_ == SECOND_PLAYER_GOES) {
        for (unsigned int i = 0; i < secondPlayer_->getAliveTanksCounter(); i++) {
            if (secondPlayer_->getTank(i)->getPositionCell().getCellCoordinates() == coordinates) {
                isFound = true;
            }
        }
    }
    return isFound;
}

bool GameModel::GameModelModule::isAction(const std::string &action) {
    return action == TankBattle::SHOT_STEP || action == TankBattle::MOVE_STEP;
}
