//
// Created by user on 03.12.2020.
//

#pragma once

#include "IObserver.h"
#include "../GameModel/GameModelModule.h"

namespace GameView {

    class GameViewModule : public IObserver {
    public:
        explicit GameViewModule(GameModel::GameModelModule &gameModel);

        void removeThisFromObserversList();

        void update() override;

    private:
        GameModel::GameModelModule &gameModel_;
    };

}

