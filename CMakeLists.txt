cmake_minimum_required(VERSION 3.17)
project(TankBattle)

set(CMAKE_CXX_STANDARD 17)

add_executable(TankBattle main.cpp GameModel/Cell.cpp GameModel/Cell.h GameModel/GameFieldObjects/ITank.h GameModel/GameFieldObjects/LightTank.h GameModel/GameFieldObjects/MediumTank.h GameModel/GameFieldObjects/HeavyTank.h GlobalParams.h GameModel/GameFieldObjects/HeavyTank.cpp GameModel/GameFieldObjects/LightTank.cpp GameModel/GameFieldObjects/MediumTank.cpp GameModel/GameFieldObjects/Plate.cpp GameModel/GameFieldObjects/Plate.h GameModel/IPlayer.h GameModel/HumanPlayer.cpp GameModel/HumanPlayer.h GameModel/BotPlayer.cpp GameModel/BotPlayer.h GameModel/IPublisher.h GameView/IObserver.h GameModel/GameModelModule.cpp GameModel/GameModelModule.h GameView/GameViewModule.cpp GameView/GameViewModule.h TankBattleLauncher.cpp TankBattleLauncher.h GameController/GameControllerModule.cpp GameController/GameControllerModule.h GameModel/Board.cpp GameModel/Board.h CellCoordinates.h)