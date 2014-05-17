//
//  SpaceStationKeeper.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 23/04/2014.
//
//

#ifndef SpaceStationKeeper_SpaceStationKeeper_h
#define SpaceStationKeeper_SpaceStationKeeper_h

#include "pch.h"
#include "cinder/app/AppNative.h"
#include "BindingManager.h"
#include "GameCamera.h"
#include "ComponentDrivenApp.h"
#include "BindingManager.h"
#include <memory>
#include "boost/filesystem.hpp"
#include "FileAssetLoader.h"
#include "Utils.h"

class SpaceStationKeeperApp : public ComponentDrivenApp {

public:
  void prepareSettings(Settings *settings);
  void setup();
  void draw();
  void resize();
  void keyDown(KeyEvent event);

private:
  void scanAssetsAndExecuteScripts();
  string getRelativePath(filesystem::path p, filesystem::path root);

  // GuiManager *_guiManager;
  // GameGrid *_gameGrid;
  GameCamera *_camera;
  // JobManager *_jobManager;
  BindingManager *_bindingManager;
  std::shared_ptr<FileAssetLoader> _fileAssetLoader;
  std::shared_ptr<JobManager> _jobManager;
};

#endif
