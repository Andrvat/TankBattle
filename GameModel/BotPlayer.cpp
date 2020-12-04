//
// Created by user on 03.12.2020.
//

#include "BotPlayer.h"

GameModel::BotPlayer::BotPlayer() {
    status_ = PlayerStatus::InProgress;
    type_ = PlayerType::Bot;
    name_ = "Bot player";
}

void GameModel::BotPlayer::makeMove() {

}
