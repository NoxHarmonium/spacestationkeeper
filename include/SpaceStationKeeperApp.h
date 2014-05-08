//
//  SpaceStationKeeper.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 23/04/2014.
//
//

#ifndef SpaceStationKeeper_SpaceStationKeeper_h
#define SpaceStationKeeper_SpaceStationKeeper_h

#include "cinder/app/AppNative.h"
#include "BindingManager.h"
#include "GameCamera.h"
#include "ComponentDrivenApp.h"
#include "BindingManager.h"
#include <memory>

class SpaceStationKeeperApp : public ComponentDrivenApp {

public:
  void prepareSettings(Settings *settings);
  void setup();
  void draw();
  void resize();
  void keyDown(KeyEvent event);

private:
  // GuiManager *_guiManager;
  // GameGrid *_gameGrid;
  GameCamera *_camera;
  // JobManager *_jobManager;
  std::unique_ptr<BindingManager> _bindingManager;
};

#endif
