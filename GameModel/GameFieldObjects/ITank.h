//
// Created by andrew on 18.11.2020.
//

#pragma once

#include <string>

#include "../../GlobalParams.h"
#include "../Cell.h"


namespace GameModel {

    class ITank {
    public:

        explicit ITank(GameModel::Cell &positionCell) : positionCell_(positionCell) {}

        virtual ~ITank() = default;

        virtual void makeMove() = 0;

        virtual void makeShot() = 0;

        [[nodiscard]] bool isAlive() const {
            return aliveStatus_;
        }

        GameModel::Cell getPositionCell() {
            return positionCell_;
        }

    protected:
        bool aliveStatus_{};

        unsigned int moveRadius_{};

        unsigned int shotRadius_{};
        unsigned int shotPower_{};

        unsigned int hp_{};

        std::string tankCode_;

        GameModel::Cell &positionCell_;
    };

}
