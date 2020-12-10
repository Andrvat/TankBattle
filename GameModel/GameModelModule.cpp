//
// Created by user on 03.12.2020.
//

#include "../GameView/GameViewModule.h"
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

[[maybe_unused]] size_t GameModel::GameModelModule::getObserversListSize() const {
    return observersList_.size();
}

void GameModel::GameModelModule::launchGameModel() {
    modelBoard_.initCellsBoard();
    int playersNumber = GameController::GameControllerModule::getPlayersNumber();
    std::string humanName;
    switch (playersNumber) {
        case 1:
            GameView::GameViewModule::askPlayersName(FIRST_PLAYER_GOES);
            humanName = GameController::GameControllerModule::getHumanName();
            firstPlayer_ = new HumanPlayer(humanName);
            secondPlayer_ = new BotPlayer();
            isSecondPlayerBot_ = true;
            break;

        case 2:
            GameView::GameViewModule::askPlayersName(FIRST_PLAYER_GOES);
            humanName = GameController::GameControllerModule::getHumanName();
            firstPlayer_ = new HumanPlayer(humanName);
            GameView::GameViewModule::askPlayersName(SECOND_PLAYER_GOES);
            humanName = GameController::GameControllerModule::getHumanName();
            secondPlayer_ = new HumanPlayer(humanName);
            isSecondPlayerBot_ = false;
            break;

        default:
            throw std::runtime_error("Doesn't work with less than one and more than two players!");
    }
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
     * Start of placing tanks
     */

    std::vector<unsigned int> randomTanksPositions;
    while (randomTanksPositions.size() != TankBattle::TANKS_BY_PLAYER_COUNT) {
        auto generated = ((unsigned int) rand()) % TankBattle::FIELD_HEIGHT;
        if (std::find(randomTanksPositions.begin(), randomTanksPositions.end(), generated) ==
            randomTanksPositions.end()) {
            randomTanksPositions.push_back(generated);
        }
    }


    auto placedTanksCounter = randomTanksPositions.begin();
    for (unsigned int i = 0;
         i < (unsigned int) TankBattle::TANKS_BY_PLAYER_COUNT * TankBattle::LIGHT_TANKS_SHARE; i++) {
        player->addNewTank(
                new GameModel::LightTank(modelBoard_.getCell(*placedTanksCounter, playerSide)));
        placedTanksCounter++;
    }
    for (unsigned int i = 0;
         i < (unsigned int) TankBattle::TANKS_BY_PLAYER_COUNT * TankBattle::MEDIUM_TANKS_SHARE; i++) {
        player->addNewTank(
                new GameModel::MediumTank(modelBoard_.getCell(*placedTanksCounter, playerSide)));
        placedTanksCounter++;
    }
    for (unsigned int i = 0;
         i < (unsigned int) TankBattle::TANKS_BY_PLAYER_COUNT * TankBattle::HEAVY_TANKS_SHARE; i++) {
        player->addNewTank(
                new GameModel::HeavyTank(modelBoard_.getCell(*placedTanksCounter, playerSide)));
        placedTanksCounter++;
    }
    /*
     * End of place tanks
    */

    player->addNewPlate(new GameModel::Plate(modelBoard_.getCell(TankBattle::FIELD_HEIGHT / 2, playerSide)));
    player->setAliveTanksCounter(TankBattle::TANKS_BY_PLAYER_COUNT);
}

bool GameModel::GameModelModule::isSomebodyWon() const {
    return firstPlayer_->isWon() || secondPlayer_->isWon();
}

std::string GameModel::GameModelModule::getTheWinnersName() const {
    if (firstPlayer_->isWon()) {
        return firstPlayer_->getName();
    } else if (secondPlayer_->isWon()) {
        return secondPlayer_->getName();
    } else {
        throw std::runtime_error("Nobody is still winning!");
    }
}

void GameModel::GameModelModule::setFirstPlayerStep() {
    whichPlayerIsGoing_ = FIRST_PLAYER_GOES;
}

bool
GameModel::GameModelModule::isCellCoordinatesAvailableForCurrentPlayerChoice(
        TankBattle::CellCoordinates coordinates, size_t &objectTypeIndex) const {
    IPlayer *player = chooseCurrentPlayer();
    bool isFound = false;
    for (unsigned int i = 0; i < player->getAliveTanksCounter(); i++) {
        if (player->getTank(i)->getPositionCell().getCellCoordinates() == coordinates) {
            objectTypeIndex = i;
            isFound = true;
        }
    }
    return isFound;
}

bool GameModel::GameModelModule::isAction(const std::string &action) {
    return action == TankBattle::SHOT_STEP || action == TankBattle::MOVE_STEP;
}

