//
//  Events.cpp
//  JumpEdt
//
//  Created by Yanxing Wang on 10/18/14.
//
//

#include "Events.h"
#include "EditorScene.h"
#include "LogicManager.h"
#include "PathLib.h"
#include "Blocks.h"
#include "Hero.h"
#include "BlockRenderer.h"

USING_NS_CC;

namespace JE {
  struct Arg {
    Arg(const std::string &defaultVal, bool opt) : value(defaultVal), optional(opt) {}

    std::string value;
    bool optional{false};

    bool getBool() const {
      return value == "true" ? true : false;
    }

    int getInt() const {
      return atoi(value.c_str());
    }

    float getFloat() const {
      return atof(value.c_str());
    }
  };

  struct Event {
    std::string command;
    std::vector<Arg> args;
    std::function<void(const std::vector<Arg> &args, BlockBase *block)> func;

    int getMinimumArgs() {
      int nonOpt = 0;
      for (auto &a : args) {
        nonOpt += a.optional ? 0 : 1;
      }
      return nonOpt;
    }
  };
}

static std::map<std::string, JE::Event> EventLists;

static void initEvents() {
  using JE::Event;
  using JE::Arg;

  if (!EventLists.empty()) {
    return;
  }
  {
    Event e;
    e.command = "open_door";
    e.args = {
        {"",     false},    // ID
        {"250",  true},  // SPEED
        {"true", true}, // DIR
    };
    e.func = [&](const std::vector<Arg> &args, BlockBase *block) {
        auto targetBlock = GameLogic::Game->findBlock(args[0].getInt());
        if (!targetBlock) {
          CCLOG("Bad ID: %d", args[0].getInt());
          return;
        }
        targetBlock->openDoor(args[1].getFloat(), args[2].getBool());
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "close_door";
    e.args = {
        {"",     false},    // ID
        {"250",  true},  // SPEED
        {"true", true}, // DIR
    };
    e.func = [&](const std::vector<Arg> &args, BlockBase *block) {
        auto targetBlock = GameLogic::Game->findBlock(args[0].getInt());
        if (!targetBlock) {
          CCLOGWARN("Bad ID: %d", args[0].getInt());
          return;
        }
        targetBlock->closeDoor(args[1].getFloat(), args[2].getBool());
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "exit";

    e.func = [&](const std::vector<Arg> &args, BlockBase *block) {
        GameLogic::Game->mWinFlag = true;
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "die";

    e.func = [&](const std::vector<Arg> &args, BlockBase *block) {
        GameLogic::Game->mDeadFlag = true;        
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "dummy";
    
    e.func = [&](const std::vector<Arg> &args, BlockBase *block) {};
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "show";
    e.args = {
        {"", false},    // ID
    };
    e.func = [&](const std::vector<Arg> &args, BlockBase *block) {
        auto targetBlock = GameLogic::Game->findBlock(args[0].getInt());
        if (!targetBlock) {
          CCLOGWARN("Bad ID: %d", args[0].getInt());
          return;
        }

        targetBlock->setVisible(true);
        targetBlock->getRenderer()->getPhysicsBody()->setEnabled(true);
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "hide";
    e.args = {
        {"", false},    // ID
    };
    e.func = [&](const std::vector<Arg> &args, BlockBase *block) {
        auto targetBlock = GameLogic::Game->findBlock(args[0].getInt());
        if (!targetBlock) {
          CCLOGWARN("Bad ID: %d", args[0].getInt());
          return;
        }

        targetBlock->setVisible(false);
        targetBlock->getRenderer()->getPhysicsBody()->setEnabled(false);
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "pause_path";
    e.args = {
        {"", false},    // ID
    };
    e.func = [&](const std::vector<Arg> &args, BlockBase *block) {
        auto targetBlock = GameLogic::Game->findBlock(args[0].getInt());
        if (!targetBlock) {
          CCLOGWARN("Bad ID: %d", args[0].getInt());
          return;
        }
        if (targetBlock->mPath.empty()) {
          CCLOGWARN("The object(ID=%d) has no path!", args[0].getInt());
          return;
        }
        targetBlock->mPath.mPause = true;
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "resume_path";
    e.args = {
        {"", false},    // ID
    };
    e.func = [&](const std::vector<Arg> &args, BlockBase *block) {
        auto targetBlock = GameLogic::Game->findBlock(args[0].getInt());
        if (!targetBlock) {
          CCLOGWARN("Bad ID: %d", args[0].getInt());
          return;
        }
        if (targetBlock->mPath.empty()) {
          CCLOGWARN("The object(ID=%d) has no path!", args[0].getInt());
          return;
        }
        targetBlock->mPath.mPause = false;
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "clear_stage";
    e.func = [&](const std::vector<Arg> &args, BlockBase *block) {
        printf("clearstage\n");
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "fade_in";
    e.args = {
      { "", false },   // ID
      { "0.5", true }, // TIME
    };
    e.func = [&](const std::vector<Arg>& args, BlockBase* block){
      auto targetBlock = GameLogic::Game->findBlock(args[0].getInt());
      if (!targetBlock) {
        CCLOGWARN("Bad ID: %d", args[0].getInt());
        return;
      }
      targetBlock->getRenderer()->getNode()->runAction(FadeIn::create(args[1].getFloat()));
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "fade_out";
    e.args = {
      { "", false },   // ID
      { "0.5", true }, // TIME
    };
    e.func = [&](const std::vector<Arg>& args, BlockBase* block){
      auto targetBlock = GameLogic::Game->findBlock(args[0].getInt());
      if (!targetBlock) {
        CCLOGWARN("Bad ID: %d", args[0].getInt());
        return;
      }
      targetBlock->getRenderer()->getNode()->runAction(FadeOut::create(args[1].getFloat()));
    };
    EventLists[e.command] = e;
  }
  {
    Event e;
    e.command = "anim_up_down";
    e.args = {
      { "20", true },  // DISTANCE
      { "0.3", true }, // MOVE TIME
      { "1", true },   // STOP TIME
    };
    e.func = [&](const std::vector<Arg>& args, BlockBase* block) {
      float moveTime = args[1].getFloat();
      Vec2 delta(0, args[0].getFloat());
      float stopTime = args[2].getFloat();
      auto action = RepeatForever::create(Sequence::create(DelayTime::create(stopTime),
                                                           MoveBy::create(moveTime, delta),
                                                           MoveBy::create(moveTime, -delta),
                                                           MoveBy::create(moveTime, delta),
                                                           MoveBy::create(moveTime, -delta),
                                                           NULL));
      block->getRenderer()->getNode()->runAction(action);
    };
    EventLists[e.command] = e;
  }
}

void Events::callEvents(std::vector<std::string>& events, BlockBase *caller) {
  for (auto& e : events) {
    if (!e.empty()) {
      callSingleEvent(e.c_str(), caller);
    }
  }
}

void Events::callSingleEvent(const char *event, BlockBase *caller = NULL) {
  initEvents();

  if (!event) {
    CCLOGWARN("Calling null event!");
    return;
  }

  std::string e = event;
  auto splits = PathLib::stringSplit(e, " ");
  if (splits.empty()) {
    CCLOGWARN("Calling empty event!");
    return;
  }

  auto eit = EventLists.find(splits[0]);
  if (eit == EventLists.end()) {
    CCLOGWARN("Cannot locate event: %s!", splits[0].c_str());
    return;
  }

  if (splits.size() > eit->second.args.size() + 1) {
    CCLOGWARN("Too many arguments for the event calling: \"%s\"!", event);
    return;
  }

  if (splits.size() < eit->second.getMinimumArgs() + 1) {
    CCLOG("Too few arguments for the event calling: \"%s\"!", event);
    return;
  }

  std::vector<JE::Arg> args;

  for (size_t i = 0; i < eit->second.args.size(); ++i) {
    auto arg = eit->second.args[i]; //copy
    if (i + 1 < splits.size())
      arg.value = splits[i + 1];
    args.push_back(arg);
  }

  // Call
  eit->second.func(args, caller);
}

