//
//  InputComponent.cpp
//  jumpproj
//
//  Created by Yanxing Wang on 1/18/16.
//
//

#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GameObject.h"

InputComponent::InputComponent(GameObject *parent) : GameComponent(parent) {
  mParent->addComponandCommand(COMMAND_INPUT, this);
}

InputComponent::~InputComponent() {
  mParent->removeComponandCommand(COMMAND_INPUT);
}

void InputComponent::runCommand(ComponentCommand type, const Parameter &param) {
  CC_ASSERT(type == COMMAND_INPUT);
  auto input = param.get<InputType>(PARAM_INPUT);
  if (input == INPUT_LEFT) {
    pressLeft();
  } else if (input == INPUT_RIGHT) {
    pressRight();
  } else if (input == INPUT_JUMP) {
    pressJump();
  }
}

void InputComponent::pressLeft() {
  mParent->getComponent<PhysicsComponent>()->setAccelerationX(-DEFAULT_MOVE_ACCEL);
}

void InputComponent::pressRight() {
  mParent->getComponent<PhysicsComponent>()->setAccelerationX(DEFAULT_MOVE_ACCEL);
}

void InputComponent::pressJump() {
  mParent->getComponent<PhysicsComponent>()->setAccelerationY(DEFAULT_JUMP_ACCEL);
}
