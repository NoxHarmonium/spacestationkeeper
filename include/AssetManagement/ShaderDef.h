//
//  GameShader.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/04/2014.
//
//

#ifndef SpaceStationKeeper_GameShader_h
#define SpaceStationKeeper_GameShader_h

#include "AssetDefBase.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include <map>

#define SHADER_UNKNOWN "Unknown"
#define SHADER_FRAGMENT "Fragment"
#define SHADER_VERTEX "Vertex"
#define SHADER_GEOMETERY "Geometery"

using namespace ci;

class ShaderDef : public AssetDefBase {
public:
  enum ShaderType { Unknown, Fragment, Vertex, Geometry };

  ShaderDef();
  ShaderDef(int id, ShaderType shaderType, string filename);
  ShaderDef(int id, map<ShaderType, string> _filenameMap);

  void setValues(int id, map<ShaderType, string> _filenameMap);
  string getFilename(ShaderType shaderType);
  void setPath(filesystem::path path);
  filesystem::path getPath();
  gl::GlslProgRef useShader();
  void releaseShader();

  static std::shared_ptr<ShaderDef> FromYamlNode(YAML::Node node);

private:
  map<ShaderType, string> _filenameMap;
  filesystem::path _path; // TODO: Directory path, need to rename to be clearer
  gl::GlslProgRef _prog = nullptr;
};

typedef std::shared_ptr<ShaderDef> ShaderDefRef;

template <> struct GetAssetType<ShaderDef> {
  static const AssetType value = AssetType::Shader;
};

#endif
