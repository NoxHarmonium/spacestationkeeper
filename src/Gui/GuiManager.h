//
//  GuiManager.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/03/2014.
//
//

#ifndef SpaceStationKeeper_GuiManager_h
#define SpaceStationKeeper_GuiManager_h

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Cairo.h"
#include "cinder/gl/Texture.h"

using namespace cinder::app;
using namespace cinder::cairo;

class GuiManager {
public:
  GuiManager(AppNative *app);
  void Update();
  void Draw();
  void Reset();

private:
  AppNative *parentApp;
  SurfaceImage *_cairoSurface;
};

#endif
