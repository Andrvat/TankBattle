//
// Created by user on 03.12.2020.
//

#pragma once

#include "../GameView/IObserver.h"

namespace GameModel {

    class IPublisher {
    public:
        virtual ~IPublisher() = default;

        virtual void attach(GameView::IObserver *observer) = 0;

        virtual void detach(GameView::IObserver *observer) = 0;

        virtual void notify() = 0;

    };

}


