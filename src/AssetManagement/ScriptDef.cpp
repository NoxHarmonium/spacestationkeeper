//
//  ScriptDef.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#include "ScriptDef.h"
#include "cinder/Utilities.h"
#include "Utils.h"

using namespace std;
using namespace ci;
using namespace ci::app;
using namespace boost;

ScriptDef::ScriptDef(int id, int order, vector<string> filenames)
    : AssetDefBaseT<string>(id) {
  _order = order;
  _filenames = filenames;
}

ScriptDef::~ScriptDef() {}

string ScriptDef::getFilename(int index) { return _filenames[index]; }

AssetType ScriptDef::getAssetType() { return GetAssetType<ScriptDef>::value; }

void ScriptDef::loadAsset() {
  _program = "";
  for (string filename : _filenames) {
    filesystem::path p = getPath() / filename;
    string code = loadString(loadFile(p.string()));
    _program += code;
  }
}

void ScriptDef::unloadAsset() { _program = ""; }

std::shared_ptr<ScriptDef> ScriptDef::FromYamlNode(YAML::Node node) {
  cout << "Deserialising ScriptDef... ";

  int id = 0;
  int order = 0;
  Node sources;
  vector<string> filenames;

  Utils::parseNode<int>(&id, node, "id");
  Utils::parseNode<int>(&id, node, "order");
  Utils::getChildNode(&sources, node, "sources");

  for (Node n : sources) {
    filenames.push_back(n.as<string>());
  }

  ScriptDef *scriptDef = new ScriptDef(id, order, filenames);

  return ScriptDefRef(scriptDef);
}
