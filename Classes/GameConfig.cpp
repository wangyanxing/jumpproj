//
//  GameConfig.cpp
//  jumpproj
//
//  Created by Yanxing Wang on 1/19/16.
//
//

#include "GameConfig.h"
#include "JsonFormat.h"
#include "JsonParser.h"

void GameConfig::load() {
  JsonParser jp(JsonParser::getBuffer("configs/GameConfig.json"));
  auto &json = jp.getCurrentDocument();
  
  HeroSize = json["heroSize"].GetDouble();
  MoveAcceleration = json["moveAcceleration"].GetDouble();
  JumpAcceleration = json["jumpAcceleration"].GetDouble();
  AccelerationResistance = json["accelerationResistance"].GetDouble();
  SawImage = json["sawImage"].GetString();
  SawImageRotation = json["sawImageRotation"].GetString();
  CurtainMoveTime = json["curtainMoveTime"].GetDouble();

  std::string controlKey = "controlPad" + JsonParser::getLevelSuffix();
  auto &controls = json[controlKey.c_str()];
  ControlPadScale = controls["scale"].GetDouble();
  ControlPadLeftButton = controls["leftButton"].GetVec2();
  ControlPadRightButton = controls["rightButton"].GetVec2();
  ControlPadJumpButton = controls["jumpButton"].GetVec2();
}
