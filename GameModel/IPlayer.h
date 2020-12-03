//
// Created by user on 03.12.2020.
//

#pragma once

#include <string>

namespace GameModel {

    enum class PlayerStatus {
        InProgress,
        Won,
        Lost
    };

    enum class PlayerType {
        Human,
        Bot
    };

    class IPlayer {
    public:
        virtual ~IPlayer() = default;

        virtual void makeMove() = 0;

        [[nodiscard]] bool isWon() const {
            return status_ == PlayerStatus::Won;
        };

        [[nodiscard]] bool isLost() const {
            return status_ == PlayerStatus::Lost;
        };

        [[nodiscard]] bool isInProgress() const {
            return status_ == PlayerStatus::InProgress;
        };

        void setStatus(PlayerStatus status) {
            status_ = status;
        }

        [[nodiscard]] PlayerType getType() const {
            return type_;
        }

        [[nodiscard]] std::string getName() const {
            return name_;
        }

    protected:
        PlayerStatus status_;
        PlayerType type_;

        std::string name_;

    };
}
