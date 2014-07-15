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
#include "yaml-cpp/yaml.h"
#include "cinder/gl/Texture.h"
#include "AssetDefBaseT.h"
#include "AssetLoadException.h"
#include "Passibility.h"

#define TEXTURE_UNKNOWN "Unknown"
#define TEXTURE_TILE "Tile"
#define TEXTURE_SIMPLE "Simple"
#define TEXTURE_ANIMATION "Animation"

namespace BlazeEngine {
namespace AssetManagement {

using namespace std;
using namespace ci;
using namespace YAML;

class TextureDef : public AssetDefBaseT<gl::Texture> {
public:
  // Enums
  enum class TextureType { Unknown, Tile, Simple, Animation };

  // Constructors/Destructors
  TextureDef(Node node);
  TextureDef(Node node, bool loadFilename);
  virtual ~TextureDef();

  // Getters/Setters
  /*! Gets the total width of the texture. */
  virtual int getWidth();
  /*! Gets the total height of the texture. */
  virtual int getHeight();
  /*! Gets the width of a frame within the texture (for defining sprites). */
  virtual int getFrameWidth();
  /*! Gets the height of a frame within the texture (for defining sprites). */
  virtual int getFrameHeight();
  /*! Gets the size of a frame within the texture (for defining sprites). */
  virtual Rectf getFrameSize();
  /*! Gets the border around each frame in a texture. */
  virtual float getBorder();
  /*! Gets the total number of frames. */
  virtual int getFrameCount();
  /*! Gets the uv coordinates to render the specified frame. */
  virtual Rectf getFrameUvCoords(const int frameNumber);
  /*! Gets if the TextureDef can be used for animation. */
  virtual bool getIsAnimated();
  /*! Gets the filename of the tile texture. */
  string getFilename();
  /*! Gets the type definition of this asset definition. */
  virtual AssetType getAssetType();

  // Methods
  /*! Loads the asset pointed to by this AssetRef object into memory so it can
   * be used. */
  virtual void loadAsset();
  /*! Unloads the asset pointed to by this AssetRef object making it unavailable
   * for use. */
  virtual void unloadAsset();

  // Static Methods
  /*! Constructs an instance of TextureDef from a loaded YAML node. This should
   * be called by an AssetLoader and not directly through scripts. */
  static std::shared_ptr<TextureDef> FromYamlNode(Node node);

protected:
  /*! The filename of the source texture file (not the full path). */
  string _filename;

private:
  // Fields
  /*! The total width of the texture. */
  int _width;
  /*! The total height of the texture. */
  int _height;
  /*! The width of a frame within the texture (for defining sprites). */
  int _frameWidth;
  /*! The height of a frame within the texture (for defining sprites). */
  int _frameHeight;
  /*! Determines the border around each frame in a texture. */
  float _border;
};

// Needed for Lua to compare instances
bool operator==(const TextureDef &a, const TextureDef &b);
// Needed for Lua to print address
std::ostream &operator<<(std::ostream &lhs, const TextureDef &rhs);

/*! A shared pointer reference to a TextureDef object. */
typedef std::shared_ptr<TextureDef> TextureDefRef;

/*! A specilization of GetAssetType to allow compile time definition of this
 * classes AssetType. */
template <> struct GetAssetType<TextureDef> {
  static const AssetType value = AssetType::Texture;
};
}
}
#endif
