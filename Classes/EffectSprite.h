//
//  EffectSprite.h
//  JumpEdt
//
//  Created by Yanxing Wang on 11/4/14.
//
//

#ifndef __JumpEdt__EffectSprite__
#define __JumpEdt__EffectSprite__

#include "cocos2d.h"

USING_NS_CC;

class Effect;

class EffectSprite : public Sprite {
public:
  static EffectSprite *create(const std::string &filename);

  static EffectSprite *create();

  void setEffect(Effect *effect);

  void addEffect(Effect *effect, ssize_t order);

  void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

protected:
  EffectSprite();

  ~EffectSprite();

  std::vector <std::tuple<ssize_t, Effect *, QuadCommand>> _effects;
  Effect *_defaultEffect;
};

//////////////////////////////////////////////////////////////////////////////////////////

class Effect : public Ref {
public:
  GLProgramState *getGLProgramState() const { return _glprogramstate; }

  virtual void setTarget(EffectSprite *sprite) { }

protected:
  bool initGLProgramState(const std::string &fragmentFilename);

  Effect();

  virtual ~Effect();

  GLProgramState *_glprogramstate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  std::string _fragSource;
  EventListenerCustom *_backgroundListener;
#endif
};

// Blur
class EffectBlur : public Effect {
public:
  CREATE_FUNC(EffectBlur);

  virtual void setTarget(EffectSprite *sprite) override;

  void setBlurRadius(float radius);

  void setBlurSampleNum(float num);

protected:
  bool init(float blurRadius = 10.0f, float sampleNum = 5.0f);

  float _blurRadius;
  float _blurSampleNum;
};

// Outline
class EffectOutline : public Effect {
public:
  CREATE_FUNC(EffectOutline);

  bool init() {
    initGLProgramState("shaders/outline.fsh");

    Vec3 color(1.0f, 0.2f, 0.3f);
    GLfloat radius = 0.01f;
    GLfloat threshold = 1.75;

    _glprogramstate->setUniformVec3("u_outlineColor", color);
    _glprogramstate->setUniformFloat("u_radius", radius);
    _glprogramstate->setUniformFloat("u_threshold", threshold);
    return true;
  }
};

// Noise
class EffectNoise : public Effect {
public:
  CREATE_FUNC(EffectNoise);

protected:
  bool init() {
    initGLProgramState("shaders/noisy.fsh");
    return true;
  }

  virtual void setTarget(EffectSprite *sprite) override {
    auto s = sprite->getTexture()->getContentSizeInPixels();
    getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
  }
};

// bloom
class EffectBloom : public Effect {
public:
  CREATE_FUNC(EffectBloom);

protected:
  bool init() {
    initGLProgramState("shaders/bloom.fsh");
    return true;
  }

  virtual void setTarget(EffectSprite *sprite) override {
    auto s = sprite->getTexture()->getContentSizeInPixels();
    getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
  }
};

// Cel shading
class EffectCelShading : public Effect {
public:
  CREATE_FUNC(EffectCelShading);

protected:
  bool init() {
    initGLProgramState("shaders/celShading.fsh");
    return true;
  }

  virtual void setTarget(EffectSprite *sprite) override {
    auto s = sprite->getTexture()->getContentSizeInPixels();
    getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
  }
};


#endif /* defined(__JumpEdt__EffectSprite__) */
