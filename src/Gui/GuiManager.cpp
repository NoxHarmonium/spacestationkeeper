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

void GuiManager::Update()
{
  DisplayRef dispRef = parentApp->getDisplay();
  
  cairo::Context ctx = cairo::Context(*_cairoSurface);
  //ctx.moveTo(dispRef->getSize() * 0.5f);
  //
  //ctx.textPath("Test Text");
  //ctx.moveTo(0, 0);
  ctx.rectangle(0, 0, dispRef->getWidth(), dispRef->getHeight());
  ctx.setSource(Color(1.0f, 0.0f, 0.0f));
  ctx.fill();

}

void GuiManager::Draw()
{
  gl::Texture texture = gl::Texture( _cairoSurface->getSurface() );
  gl::draw(texture);
}

void GuiManager::Reset()
{
  DisplayRef dispRef = parentApp->getDisplay();
  
  _cairoSurface = new SurfaceImage(
    dispRef->getWidth(),
    dispRef->getHeight(),
    true
  );


}

GuiManager::GuiManager(AppNative* app)
{
  parentApp = app;
  DisplayRef dispRef = parentApp->getDisplay();
  
  _cairoSurface = new SurfaceImage(
    dispRef->getWidth(),
    dispRef->getHeight(),
    true
  );
  
}