bool GameModel::GameModelModule::isCellCoordinatesAvailableForMakeStep(TankBattle::CellCoordinates coordinates,
                                                                       const size_t &objectTypeIndex,
                                                                       const std::string &action) const {
    bool isAvailable = false;
    TankBattle::CellCoordinates tankCoordinates = chooseCurrentPlayer()->getTank(
            objectTypeIndex)->getPositionCell().getCellCoordinates();
    if (action == TankBattle::SHOT_STEP) {
        if (abs((int) tankCoordinates.getX() - (int) coordinates.getX()) <=
            chooseCurrentPlayer()->getTank(objectTypeIndex)->getShotRadius() &&
            abs((int) tankCoordinates.getY() - (int) coordinates.getY()) <=
            chooseCurrentPlayer()->getTank(objectTypeIndex)->getShotRadius()) {
            isAvailable = true;
        }
    } else if (action == TankBattle::MOVE_STEP) {
        if (abs((int) tankCoordinates.getX() - (int) coordinates.getX()) <=
            chooseCurrentPlayer()->getTank(objectTypeIndex)->getMoveRadius() &&
            abs((int) tankCoordinates.getY() - (int) coordinates.getY()) <=
            chooseCurrentPlayer()->getTank(objectTypeIndex)->getMoveRadius()) {
            isAvailable = true;
        }

        // Checking for occupied cell by enemy player
        IPlayer *player = chooseEnemyPlayer();
        for (unsigned int i = 0; i < player->getAliveTanksCounter(); i++) {
            if (player->getTank(i)->getPositionCell().getCellCoordinates() == coordinates) {
                isAvailable = false;
            }
        }
    }
    return isAvailable;
}

GameModel::IPlayer *GameModel::GameModelModule::chooseCurrentPlayer() const {
    if (whichPlayerIsGoing_ == FIRST_PLAYER_GOES) {
        return firstPlayer_;
    } else if (whichPlayerIsGoing_ == SECOND_PLAYER_GOES) {
        return secondPlayer_;
    } else {
        throw std::runtime_error("Undefined behaviour!");
    }
}


GameModel::IPlayer *GameModel::GameModelModule::chooseEnemyPlayer() const {
    if (whichPlayerIsGoing_ == FIRST_PLAYER_GOES) {
        return secondPlayer_;
    } else if (whichPlayerIsGoing_ == SECOND_PLAYER_GOES) {
        return firstPlayer_;
    } else {
        throw std::runtime_error("Undefined behaviour!");
    }
}

void GameModel::GameModelModule::makePlayersTankMoving(const TankBattle::CellCoordinates directionCoordinates,
                                                       const size_t chosenObjectTypeIndex) {
    auto currentTankCoordinates = chooseCurrentPlayer()->getTank(
            chosenObjectTypeIndex)->getPositionCell().getCellCoordinates();
    if (currentTankCoordinates == chooseEnemyPlayer()->getPlayersPlate()->getPositionCell().getCellCoordinates() &&
        currentTankCoordinates != directionCoordinates) {
        chooseEnemyPlayer()->getPlayersPlate()->resetCapture();
    }

    chooseCurrentPlayer()->getTank(chosenObjectTypeIndex)->makeMove(directionCoordinates);

    if (chooseEnemyPlayer()->getPlayersPlate()->getPositionCell().getCellCoordinates() == directionCoordinates) {
        chooseEnemyPlayer()->getPlayersPlate()->startCapture();
    }
    notifyObservers();
}

void GameModel::GameModelModule::makePlayersTankShooting(const TankBattle::CellCoordinates directionCoordinates,
                                                         const size_t chosenObjectTypeIndex) {
    bool isThereEnemyTank = false;
    IPlayer *enemyPlayer = chooseEnemyPlayer();
    size_t shootingEnemyTankIndex;
    for (unsigned int i = 0; i < enemyPlayer->getAliveTanksCounter(); i++) {
        if (enemyPlayer->getTank(i)->getPositionCell().getCellCoordinates() == directionCoordinates) {
            isThereEnemyTank = true;
            shootingEnemyTankIndex = i;
        }
    }
    if (!isThereEnemyTank) {
        notifyObservers();
        return;
    }
    bool isEnemyTankWasKilled = chooseCurrentPlayer()->getTank(chosenObjectTypeIndex)->makeShot(
            enemyPlayer->getTank(shootingEnemyTankIndex));
    if (isEnemyTankWasKilled) {
        enemyPlayer->deleteTank(shootingEnemyTankIndex);
        if (enemyPlayer->getAliveTanksCounter() == 0) {
            chooseCurrentPlayer()->setStatus(GameModel::PlayerStatus::Won);
        }
    }
    notifyObservers();
}

