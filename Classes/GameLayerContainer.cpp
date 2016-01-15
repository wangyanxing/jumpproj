//
//  GameLayerContainer.cpp
//  jumpproj
//
//  Created by Yanxing Wang on 1/5/16.
//
//

#include "GameLayerContainer.h"
#include "LogicManager.h"
#include "GameLevel.h"

USING_NS_CC;

#define UPDATE_DT 1.0f / 60.0f

GamePostUpdater::GamePostUpdater(GameLayerContainer *ct): container(ct) {
}

void GamePostUpdater::update(float dt) {
  container->postUpdate(dt);
}

cocos2d::Scene *GameLayerContainer::createPhysicsScene() {
  auto scene = Scene::createWithPhysics();
  scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
  GameLogic::PhysicsWorld = scene->getPhysicsWorld();
  return scene;
}

GameLayerContainer::GameLayerContainer() : mPostUpdater(this) {
}

GameLayerContainer::~GameLayerContainer() {
  getScheduler()->unscheduleAllForTarget(&mPostUpdater);

#if !USE_REFACTOR
  CC_SAFE_DELETE(mGame);
#endif
}

bool GameLayerContainer::init() {
  Layer::init();

  mBlockRoot = Node::create();
  mBlockRoot->setCameraMask((unsigned short) CameraFlag::USER2);
  mCamera = Camera::create();

#if !USE_REFACTOR
  CC_SAFE_DELETE(GameLogic::Game);
  mGame = new GameLogic(this);
  mGame->mWinGameEvent = [this] { onWinGame(); };
#endif

  mCamera->setCameraFlag(CameraFlag::USER2);
  mCamera->setDepth(getCameraDepth());
  addChild(mCamera);
  addChild(mBlockRoot, ZORDER_BLOCK_ROOT);
  setCameraMask((unsigned short) CameraFlag::USER2);
  return true;
}

void GameLayerContainer::onEnter() {
  Layer::onEnter();
  getScheduler()->scheduleUpdate(this, -2, false);
  getScheduler()->scheduleUpdate(&mPostUpdater, 100, false);

#if !USE_REFACTOR
  auto contactListener = EventListenerPhysicsContact::create();
  contactListener->onContactPreSolve = CC_CALLBACK_2(GameLayerContainer::onCollisionDetected, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
#endif
}

bool GameLayerContainer::onCollisionDetected(cocos2d::PhysicsContact &contact,
                                             cocos2d::PhysicsContactPreSolve &solve) {
  return mGame->onContactPreSolve(contact, solve);
}

void GameLayerContainer::update(float dt) {
  GameLevel::instance().update(dt);

#if !USE_REFACTOR
  mGame->update(UPDATE_DT);
  mGame->updateCamera(mCamera);
#endif
}

void GameLayerContainer::postUpdate(float dt) {
#if !USE_REFACTOR
  mGame->postUpdate(UPDATE_DT);
#endif
}

void GameLayerContainer::clean() {
#if !USE_REFACTOR
  mGame->clean();
#endif
}
