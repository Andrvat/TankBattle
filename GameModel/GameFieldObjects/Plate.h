//
// Created by user on 03.12.2020.
//

#pragma once

#include <exception>

#include "../../GlobalParams.h"

#include "../Cell.h"

namespace GameModel {

    class Plate {
    public:
        explicit Plate(GameModel::Cell &positionCell);

        [[nodiscard]] unsigned int getTimer() const;

        void increaseTimer();

        void resetCapture();

        [[nodiscard]] bool isStatus() const;

        void startCapture();

        [[nodiscard]] bool isPlateCaptured() const;

    private:
        unsigned int timer_;
        bool status_;

        GameModel::Cell &positionCell;
    };

}
