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
#include "GuiManager.h"
#include "ComponentDrivenApp.h"
#include "GameGrid.h"
#include "GameCamera.h"
#include "EventManager.h"
#include "Resource.h"
#include "Job.h"
#include "JobManager.h"

class SpaceStationKeeperApp : public ComponentDrivenApp {

public:
  void prepareSettings(Settings *settings);
  void setup();
  void draw();
  void resize();
  void keyDown(KeyEvent event);

private:
  GuiManager *_guiManager;
  GameGrid *_gameGrid;
  GameCamera *_camera;
  JobManager *_jobManager;
};

#endif
