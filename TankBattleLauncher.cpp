//
// Created by user on 03.12.2020.
//

#include "TankBattleLauncher.h"
#include "GameView/GameViewModule.h"
#include "GameModel/GameModelModule.h"
#include "GameController/GameControllerModule.h"


void TankBattle::TankBattleLauncher::startGame() {
    GameModel::GameModelModule model;

    // subscribe to model
    GameView::GameViewModule view(model);

    GameController::GameControllerModule controller;

    model.launchGameModel(&controller);
    model.placeGameFieldObjects();
    model.setFirstPlayerStep();

    while (!model.isSomebodyWon()) {
        TankBattle::CellCoordinates stepCellCoordinates = controller.getStepCoordinates();
        size_t chosenObjectTypeIndex;
        bool playerChoosingStatus = false;
        while (!playerChoosingStatus) {
            if (!model.isCellCoordinatesAvailableForCurrentPlayerChoice(stepCellCoordinates, chosenObjectTypeIndex)) {
                view.update();
                continue;
            }
            playerChoosingStatus = true;
        }

        bool isAvailableAction = false;
        std::string stepAction;
        while (!isAvailableAction) {
            stepAction = controller.getStepAction();
            if (!GameModel::GameModelModule::isAction(stepAction)) {
                view.update();
                isAvailableAction = true;
            }
        }

        // TODO: check coordinate's borders in getStepCoordinates method
        stepCellCoordinates = controller.getStepCoordinates();
        playerChoosingStatus = false;
        while (!playerChoosingStatus) {
            if (!model.isCellCoordinatesAvailableForMakeStep(stepCellCoordinates, chosenObjectTypeIndex, stepAction)) {
                view.update();
            }
            playerChoosingStatus = true;
        }

        model.makeAction(stepAction, stepCellCoordinates, chosenObjectTypeIndex);
        if (model.isSomebodyWon()) {
            break;
        }

    }

}
