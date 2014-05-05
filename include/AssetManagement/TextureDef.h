//
//  TextureDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 19/03/2014.
//
//

#ifndef SpaceStationKeeper_TextureDef_h
#define SpaceStationKeeper_TextureDef_h

#include <map>
#include "yaml.h"
#include "cinder/gl/Texture.h"
#include "AssetDefBaseT.h"
#include "AssetDefConverters.h"
#include "AssetLoadException.h"

#include "Passibility.h"

using namespace std;
using namespace ci;
using namespace YAML;

class TextureDef : public AssetDefBaseT<gl::Texture> {
public:
  // Constructors/Destructors
  ~TextureDef();

  // Getters/Setters
  /*! Gets the total width of the texture. */
  int getWidth();
  /*! Gets the total height of the texture. */
  int getHeight();
  /*! Gets the width of a frame within the texture (for defining sprites). */
  int getFrameWidth();
  /*! Gets the height of a frame within the texture (for defining sprites). */
  int getFrameHeight();
  /*! Gets the size of a frame within the texture (for defining sprites). */
  Rectf getFrameSize();
  /*! Gets if the texture can have things on top of it. */
  bool getCanWalk();
  /*! Gets the border around each frame in a texture. */
  float getBorder();
  /*! Gets the filename of the source texture file (not the full path). */
  string getFilename();
  /*! Gets the Passability enum for a particular frame. */
  Passibility getPassiblity(const int frameNumber);
  /*! Sets the Passabilty enum for a particular frame. */
  void setPassiblity(const int frameNumber, const Passibility passability);
  /*! Gets the first frame that matches the provided Passability enum. */
  int getFrameFromPassibility(const Passibility passability);
  /*! Gets the total number of frames. */
  int getFrameCount();

  // Methods
  /*! Loads the asset pointed to by this AssetRef object into memory so it can
   * be used. */
  void loadAsset();
  /*! Unloads the asset pointed to by this AssetRef object making it unavailable
   * for use. */
  void unloadAsset();

  // Static Methods
  /*! Constructs an instance of TextureDef from a loaded YAML node. This should
   * be called by an AssetLoader and not directly through scripts. */
  static std::shared_ptr<TextureDef> FromYamlNode(Node node);

private:
  // Constructors/Destructors
  /*! Constructs a new instance of TextureDef with values provided through the
   * static method FromYamlNode(). */
  TextureDef(int id, int width, int height, int frameHeight, int frameWidth,
             string filename, bool canWalk, float border);

  // Fields
  /*! The total width of the texture. */
  int _width;
  /*! The total height of the texture. */
  int _height;
  /*! The width of a frame within the texture (for defining sprites). */
  int _frameWidth;
  /*! The height of a frame within the texture (for defining sprites). */
  int _frameHeight;
  /*! Determines if the texture can have things on top of it. */
  bool _canWalk;
  /*! Determines the border around each frame in a texture. */
  float _border;
  /*! The filename of the source texture file (not the full path). */
  string _filename;
  /*! The reference to the OpenGL texture. (Wrapped by Cinder)*/
  gl::TextureRef _texture = nullptr;
  /*! The an array of enum which defines the passability of each edge. The index
   * refers to the frame number. */
  vector<Passibility> _passibilities;
  /*! Maps passability values to frames. (opposite of the _passibilities
   * field)*/
  map<int, int> _passabilityMap;
};

/*! A shared pointer reference to a TextureDef object. */
typedef std::shared_ptr<TextureDef> TextureDefRef;

/*! A specilization of GetAssetType to allow compile time definition of this
 * classes AssetType. */
template <> struct GetAssetType<TextureDef> {
  static const AssetType value = AssetType::Texture;
};

#endif
