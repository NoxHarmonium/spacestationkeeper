//
//  Renderable.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 2/08/2014.
//
//

#ifndef SpaceStationKeeper_Renderable_h
#define SpaceStationKeeper_Renderable_h

#include "RenderInfo.h"
#include <memory>

namespace BlazeEngine {
namespace Components {

class Renderable {
public:
  // Public Fields
  RenderInfoRef renderer = nullptr;
};

typedef std::shared_ptr<Renderable> RenderableRef;
}
}

#endif
