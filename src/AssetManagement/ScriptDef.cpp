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
    : _filenames(filenames), _order(order), AssetDefBaseT<string>(id) {}

ScriptDef::~ScriptDef() {}

string ScriptDef::getFilename(int index) { return _filenames[index]; }

int ScriptDef::getOrder() { return _order; }

AssetType ScriptDef::getAssetType() { return GetAssetType<ScriptDef>::value; }

void ScriptDef::loadAsset() {
  std::shared_ptr<string> program = make_shared<string>();

  for (string filename : _filenames) {
    filesystem::path p = getPath() / filename;
    string code = loadString(loadFile(p.string()));
    *program += code;
  }
  setAssetPointer(program);
}

void ScriptDef::unloadAsset() { setAssetPointer(nullptr); }

std::shared_ptr<ScriptDef> ScriptDef::FromYamlNode(YAML::Node node) {
  // cout << "Deserialising ScriptDef... ";

  int id = 0;
  int order = 0;
  Node sources;
  vector<string> filenames;

  Utils::parseNode<int>(&id, node, "id");
  Utils::parseNode<int>(&order, node, "order");
  Utils::getChildNode(&sources, node, "sources");

  for (Node n : sources) {
    filenames.push_back(n.as<string>());
  }

  ScriptDef *scriptDef = new ScriptDef(id, order, filenames);

  return ScriptDefRef(scriptDef);
}
