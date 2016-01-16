//
//  SimpleRenderer.cpp
//  jumpproj
//
//  Created by Yanxing Wang on 1/13/16.
//
//

#include "SimpleRenderer.h"
#include "SpriteUV.h"
#include "Defines.h"
#include "GameUtils.h"

USING_NS_CC;

SimpleRenderer::SimpleRenderer(GameObject *parent) : GameRenderer(parent) {
}

SimpleRenderer::~SimpleRenderer() {
#if EDITOR_MODE
  mSprite->removeFromParent();
#endif
}

GameRenderer *SimpleRenderer::init(Parameter &param) {
  Size size = param.get<Size>(PARAM_SIZE);
  Vec2 pos = param.get<Vec2>(PARAM_POS);
  int color = param.get<int>(PARAM_COLOR_INDEX, DEFAULT_COLOR_ID);
  std::string image = param.get<std::string>(PARAM_IMAGE, "");

  mSprite = GameUtils::createRect(size, pos);
  setColorIndex(color);
  setTexture(image);
  return this;
}

void SimpleRenderer::setTexture(const std::string& texName) {
  if (texName.empty()) {
    return;
  }
  mTextureName = texName;
  Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(texName);
  mSprite->setTexture(texture);
}

cocos2d::Node* SimpleRenderer::getNode() {
  return mSprite;
}

cocos2d::Node* SimpleRenderer::getNode() const {
  return mSprite;
}
