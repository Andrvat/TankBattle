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

        explicit ITank(GameModel::Cell positionCell) : positionCell_(positionCell) {}

        virtual ~ITank() = default;

        void makeMove(const TankBattle::CellCoordinates directionCoordinates) {
            positionCell_.setCellCoordinates(directionCoordinates.getX(), directionCoordinates.getY());
        };

        bool makeShot(ITank *enemyTank) const {
            enemyTank->setHp(enemyTank->getHp() - (int) this->getShotPower());
            return enemyTank->getHp() <= 0;
        };

        [[nodiscard]] bool isAlive() const {
            return aliveStatus_;
        }

        GameModel::Cell getPositionCell() {
            return positionCell_;
        }

        [[nodiscard]] std::string getTankCode() const {
            return tankCode_;
        }

        [[nodiscard]] unsigned int getMoveRadius() const {
            return moveRadius_;
        }

        [[nodiscard]] unsigned int getShotRadius() const {
            return shotRadius_;
        }

        [[nodiscard]] int getHp() const {
            return hp_;
        }

        void setHp(int hp) {
            hp_ = hp;
        }

        [[nodiscard]] unsigned int getShotPower() const {
            return shotPower_;
        }

    protected:
        bool aliveStatus_{};

        unsigned int moveRadius_{};

        unsigned int shotRadius_{};
        unsigned int shotPower_{};

        int hp_{};

        std::string tankCode_;

        GameModel::Cell positionCell_;
    };

}
