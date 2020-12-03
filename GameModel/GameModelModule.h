//
// Created by user on 03.12.2020.
//

#pragma once

#include <list>
#include "IPublisher.h"
#include "../GameView/IObserver.h"

namespace GameModel {

    /**
     * @brief
     * Facade of access to the complex system "Game Model"
     */

    class GameModelModule : public IPublisher {
    private:
        std::list<GameView::IObserver *> observersList_;
    public:
        void attach(GameView::IObserver *observer) override;

        void detach(GameView::IObserver *observer) override;

        void notify() override;

        [[nodiscard]] size_t getObserversListSize() const;
    };

}

