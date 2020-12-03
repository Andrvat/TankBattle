//
// Created by user on 03.12.2020.
//

#pragma once

namespace GameView {


    class IObserver {
    public:
        virtual ~IObserver() = default;

        virtual void update() = 0;
    };
}
