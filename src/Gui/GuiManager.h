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
#include "GameComponent.h"

using namespace cinder::app;
using namespace cinder::cairo;

class GuiManager : public GameComponent {
public:
  GuiManager(AppNative *parent);
  void setup();
  void update();
  void draw();

private:
  SurfaceImage *_cairoSurface;
};

#endif
