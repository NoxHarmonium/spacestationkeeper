//
//  GameShader.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/04/2014.
//
//

#include "ShaderDef.h"

using namespace YAML;
ShaderDef::~ShaderDef() {};

ShaderDef::ShaderDef(int id, map<ShaderType, string> filenameMap)
    : _filenameMap(filenameMap), AssetDefBaseT(id) {}

string ShaderDef::getFilename(const ShaderDef::ShaderType shaderType) {
  if (_filenameMap.count(shaderType)) {
    return _filenameMap[shaderType];
  }
  return nullptr;
}

// Methods
void ShaderDef::loadAsset() {
  if (!assetLoaded() && _shouldLoad) {
    cout << "Loading shader at: " << getPath() << endl;

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

    // TODO: Check at least one shader is loaded

    try {
      setAssetPointer(gl::GlslProg::create(vertexShaderData, fragmentShaderData,
                                           geometeryShaderData));
    }
    catch (gl::GlslProgCompileExc &exc) {
      std::cout << std::endl << "Error: Shader compile error: " << std::endl;
      std::cout << exc.what();
      _shouldLoad = false; // Prevent bad assets from reloading multiple times.
    }
    catch (...) {
      std::cout << std::endl << "Error: Unable to load shader" << std::endl;
      _shouldLoad = false; // Prevent bad assets from reloading multiple times.
    }

    cout << endl;
  }
}

void ShaderDef::unloadAsset() {
  // shared_ptr will handle destruction if nothing else has
  // a reference
  setAssetPointer(nullptr);
}

// Static Methods
std::shared_ptr<ShaderDef> ShaderDef::FromYamlNode(YAML::Node node) {
  cout << "Deserialising ShaderDef... ";

  int id = node["id"].as<int>();

  map<ShaderDef::ShaderType, string> _filenameMap;

  Node components = node["components"];
  if (components["vertex"]) {
    cout << "vertex ";
    string source = components["vertex"]["source"].as<string>();
    _filenameMap[ShaderDef::ShaderType::Vertex] = source;
  }
  if (components["fragment"]) {
    cout << "fragment ";
    string source = components["fragment"]["source"].as<string>();
    _filenameMap[ShaderDef::ShaderType::Fragment] = source;
  }
  if (components["geometry"]) {
    cout << "geometry ";
    string source = components["geometry"]["source"].as<string>();
    _filenameMap[ShaderDef::ShaderType::Geometry] = source;
  }

  cout << endl;

  ShaderDef *shaderDef = new ShaderDef(id, _filenameMap);

  // TODO: Validate and return nullptr/exception if invalid.
  return ShaderDefRef(shaderDef);
}