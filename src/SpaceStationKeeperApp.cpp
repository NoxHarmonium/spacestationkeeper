#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Cairo.h"
#include "cinder/gl/Texture.h"
#include "GuiManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace cinder::cairo;

class SpaceStationKeeperApp : public AppNative {

public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
  void resize();
  
private:
  GuiManager* _guiManager;

};

void SpaceStationKeeperApp::setup()
{
  _guiManager = new GuiManager(this);
}

void SpaceStationKeeperApp::resize()
{
  _guiManager->Reset();
}

void SpaceStationKeeperApp::mouseDown( MouseEvent event )
{
  
}

void SpaceStationKeeperApp::update()
{
  _guiManager->Update();
  

}

void SpaceStationKeeperApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
  _guiManager->Draw();
    
}

CINDER_APP_NATIVE( SpaceStationKeeperApp, RendererGl )
