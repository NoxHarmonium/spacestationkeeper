#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SpaceStationKeeperApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void SpaceStationKeeperApp::setup()
{
}

void SpaceStationKeeperApp::mouseDown( MouseEvent event )
{
}

void SpaceStationKeeperApp::update()
{
}

void SpaceStationKeeperApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( SpaceStationKeeperApp, RendererGl )
