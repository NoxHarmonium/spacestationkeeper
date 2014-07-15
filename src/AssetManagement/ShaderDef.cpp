//
//  GameShader.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/04/2014.
//
//

#include "ShaderDef.h"
#include "AssetLoadException.h"
#include "Utils.h"

namespace BlazeEngine {
namespace AssetManagement {

using namespace YAML;
using namespace BlazeEngine::Exceptions;
using namespace BlazeEngine::Misc;

// Constructors/Destructors

ShaderDef::~ShaderDef() {};

// Getters/Setters
ShaderDef::ShaderDef(int id, map<ShaderType, string> filenameMap)
    : _filenameMap(filenameMap), AssetDefBaseT(id) {}

string ShaderDef::getFilename(const ShaderDef::ShaderType shaderType) {
  if (_filenameMap.count(shaderType)) {
    return _filenameMap[shaderType];
  }
  return nullptr;
}

AssetType ShaderDef::getAssetType() { return GetAssetType<ShaderDef>::value; }

// Methods

void ShaderDef::loadAsset() {
  if (!assetLoaded() && _shouldLoad) {
    cout << "Loading shader at: " << getPath() << endl;

    // DataSourceRef default constructor is null;
    DataSourceRef vertexShaderData = DataSourceRef();
    DataSourceRef fragmentShaderData = DataSourceRef();
    DataSourceRef geometeryShaderData = DataSourceRef();

    for (auto &shaderPair : _filenameMap) {
      switch (shaderPair.first) {
      case ShaderDef::ShaderType::Vertex: {
        // cout << " ...vertex" << endl;
        vertexShaderData = loadFile(getPath() / shaderPair.second);
        break;
      }
      case ShaderDef::ShaderType::Fragment: {
        // cout << " ...fragment";
        fragmentShaderData = loadFile(getPath() / shaderPair.second);
        break;
      }
      case ShaderDef::ShaderType::Geometry: {
        // cout << " ...geometry";
        geometeryShaderData = loadFile(getPath() / shaderPair.second);
        break;
      }
      default: {
        cout << "Warning: Bogus shader type loaded from asset: " << getPath()
             << endl;
      }
      }
    }

    if (!(vertexShaderData || fragmentShaderData || geometeryShaderData)) {
      throw AssetLoadException(
          AssetLoadException::AssetLoadExceptionReason::SourceFileMissing);
    }

    try {
      setAssetPointer(gl::GlslProg::create(vertexShaderData, fragmentShaderData,
                                           geometeryShaderData));
    }
    catch (const gl::GlslProgCompileExc &exc) {
      std::cout << std::endl << "Error: Shader compile error: " << std::endl;
      std::cout << exc.what();
      throw AssetLoadException(&exc);
      _shouldLoad = false; // Prevent bad assets from reloading multiple times.
    }
    catch (const std::exception &e) {
      std::cout << std::endl << "Error: Unable to load shader" << std::endl;
      _shouldLoad = false; // Prevent bad assets from reloading multiple times.
      throw AssetLoadException(&e);
    }
  }
}

void ShaderDef::unloadAsset() {
  // shared_ptr will handle destruction if nothing else has
  // a reference
  setAssetPointer(nullptr);
}

bool ShaderDef::parseShader(Node node, string key,
                            map<ShaderType, string> *filenameMap,
                            ShaderDef::ShaderType shaderType) {
  Node childNode;
  string source;

  bool nodeExists = Utils::getChildNode(&childNode, node, key, false);
  if (nodeExists) {
    Utils::parseNode<string>(&source, childNode, "source");
    (*filenameMap)[shaderType] = source;
    return true;
  }
  return false;
}

// Static Methods

std::shared_ptr<ShaderDef> ShaderDef::FromYamlNode(YAML::Node node) {
  // cout << "Deserialising ShaderDef... " << endl;

  int id = 0;
  Node components;
  map<ShaderDef::ShaderType, string> _filenameMap;

  Utils::parseNode<int>(&id, node, "id");
  Utils::getChildNode(&components, node, "components");

  bool geomExists = parseShader(components, "geometry", &_filenameMap,
                                ShaderDef::ShaderType::Geometry);
  bool fragExists = parseShader(components, "fragment", &_filenameMap,
                                ShaderDef::ShaderType::Fragment);
  bool vertexExists = parseShader(components, "vertex", &_filenameMap,
                                  ShaderDef::ShaderType::Vertex);

  // Transitive dependencies (i.e. frag shader needs vertex shader.)
  if ((geomExists && !(fragExists && vertexExists)) ||
      (fragExists && !vertexExists) || !vertexExists) {
    throw AssetLoadException(AssetLoadException::AssetLoadExceptionReason::
                                 AssetDefMissingDependencies,
                             "The shader pipeline depends on a specific "
                             "order of defined shaders (i.e. You need a "
                             "vertex shader for a fragment shader).");
  }

  ShaderDef *shaderDef = new ShaderDef(id, _filenameMap);

  return ShaderDefRef(shaderDef);
}
}
}