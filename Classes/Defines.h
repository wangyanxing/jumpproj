//
//  Defines.h
//  JumpEdt
//
//  Created by Yanxing Wang on 10/18/14.
//
//

#ifndef __JumpEdt__Defines__
#define __JumpEdt__Defines__

#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#   define EDITOR_MODE 1
#else
#   define EDITOR_MODE 0
#endif

#define EDITOR_IPAD_MODE 1
#define EDITOR_IP5_MODE  2
#define EDITOR_IP4_MODE  3

#define EDITOR_RATIO EDITOR_IP5_MODE

#define GLOW_NODE_TAG 2000

#define ORG_RECT_SIZE 8.0

#define GRAVITY_VAL -1100
#define JUMP_VOL 450

enum BlockKind {
  KIND_HERO = 0,
  KIND_BLOCK,
  KIND_DEATH,
  KIND_DEATH_CIRCLE,
  KIND_BUTTON,
  KIND_PUSHABLE,
  KIND_FORCEFIELD,

  KIND_MAX
};

enum FollowMode {
  F_CENTER,
  F_UP, F_DOWN, F_LEFT, F_RIGHT
};

#define UI_LAYER_HIGHT 100

#define ZORDER_SHADOW_1 2
#define ZORDER_SHADOW_2 3

#define USE_SHADER_LAYER 0
#define USE_SHADOW 1

#define BORDER_BLOCK_LEFT 3
#define BORDER_BLOCK_RIGHT 4
#define BORDER_BLOCK_TOP 2
#define BORDER_BLOCK_BOTTOM 1
#define BORDER_FRAME_SIZE 10

#define EDT_UI_YBIAS (VisibleRect::getFrameSize().height - UI_LAYER_HIGHT)


// Art resource
#define BLOCK_IMAGE "images/rect.png"
#define DEATH_IMAGE "images/saw.png"
#define DEATH_CIRCLE_IMAGE "images/saw3.png"

#endif /* defined(__JumpEdt__Defines__) */
