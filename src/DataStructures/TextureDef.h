//
//  TextureDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 19/03/2014.
//
//

#ifndef SpaceStationKeeper_TextureDef_h
#define SpaceStationKeeper_TextureDef_h

struct TextureDef {
  int width;
  int height;
  int frameHeight;
  int frameWidth;
  std::string source;

  static TextureDef loadFromPath(std::string path) {}
};

#endif
