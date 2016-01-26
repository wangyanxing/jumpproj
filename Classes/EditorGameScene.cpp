//
//  EditorGameScene.cpp
//  jumpproj
//
//  Created by Yanxing Wang on 1/15/16.
//
//

#include "EditorGameScene.h"
#include "GameLevel.h"
#include "GameInputs.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "Parameter.h"

#if USE_REFACTOR

USING_NS_CC;

EditorGameScene::EditorGameScene() {
}

EditorGameScene::~EditorGameScene() {
}

bool EditorGameScene::init() {
  GameLayerContainer::init();
  GameLevel::instance().setGameLayer(this);

  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyPressed = CC_CALLBACK_2(EditorGameScene::keyPressed, this);
  keyboardListener->onKeyReleased = CC_CALLBACK_2(EditorGameScene::keyReleased, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

  GameInputs::instance().addKeyboardEvent(EventKeyboard::KeyCode::KEY_SPACE,
                                          [&](GameInputs::KeyCode key) {
      GameLevel::instance().getHero()->runCommand(COMMAND_INPUT, {{PARAM_INPUT, Any(INPUT_JUMP)}});
  });
  
  // Register editor commands.
  registerCommands();

  // Test.
  GameLevel::instance().load("maps/local/test_refactor1.json");
  return true;
}

void EditorGameScene::onEnter() {
  GameLayerContainer::onEnter();
}

void EditorGameScene::update(float dt) {
  processInput();
  GameLayerContainer::update(dt);
}

void EditorGameScene::postUpdate(float dt) {
  GameLayerContainer::postUpdate(dt);
}

void EditorGameScene::processInput() {
  auto &gameInputs = GameInputs::instance();
  auto hero = GameLevel::instance().getHero();

  if (gameInputs.isPressing(EventKeyboard::KeyCode::KEY_A)) {
    hero->runCommand(COMMAND_INPUT, {{PARAM_INPUT, Any(INPUT_LEFT)}});
  } else if (gameInputs.isPressing(EventKeyboard::KeyCode::KEY_D)) {
    hero->runCommand(COMMAND_INPUT, {{PARAM_INPUT, Any(INPUT_RIGHT)}});
  }
}

void EditorGameScene::registerCommands() {
  auto &gameInputs = GameInputs::instance();
  
  // Enter or leave game mode.
  gameInputs.addKeyboardEvent(EventKeyboard::KeyCode::KEY_L, [this](GameInputs::KeyCode key) {
      GameLevel::instance().enableGame(!GameLevel::instance().isGameEnabled());
  });
  
  // Show helpers.
  gameInputs.addKeyboardEvent(EventKeyboard::KeyCode::KEY_G, [this](GameInputs::KeyCode key) {
      auto physicsMgr = GameLevel::instance().getPhysicsManager();
      physicsMgr->setPhysicsDebugDraw(!physicsMgr->getPhysicsDebugDraw());
  });
}

void EditorGameScene::clean() {
  GameLayerContainer::clean();
  GameLevel::instance().unload();
}

void EditorGameScene::onWinGame() {
}

void EditorGameScene::keyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
  GameInputs::instance().keyPressed(keyCode, event);
}

void EditorGameScene::keyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
  GameInputs::instance().keyReleased(keyCode, event);
}

#endif
