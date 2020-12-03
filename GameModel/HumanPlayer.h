//
// Created by user on 03.12.2020.
//

#pragma once

#include "IPlayer.h"

namespace GameModel {

    class HumanPlayer : public IPlayer {
    public:
        HumanPlayer();

        explicit HumanPlayer(const std::string &name);
    };

}