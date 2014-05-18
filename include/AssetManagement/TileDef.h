//
//  SpriteDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 18/05/2014.
//
//

#ifndef SpaceStationKeeper_SpriteDef_h
#define SpaceStationKeeper_SpriteDef_h

#include "TextureDef.h"

using namespace std;

class TileDef : public TextureDef {
public:
  // Constructors/Destructors
  virtual ~TileDef();

  // Getters/Setters
  /*! Gets if the texture can have things on top of it. */
  bool getCanWalk();
  /*! Gets the filename of the tile texture. */
  string getFilename();
  /*! Gets the Passability enum for a particular frame. */
  Passibility getPassiblity(const int frameNumber);
  /*! Sets the Passabilty enum for a particular frame. */
  void setPassiblity(const int frameNumber, const Passibility passability);
  /*! Gets the first frame that matches the provided Passability enum. */
  int getFrameFromPassibility(const Passibility passability);

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
  static std::shared_ptr<TileDef> FromYamlNode(Node node);

private:
  // Constructors/Destructors
  /*! Constructs a new instance of SpriteDef with values provided through the
   * static method FromYamlNode(). */
  TileDef(int id, int width, int height, int frameHeight, int frameWidth,
          string filename, bool canWalk, float border);

  // Fields
  /*! Determines if the texture can have things on top of it. */
  bool _canWalk;
  /*! The filename of the source texture file (not the full path). */
  string _filename;
  /*! The an array of enum which defines the passability of each edge. The index
   * refers to the frame number. */
  vector<Passibility> _passibilities;
  /*! Maps passability values to frames. (opposite of the _passibilities
   * field)*/
  map<int, int> _passabilityMap;
  /*! The reference to the OpenGL texture. (Wrapped by Cinder)*/
  gl::TextureRef _texture = nullptr;
};

/*! A shared pointer reference to a TextureDef object. */
typedef std::shared_ptr<TileDef> TileDefRef;

/*! A specilization of GetAssetType to allow compile time definition of this
 * classes AssetType. */
template <> struct GetAssetType<TileDef> {
  static const AssetType value = AssetType::Texture;
};

#endif
