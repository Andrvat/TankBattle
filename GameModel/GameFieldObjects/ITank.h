//
// Created by andrew on 18.11.2020.
//

#pragma once

#include <string>

#include "../../GlobalParams.h"

namespace GameModel {

    class ITank {
    public:
        virtual ~ITank() = default;

        virtual void makeMove() = 0;

        virtual void makeShot() = 0;

    protected:

        unsigned int moveRadius_;

        unsigned int shotRadius_;
        unsigned int shotPower_;

        unsigned int hp_;

        std::string tankCode_;
    };

}
