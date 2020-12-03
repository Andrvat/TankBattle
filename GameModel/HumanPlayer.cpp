//
// Created by user on 03.12.2020.
//

#include "HumanPlayer.h"

GameModel::HumanPlayer::HumanPlayer() {
    status_ = PlayerStatus::InProgress;
    type_ = PlayerType::Human;
    name_ = "Human player";
}

GameModel::HumanPlayer::HumanPlayer(const std::string &name) {
    status_ = PlayerStatus::InProgress;
    type_ = PlayerType::Human;
    name_ = name;
}
