//
// Created by user on 03.12.2020.
//

#include "TankBattleLauncher.h"
#include "GameView/GameViewModule.h"


void TankBattle::TankBattleLauncher::startGame() {
    GameModel::GameModelModule model;

    // subscribe to model
    GameView::GameViewModule view(model);

    GameView::GameViewModule::printStartMessage();
    GameView::GameViewModule::askPlayersNumber();
    model.launchGameModel();
    model.placeGameFieldObjects();
    model.setFirstPlayerStep();


    while (!model.isSomebodyWon()) {
        std::string botMessage = "Bot chose cell with coordinates ";
        view.printWhatPlayerIsGoing();
        size_t chosenObjectTypeIndex;
        TankBattle::CellCoordinates stepCellCoordinates{};
        bool playerChoosingStatus = false;
        while (!playerChoosingStatus) {
            if (model.isSecondPlayerBot() && model.whichPlayerIsGoing() == SECOND_PLAYER_GOES) {
                stepCellCoordinates = model.getBotsTanksCoordinates(chosenObjectTypeIndex);
                botMessage += "(" + std::to_string(stepCellCoordinates.getX()) + " " +
                              std::to_string(stepCellCoordinates.getY()) + "), ";
                Sleep(3000);
            } else {
                GameView::GameViewModule::askCoordinates();
                stepCellCoordinates = GameController::GameControllerModule::getStepCoordinates();
            }
            if (!model.isCellCoordinatesAvailableForCurrentPlayerChoice(stepCellCoordinates, chosenObjectTypeIndex)) {
                GameView::GameViewModule::printAboutUnreachableCoordinates();
                continue;
            }
            playerChoosingStatus = true;
        }

        bool isAvailableAction = false;
        std::string stepAction;
        while (!isAvailableAction) {
            if (model.isSecondPlayerBot() && model.whichPlayerIsGoing() == SECOND_PLAYER_GOES) {
                stepAction = model.getBotsAction(stepCellCoordinates);
                botMessage += "make " + stepAction + " and ";
            } else {
                GameView::GameViewModule::askAction();
                stepAction = GameController::GameControllerModule::getStepAction();
                if (!GameModel::GameModelModule::isAction(stepAction)) {
                    GameView::GameViewModule::printAboutInvalidAction();
                    continue;
                }
            }
            isAvailableAction = true;
        }

        playerChoosingStatus = false;
        while (!playerChoosingStatus) {
            if (model.isSecondPlayerBot() && model.whichPlayerIsGoing() == SECOND_PLAYER_GOES) {
                stepCellCoordinates = model.getBotsStepCoordinates(stepCellCoordinates, chosenObjectTypeIndex,
                                                                   stepAction);
                botMessage += "do it to (" + std::to_string(stepCellCoordinates.getX()) + " " +
                              std::to_string(stepCellCoordinates.getY()) + ") cell.";
            } else {
                GameView::GameViewModule::askCoordinates(stepAction);
                stepCellCoordinates = GameController::GameControllerModule::getStepCoordinates();
                if (!model.isCellCoordinatesAvailableForMakeStep(stepCellCoordinates, chosenObjectTypeIndex,
                                                                 stepAction)) {
                    GameView::GameViewModule::printAboutUnreachableCoordinates();
                    continue;
                }
            }
            playerChoosingStatus = true;
        }

        model.makeAction(stepAction, stepCellCoordinates, chosenObjectTypeIndex);
        if (model.isSecondPlayerBot() && model.whichPlayerIsGoing() == SECOND_PLAYER_GOES) {
            GameView::GameViewModule::printBotStepMessage(botMessage);
        }
        if (model.isSomebodyWon()) {
            view.printAboutTheWinner();
            break;
        }

        model.changePlayersStep();
    }

}
