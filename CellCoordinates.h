//
// Created by user on 04.12.2020.
//

#pragma once

namespace TankBattle {

    class CellCoordinates {
    private:
        unsigned int x_;
        unsigned int y_;
    public:
        unsigned int getX() const {
            return x_;
        }

        void setX(unsigned int x) {
            CellCoordinates::x_ = x;
        }

        unsigned int getY() const {
            return y_;
        }

        void setY(unsigned int y) {
            CellCoordinates::y_ = y;
        }

        friend bool operator==(const CellCoordinates &left, const CellCoordinates &right);

        friend bool operator!=(const CellCoordinates &left, const CellCoordinates &right);
    };

    inline bool operator==(const CellCoordinates &left, const CellCoordinates &right) {
        return left.x_ == right.x_ && left.y_ == right.y_;
    }

    inline bool operator!=(const CellCoordinates &left, const CellCoordinates &right) {
        return !(left == right);
    }

}

