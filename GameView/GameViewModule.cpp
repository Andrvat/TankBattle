//
// Created by user on 03.12.2020.
//

#include "GameViewModule.h"

GameView::GameViewModule::GameViewModule(GameModel::GameModelModule &gameModel) : gameModel_(gameModel) {
    this->gameModel_.attachObserver(this);
}

void GameView::GameViewModule::removeThisFromObserversList() {
    this->gameModel_.detachObserver(this);
}

void GameView::GameViewModule::update() {
    // TODO: Something is happening while we call update. But what??? Nobody knows...
}
