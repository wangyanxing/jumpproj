//
//  DeathRotatorRenderer.cpp
//  jumpproj
//
//  Created by Yanxing Wang on 1/15/16.
//
//

#include "DeathRotatorRenderer.h"
#include "SpriteUV.h"
#include "GameUtils.h"

USING_NS_CC;

DeathRotatorRenderer::DeathRotatorRenderer(GameObject *parent) : SimpleRenderer(parent) {
}

DeathRotatorRenderer::~DeathRotatorRenderer() {
#if EDITOR_MODE
  mChild->removeFromParent();
#endif
}

GameRenderer *DeathRotatorRenderer::init(Parameter& param) {
  Size size = param.get<Size>(PARAM_SIZE);
  Vec2 pos = param.get<Vec2>(PARAM_POS);
  mChild = GameUtils::createRect(size, pos);
  
  return SimpleRenderer::init(param);
}

void DeathRotatorRenderer::addToParent(cocos2d::Node* parent, int zorder) {
  GameRenderer::addToParent(parent, zorder);
  parent->addChild(mChild, zorder);
}

void DeathRotatorRenderer::setPosition(const cocos2d::Vec2& pos) {
  GameRenderer::setPosition(pos);
  mChild->setPosition(pos);
}

void DeathRotatorRenderer::setRotation(float val) {
  GameRenderer::setRotation(val);
  mChild->setRotation(45 - val);
}

void DeathRotatorRenderer::setScale(float x, float y) {
  GameRenderer::setScale(x, y);
  mChild->setScale(x, y);
}

void DeathRotatorRenderer::setColor(const cocos2d::Color3B& color) {
  GameRenderer::setColor(color);
  mChild->setColor(color);
}

void DeathRotatorRenderer::setRotationSpeed(int speed) {
  mRotationSpeed = speed;
}

int DeathRotatorRenderer::getRotationSpeed() {
  return mRotationSpeed;
}

void DeathRotatorRenderer::update(float dt) {
  SimpleRenderer::update(dt);

  if (mRotationSpeed > 0) {
    auto rotation = getRotation();
    rotation += mRotationSpeed * dt;
    if (rotation > 360) {
      rotation -= 360;
    }
    setRotation(rotation);
  }
}
