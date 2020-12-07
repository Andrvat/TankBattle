//
// Created by user on 03.12.2020.
//

#pragma once

#include <exception>

#include "../../GlobalParams.h"

#include "../Cell.h"

namespace GameModel {

    enum class PlateStatus {
        NotCapture,
        Capturing,
        Captured
    };

    class Plate {
    public:
        explicit Plate(GameModel::Cell &positionCell);

        [[nodiscard]] unsigned int getTimer() const;

        void increaseTimer();

        void resetCapture();

        void startCapture();

        [[nodiscard]] bool isPlateCaptured() const;

        [[nodiscard]] bool isPlateCapturing() const;

        [[nodiscard]] Cell getPositionCell() const;

    private:
        unsigned int timer_;
        PlateStatus status_;

        GameModel::Cell positionCell;
    };

}
