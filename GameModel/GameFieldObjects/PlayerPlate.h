//
// Created by user on 03.12.2020.
//

#pragma once

#include "../../GlobalParams.h"
#include <exception>

namespace GameModel {

    class PlayerPlate {
    public:
        PlayerPlate();

        [[nodiscard]] unsigned int getTimer() const;

        void increaseTimer();

        void resetCapture();

        [[nodiscard]] bool isStatus() const;

        void startCapture();

        [[nodiscard]] bool isPlateCaptured() const;

    private:
        unsigned int timer_;
        bool status_;
    };

}
