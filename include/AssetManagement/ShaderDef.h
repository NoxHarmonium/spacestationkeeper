//
//  GameShader.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/04/2014.
//
//

#ifndef SpaceStationKeeper_GameShader_h
#define SpaceStationKeeper_GameShader_h

#include <map>
#include "cinder/gl/GlslProg.h"
#include "yaml.h"
#include "AssetDefBaseT.h"

#define SHADER_UNKNOWN "Unknown"
#define SHADER_FRAGMENT "Fragment"
#define SHADER_VERTEX "Vertex"
#define SHADER_GEOMETERY "Geometery"

using namespace ci;

/*!
 @brief Encapsulates a set of shader programs loaded from the assets directory.
 @discussion You usually assign a Material object a ShaderDef for
 RenderComponents to use for rendering.
 Shaders are defined in YAML in the following format:
 @textblock
 <pre>
 --- # Shader Def
 id:          1
 type:        Shader
 components:
 vertex:
  source:     vertex.glsl
 fragment:
  source:     fragment.glsl
 geometry:
  source:     geometry.glsl
 </pre>
 @/textblock
 */
class ShaderDef : public AssetDefBaseT<gl::GlslProg> {
public:
  // Enums
  enum class ShaderType { Unknown, Fragment, Vertex, Geometry };

  // Constructors/Destructors
  ~ShaderDef();

  // Getters/Setters
  /*! Gets the filename of each shader program (not the full path). */
  string getFilename(const ShaderType shaderType);
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
  static std::shared_ptr<ShaderDef> FromYamlNode(YAML::Node node);

private:
  // Constructors/Destructors
  /* Constructs a new instance of ShaderDef with values provided through the
   * static method FromYamlNode(). */
  ShaderDef(int id, map<ShaderType, string> _filenameMap);

  // Static Methods
  /*! Load in a shader source from a YAML node. Returns true if key exists,
   * otherwise false. */
  static bool parseShader(Node node, string key,
                          map<ShaderType, string> *filenameMap,
                          ShaderDef::ShaderType shaderType);

  // Fields
  /* Maps shader types to their source files. */
  map<ShaderType, string> _filenameMap;
  /*! The reference to the OpenGL shader program. (Wrapped by Cinder)*/
  gl::GlslProgRef _prog = nullptr;
};

/*! A shared pointer reference to a ShaderDef object. */
typedef std::shared_ptr<ShaderDef> ShaderDefRef;

/*! A specilization of GetAssetType to allow compile time definition of this
 * class's AssetType. */
template <> struct GetAssetType<ShaderDef> {
  static const AssetType value = AssetType::Shader;
};

#endif
