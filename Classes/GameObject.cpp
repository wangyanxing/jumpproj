//
//  GameObject.cpp
//  jumpproj
//
//  Created by Yanxing Wang on 1/12/16.
//
//

#include "GameObject.h"
#include "GameRenderer.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "SimpleRenderer.h"
#include "DeathRenderer.h"
#include "DeathRotatorRenderer.h"

USING_NS_CC;

GameObject::GameObject() {
}

GameObject::~GameObject() {
  release();
}

void GameObject::addComponandCommand(ComponentCommand command, GameComponent *component) {
  mComponentCommands[command] = component;
}

void GameObject::removeComponandCommand(ComponentCommand command) {
  CC_ASSERT(mComponentCommands.count(command));
  mComponentCommands.erase(command);
}

void GameObject::runCommand(ComponentCommand command, const Parameter &param) {
  auto it = mComponentCommands.find(command);
  if (it == mComponentCommands.end()) {
    CCLOGERROR("Cannot find the command!");
    return;
  }
  it->second->runCommand(command, param);
}

GameRenderer *GameObject::setRenderer(RendererType renderType) {
  GameRenderer *renderer = nullptr;
  switch (renderType) {
    case RENDERER_RECT:
      renderer = new SimpleRenderer(this);
      break;
    case RENDERER_DEATH:
      renderer = new DeathRenderer(this);
      break;
    case RENDERER_DEATH_CIRCLE:
      renderer = new DeathRotatorRenderer(this);
      break;
    default:
      CCLOGWARN("Invalid renderer type!");
  }
  return setRenderer(renderer);
}

GameRenderer *GameObject::setRenderer(GameRenderer *renderer) {
  CC_SAFE_DELETE(mRenderer);
  mRenderer = renderer;
  return mRenderer;
}

void GameObject::update(float dt) {
  if (mRenderer) {
    mRenderer->update(dt);
  }

  for (auto component : mComponents) {
    component.second->update(dt);
  }
}

void GameObject::postUpdate(float dt) {
  for (auto component : mComponents) {
    component.second->postUpdate(dt);
  }
}

GameComponent* GameObject::getComponent(ComponentType type) {
  auto it = mComponents.find(type);
  return it == mComponents.end() ? nullptr : it->second;
}

GameComponent* GameObject::addComponent(ComponentType type) {
  auto component = getComponent(type);
  CC_SAFE_DELETE(component);

  switch (type) {
    case COMPONENT_PHYSICS:
      component = new PhysicsComponent(this);
      break;
    case COMPONENT_INPUT:
      component = new InputComponent(this);
      break;
    case COMPONENT_PATH:
    case COMPONENT_BUTTON:
    case COMPONENT_ROTATOR:
    default:
      CCLOGERROR("Invalid component type");
  }
  mComponents[type] = component;
  return component;
}

void GameObject::removeComponent(ComponentType type) {
  auto it = mComponents.find(type);
  if (it != mComponents.end()) {
    CC_SAFE_DELETE(it->second);
    mComponents.erase(it);
  }
}

bool GameObject::hasComponent(ComponentType type) {
  return mComponents.find(type) != mComponents.end();
}

void GameObject::release() {
  CC_SAFE_DELETE(mRenderer);

  for (auto &component : mComponents) {
    CC_SAFE_DELETE(component.second);
  }
  mComponents.clear();
}

void GameObject::traverseComponents(std::function<void(GameComponent*)> func) {
  for (auto comp : mComponents) {
    func(comp.second);
  }
}
