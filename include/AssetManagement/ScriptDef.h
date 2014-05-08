//
//  ScriptDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 7/05/2014.
//
//

#ifndef SpaceStationKeeper_ScriptDef_h
#define SpaceStationKeeper_ScriptDef_h

#include "yaml.h"
#include "AssetDefBaseT.h"

using namespace ci;

/*! Encapsulates a LUA script. */
class ScriptDef : public AssetDefBaseT<string> {
public:
  // Constructors/Destructors
  ScriptDef(int id, int order, vector<string> filenames);
  ~ScriptDef();

  // Getters/Setters
  /*! Gets the filename of each script (not the full path). */
  string getFilename(int index);
  /*! Gets the type definition of this asset definition. */
  virtual AssetType getAssetType();

  // Methods
  /*! Loads the asset pointed to by this AssetRef object into memory so it can
   * be used. */
  void loadAsset();
  /*! Unloads the asset pointed to by this AssetRef object making it unavailable
   * for use. */
  void unloadAsset();

  // Static Methods
  /*! Constructs an instance of ShaderDef from a loaded YAML node. This should
   * be called by an AssetLoader and not directly through scripts. */
  static std::shared_ptr<ScriptDef> FromYamlNode(YAML::Node node);

private:
  // Constructors/Destructors
  /* Constructs a new instance of ShaderDef with values provided through the
   * static method FromYamlNode(). */
  ScriptDef(int id, vector<string> filenames);

  // Fields
  /* Maps shader types to their source files. */
  vector<string> _filenames;
  /*! The reference to the OpenGL shader program. (Wrapped by Cinder)*/
  string _program = nullptr;
  /*! The execution order of this script. Scripts with lower numbers execute
   * first. */
  int _order;
};

/*! A shared pointer reference to a ShaderDef object. */
typedef std::shared_ptr<ScriptDef> ScriptDefRef;

/*! A specilization of GetAssetType to allow compile time definition of this
 * class's AssetType. */
template <> struct GetAssetType<ScriptDef> {
  static const AssetType value = AssetType::Script;
};

#endif
