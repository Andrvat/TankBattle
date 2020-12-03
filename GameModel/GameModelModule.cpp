//
// Created by user on 03.12.2020.
//

#include "GameModelModule.h"

void GameModel::GameModelModule::attach(GameView::IObserver *observer) {
    observersList_.push_back(observer);
}

void GameModel::GameModelModule::detach(GameView::IObserver *observer) {
    observersList_.remove(observer);
}

void GameModel::GameModelModule::notify() {
    auto iterator = observersList_.begin();
    while (iterator != observersList_.end()) {
        (*iterator)->update();
        ++iterator;
    }
}

size_t GameModel::GameModelModule::getObserversListSize() const {
    return observersList_.size();
}
