//
//  GameShader.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/04/2014.
//
//

#include "yaml.h"
#include "ShaderDef.h"

using namespace YAML;

ShaderDef::ShaderDef() {}
ShaderDef::ShaderDef(int id, ShaderType shaderType, string filename) {
  map<ShaderType, string> filenameMap;
  _filenameMap[shaderType] = filename;
  setValues(id, filenameMap);
}

ShaderDef::ShaderDef(int id, map<ShaderType, string> filenameMap) {
  setValues(id, filenameMap);
}
void ShaderDef::setValues(int id, map<ShaderType, string> filenameMap) {
  _id = id;
  _filenameMap = filenameMap;
}

string ShaderDef::getFilename(ShaderDef::ShaderType shaderType) {
  if (_filenameMap.count(shaderType)) {
    return _filenameMap[shaderType];
  }
  return nullptr;
}

void ShaderDef::setPath(filesystem::path path) { _path = path; }
filesystem::path ShaderDef::getPath() { return _path; }

gl::GlslProgRef ShaderDef::useShader() {

  if (_prog == nullptr && _shouldLoad) {
    cout << "Loading shader at: " << _path << endl;

    DataSourceRef vertexShaderData = DataSourceRef();
    DataSourceRef fragmentShaderData = DataSourceRef();
    DataSourceRef geometeryShaderData = DataSourceRef();

    for (auto &shaderPair : _filenameMap) {
      switch (shaderPair.first) {
      case ShaderDef::ShaderType::Vertex: {
        // cout << " ...vertex" << endl;
        vertexShaderData = loadFile(_path / shaderPair.second);
        break;
      }
      case ShaderDef::ShaderType::Fragment: {
        // cout << " ...fragment";
        fragmentShaderData = loadFile(_path / shaderPair.second);
        break;
      }
      case ShaderDef::ShaderType::Geometry: {
        // cout << " ...geometry";
        geometeryShaderData = loadFile(_path / shaderPair.second);
        break;
      }
      default: {
        cout << "Warning: Bogus shader type loaded from asset: " << _path;
      }
      }
    }

    // TODO: Check at least one shader is loaded

    try {
      _prog = gl::GlslProg::create(vertexShaderData, fragmentShaderData,
                                   geometeryShaderData);
      _refCount++;
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

  return _prog;
}

void ShaderDef::releaseShader() { _refCount--; }

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