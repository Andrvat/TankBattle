//
// Created by user on 03.12.2020.
//

#pragma once

#include "../GameView/IObserver.h"

namespace GameModel {

    class IPublisher {
    public:
        virtual ~IPublisher() = default;

        virtual void attachObserver(GameView::IObserver *observer) = 0;

        virtual void detachObserver(GameView::IObserver *observer) = 0;

        virtual void notifyObservers() = 0;

    };

}


