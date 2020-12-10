//
// Created by user on 03.12.2020.
//

#pragma once

#include <iostream>

#include "IObserver.h"
#include "../GameModel/GameModelModule.h"
#include "../GlobalParams.h"

namespace GameView {

    class GameViewModule : public IObserver {
    public:
        explicit GameViewModule(GameModel::GameModelModule &gameModel);

        [[maybe_unused]] void removeThisFromObserversList();

        void update() override;

        void initFieldMap();

        void printFieldMapInConsole() const;

        static void printStartMessage();

        static void askCoordinates();

        static void askPlayersName(bool playerNumber);

        static void askPlayersNumber();

        void printWhatPlayerIsGoing();

        static void printAboutUnreachableCoordinates();

        static void printAboutInvalidAction();

        static void askCoordinates(const std::string &forWhichAction);

        void printAboutTheWinner() const;

        static void printInfoAboutNegativeCoordinates();

        static void printBotStepMessage(const std::string &botMessage);

        static void askAction();

    private:
        GameModel::GameModelModule &gameModel_;
        std::vector<std::string> fieldMap_;
    };

}

