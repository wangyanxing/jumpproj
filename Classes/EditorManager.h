//
//  EditorManager.h
//  jumpproj
//
//  Created by Yanxing Wang on 2/3/16.
//
//

#ifndef EditorManager_h
#define EditorManager_h

#include "Prerequisites.h"
#include "Singleton.h"

class EditorManager {
public:
  DECL_SIMPLE_SINGLETON(EditorManager);

  void init();

  cocos2d::Node *getEditorRootNode() {
    return mEditorRoot;
  }

  cocos2d::DrawNode *getGridNode() {
    return mGridNode;
  }

  void afterLoad();

  void loadLastEdit();

  void onMouseDown(const MouseEvent &event);

  void onMouseUp(const MouseEvent &event);

  void onMouseMove(const MouseEvent &event);

private:
  void registerInputs();

  void openMapFile();

  void initHelpers();

  void toggleHelpersVisible();

  void clearSelections();

  void moveObjects(cocos2d::EventKeyboard::KeyCode key);

  void resizeObjects(cocos2d::EventKeyboard::KeyCode key);

private:
  cocos2d::Node *mEditorRoot{nullptr};

  cocos2d::DrawNode *mGridNode{nullptr};

  std::vector<GameObject*> mSelections;
};

#endif /* EditorManager_h */
