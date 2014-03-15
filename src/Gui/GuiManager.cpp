//
//  GuiManager.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/03/2014.
//
//

#include "GuiManager.h"

using namespace cinder;
using namespace cinder::app;
using namespace cinder::cairo;

void GuiManager::update() {
  // Only redraw cairo surface if there is a change (expensive)
  if (_currentText != _prevText) {
    DisplayRef dispRef = parentApp->getDisplay();
    // TODO: Just hard coded test commands, will be replaced with a system of
    // nested GUI components at some point
    cairo::Context ctx = cairo::Context(*_cairoSurface);

    ctx.setFontSize(40.0);
    ctx.moveTo(5.0, 35.0);
    ctx.textPath(_currentText);
    ctx.setSource(Color(1.0f, 0.0f, 0.0f));
    ctx.fill();

    _prevText = _currentText;
    _currentTexture = gl::Texture(_cairoSurface->getSurface());
  }
}

void GuiManager::draw() { gl::draw(_currentTexture); }

void GuiManager::setup() {
  DisplayRef dispRef = parentApp->getDisplay();

  cleanUp();
  _cairoSurface =
      new SurfaceImage(dispRef->getWidth(), dispRef->getHeight(), true);
}

void GuiManager::resize() {
  // Reconfigure GUI when the window is resized.
  setup();
}

void GuiManager::cleanUp() {
  if (_cairoSurface != NULL) {
    delete _cairoSurface;
    _cairoSurface = NULL;
  }
}

GuiManager::GuiManager(AppNative *app) : GameComponent(app) {
  DisplayRef dispRef = parentApp->getDisplay();

  _cairoSurface =
      new SurfaceImage(dispRef->getWidth(), dispRef->getHeight(), true);
}
