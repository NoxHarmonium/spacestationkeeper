//
//  AnimationDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 18/05/2014.
//
//

#ifndef SpaceStationKeeper_AnimationDef_h
#define SpaceStationKeeper_AnimationDef_h

#include "TextureDef.h"

class AnimationDef : public TextureDef {
public:
  // Constructors/Destructors
  virtual ~TextureDef();
  
  
  /*! Gets the filename of the source texture file (not the full path). */
  virtual string getFilename();
  /*! Gets the filename of the source texture file (not the full path). */
  virtual string getFilename();

};

#endif