void GameModel::GameModelModule::makeAction(const std::string &action,
                                            const TankBattle::CellCoordinates directionCoordinates,
                                            const size_t chosenObjectTypeIndex) {
    if (chooseEnemyPlayer()->getPlayersPlate()->isPlateCapturing()) {
        chooseEnemyPlayer()->getPlayersPlate()->increaseTimer();
    }

    if (action == TankBattle::SHOT_STEP) {
        makePlayersTankShooting(directionCoordinates, chosenObjectTypeIndex);
    } else if (action == TankBattle::MOVE_STEP) {
        makePlayersTankMoving(directionCoordinates, chosenObjectTypeIndex);
    } else {
        throw std::runtime_error("Undefined action!");
    }

    if (chooseEnemyPlayer()->getPlayersPlate()->isPlateCaptured()) {
        chooseCurrentPlayer()->setStatus(GameModel::PlayerStatus::Won);
    }

}

void GameModel::GameModelModule::changePlayersStep() {
    if (whichPlayerIsGoing_ == FIRST_PLAYER_GOES) {
        whichPlayerIsGoing_ = SECOND_PLAYER_GOES;
    } else {
        whichPlayerIsGoing_ = FIRST_PLAYER_GOES;
    }
}

GameModel::IPlayer *GameModel::GameModelModule::getFirstPlayer() const {
    return firstPlayer_;
}

GameModel::IPlayer *GameModel::GameModelModule::getSecondPlayer() const {
    return secondPlayer_;
}

bool GameModel::GameModelModule::whichPlayerIsGoing() const {
    return whichPlayerIsGoing_;
}

bool GameModel::GameModelModule::isSecondPlayerBot() const {
    return isSecondPlayerBot_;
}

TankBattle::CellCoordinates GameModel::GameModelModule::getBotsTanksCoordinates(size_t &chosenObjectTypeIndex) const {
    auto generated = ((unsigned int) rand()) % chooseCurrentPlayer()->getAliveTanksCounter();
    chosenObjectTypeIndex = generated;
    return chooseCurrentPlayer()->getTank(generated)->getPositionCell().getCellCoordinates();
}

std::string GameModel::GameModelModule::getBotsAction(TankBattle::CellCoordinates coordinates) const {
    bool isReachablePlayerTank = false;
    for (unsigned int i = 0; i < chooseEnemyPlayer()->getAliveTanksCounter(); i++) {
        auto currentEnemyTank = chooseEnemyPlayer()->getTank(i);
        if (abs((int) currentEnemyTank->getPositionCell().getCellCoordinates().getX() - (int) coordinates.getX()) <=
            currentEnemyTank->getShotRadius() &&
            abs((int) currentEnemyTank->getPositionCell().getCellCoordinates().getY() - (int) coordinates.getY()) <=
            currentEnemyTank->getShotRadius()) {
            isReachablePlayerTank = true;
            break;
        }
    }
    return isReachablePlayerTank ? TankBattle::SHOT_STEP : TankBattle::MOVE_STEP;
}

TankBattle::CellCoordinates GameModel::GameModelModule::getBotsStepCoordinates(TankBattle::CellCoordinates coordinates,
                                                                               const size_t chosenObjectTypeIndex,
                                                                               const std::string &action) const {
    if (action == TankBattle::SHOT_STEP) {
        for (unsigned int i = 0; i < chooseEnemyPlayer()->getAliveTanksCounter(); i++) {
            auto currentEnemyTank = chooseEnemyPlayer()->getTank(i);
            if (abs((int) currentEnemyTank->getPositionCell().getCellCoordinates().getX() -
                    (int) coordinates.getX()) <= currentEnemyTank->getShotRadius() &&
                abs((int) currentEnemyTank->getPositionCell().getCellCoordinates().getY() -
                    (int) coordinates.getY()) <= currentEnemyTank->getShotRadius()) {
                return currentEnemyTank->getPositionCell().getCellCoordinates();
            }
        }
    }
    unsigned int randX, randY;
    while (true) {
        randX = (unsigned int) rand() % TankBattle::FIELD_HEIGHT;
        randY = (unsigned int) rand() % TankBattle::FIELD_WIDTH;
        if (abs((int) randX - (int) coordinates.getX()) <=
            chooseCurrentPlayer()->getTank(chosenObjectTypeIndex)->getMoveRadius() &&
            abs((int) randY - (int) coordinates.getY()) <=
            chooseCurrentPlayer()->getTank(chosenObjectTypeIndex)->getMoveRadius()) {
            break;
        }
    }
    TankBattle::CellCoordinates generatedCoordinates{};
    generatedCoordinates.setX(randX);
    generatedCoordinates.setY(randY);
    return generatedCoordinates;
}

