//
// Created by user on 03.12.2020.
//

#pragma once

#include <list>
#include <memory>
#include <stdexcept>
#include <random>
#include <set>

#include "../GameController/GameControllerModule.h"

#include "../GameView/IObserver.h"
#include "../GlobalParams.h"
#include "../CellCoordinates.h"

#include "GameFieldObjects/LightTank.h"
#include "GameFieldObjects/MediumTank.h"
#include "GameFieldObjects/HeavyTank.h"
#include "GameFieldObjects/Plate.h"

#include "BotPlayer.h"
#include "HumanPlayer.h"
#include "IPublisher.h"
#include "Board.h"
#include "IPlayer.h"

#define FIRST_PLAYER_GOES true
#define SECOND_PLAYER_GOES false

namespace GameModel {

    /**
     * @brief
     * Facade of access to the complex system "Game Model"
     */

    class GameModelModule : public IPublisher {
    private:
        std::list<GameView::IObserver *> observersList_;

        Board modelBoard_;
        IPlayer *firstPlayer_ = nullptr;
        IPlayer *secondPlayer_ = nullptr;

        bool whichPlayerIsGoing_;

        void initPlayersObjects(GameModel::IPlayer *player, unsigned int playerSide);

    public:
        ~GameModelModule() {
            delete firstPlayer_;
            delete secondPlayer_;
        }

        void attachObserver(GameView::IObserver *observer) override;

        void detachObserver(GameView::IObserver *observer) override;

        void notifyObservers() override;

        [[nodiscard]] size_t getObserversListSize() const;

        void launchGameModel(GameController::GameControllerModule *controller);

        void placeGameFieldObjects();

        [[nodiscard]] bool isSomebodyWon() const;

        void setFirstPlayerStep();

        void changePlayersStep();

        [[nodiscard]] bool isCellCoordinatesAvailableForCurrentPlayerChoice(TankBattle::CellCoordinates coordinates,
                                                                            size_t &objectTypeIndex) const;

        static bool isAction(const std::string &action);

        [[nodiscard]] bool isCellCoordinatesAvailableForMakeStep(TankBattle::CellCoordinates coordinates,
                                                                 const size_t &objectTypeIndex,
                                                                 const std::string &action) const;

        [[nodiscard]] IPlayer *chooseCurrentPlayer() const;


        [[nodiscard]] IPlayer *chooseEnemyPlayer() const;

        void makePlayersTankMoving(TankBattle::CellCoordinates directionCoordinates, size_t chosenObjectTypeIndex);

        void makeAction(const std::string &action, TankBattle::CellCoordinates directionCoordinates,
                        size_t chosenObjectTypeIndex);

        void makePlayersTankShooting(TankBattle::CellCoordinates directionCoordinates,
                                     size_t chosenObjectTypeIndex);

        [[nodiscard]] IPlayer *getFirstPlayer() const;

        [[nodiscard]] IPlayer *getSecondPlayer() const;

        [[nodiscard]] bool whichPlayerIsGoing() const;

        [[nodiscard]] std::string getTheWinnersName() const;
    };

}

