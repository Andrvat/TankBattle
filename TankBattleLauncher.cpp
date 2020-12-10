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

    GameView::GameViewModule::printStartMessage();
    GameView::GameViewModule::askPlayersNumber();
    model.launchGameModel(&controller);
    model.placeGameFieldObjects();
    model.setFirstPlayerStep();


    while (!model.isSomebodyWon()) {
        view.printWhatPlayerIsGoing();
        size_t chosenObjectTypeIndex;
        TankBattle::CellCoordinates stepCellCoordinates{};
        bool playerChoosingStatus = false;
        while (!playerChoosingStatus) {
            GameView::GameViewModule::askCoordinates();
            stepCellCoordinates = controller.getStepCoordinates();
            if (!model.isCellCoordinatesAvailableForCurrentPlayerChoice(stepCellCoordinates, chosenObjectTypeIndex)) {
                GameView::GameViewModule::printAboutUnreachableCoordinates();
                continue;
            }
            playerChoosingStatus = true;
        }

        bool isAvailableAction = false;
        std::string stepAction;
        while (!isAvailableAction) {
            GameView::GameViewModule::askAction();
            stepAction = controller.getStepAction();
            if (!GameModel::GameModelModule::isAction(stepAction)) {
                GameView::GameViewModule::printAboutInvalidAction();
                continue;
            }
            isAvailableAction = true;
        }

        playerChoosingStatus = false;
        while (!playerChoosingStatus) {
            GameView::GameViewModule::askCoordinates(stepAction);
            stepCellCoordinates = controller.getStepCoordinates();
            if (!model.isCellCoordinatesAvailableForMakeStep(stepCellCoordinates, chosenObjectTypeIndex, stepAction)) {
                GameView::GameViewModule::printAboutUnreachableCoordinates();
                continue;
            }
            playerChoosingStatus = true;
        }

        model.makeAction(stepAction, stepCellCoordinates, chosenObjectTypeIndex);
        if (model.isSomebodyWon()) {
            view.printAboutTheWinner();
            break;
        }

        model.changePlayersStep();
    }

}
