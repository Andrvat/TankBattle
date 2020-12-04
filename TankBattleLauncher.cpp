//
// Created by user on 03.12.2020.
//

#include "TankBattleLauncher.h"
#include "GameView/GameViewModule.h"
#include "GameModel/GameModelModule.h"
#include "GameController/GameControllerModule.h"


void TankBattle::TankBattleLauncher::startGame() {
    GameModel::GameModelModule model;
    GameView::GameViewModule view(model);
    GameController::GameControllerModule controller;

    model.launchGameModel(&controller);
    model.placeGameFieldObjects();
    model.setFirstPlayerStep();

    while (!model.isSomebodyWon()) {
        TankBattle::CellCoordinates stepCellCoordinates = controller.getStepCoordinates();
        if (!model.isCellCoordinatesAvailableForCurrentPlayer(stepCellCoordinates)) {
            view.update();
            continue;
        }

        bool isAvailableAction = false;
        while (!isAvailableAction) {
            std::string stepAction = controller.getStepAction();
            if (!GameModel::GameModelModule::isAction(stepAction)) {
                view.update();
                isAvailableAction = true;
            }
        }




    }

}
