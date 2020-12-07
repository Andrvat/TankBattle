//
// Created by user on 03.12.2020.
//

#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include "GameFieldObjects/ITank.h"
#include "GameFieldObjects/Plate.h"
#include "../GlobalParams.h"

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

        void addNewTank(GameModel::ITank *tank) {
            if (playersTanks_.size() >= TankBattle::TANKS_BY_PLAYER_COUNT) {
                throw std::logic_error("You are trying to add a new tank when the limit is already reached!");
            }
            playersTanks_.push_back(tank);
        }

        void addNewPlate(GameModel::Plate *plate) {
            playersPlate_ = plate;
        }

        [[nodiscard]] size_t getAliveTanksCounter() const {
            return aliveTanksCounter_;
        }

        void setAliveTanksCounter(size_t aliveTanksCounter) {
            aliveTanksCounter_ = aliveTanksCounter;
        }

        GameModel::ITank *getTank(const unsigned int tankNumber) {
            if (tankNumber >= playersTanks_.size()) {
                throw std::runtime_error("SOMETHING GOES WRONG!");
            }
            return playersTanks_[tankNumber];
        };

        void deleteTank(const size_t tank) {
            std::swap(playersTanks_[tank], playersTanks_.back());
            delete playersTanks_[playersTanks_.size() - 1];
            playersTanks_.pop_back();
            --aliveTanksCounter_;
        }

        [[nodiscard]] Plate *getPlayersPlate() {
            return playersPlate_;
        }

    protected:
        PlayerStatus status_;
        PlayerType type_;

        std::string name_;

        std::vector<GameModel::ITank *> playersTanks_;
        GameModel::Plate *playersPlate_;

        size_t aliveTanksCounter_;

    };
}
