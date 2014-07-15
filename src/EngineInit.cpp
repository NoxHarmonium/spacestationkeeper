
#include "EngineInit.h"
#include "AssetLoadException.h"
#include "ScriptDef.h"
#include "LuaExecutionException.h"
#include "NotImplementedException.h"
#include <vector>
#include <string>

using namespace ci::app;

namespace BlazeEngine {

using namespace std;
using namespace boost;
using namespace BlazeEngine::AssetManagement;
using namespace BlazeEngine::Exceptions;
using namespace BlazeEngine::DataStructures;
using namespace BlazeEngine::Misc;
using namespace BlazeEngine::Binding;
using namespace BlazeEngine::Jobs;

void EngineInit::prepareSettings(Settings *settings) {
  // Utils::printOpenGlVersionInfo();

  settings->setFrameRate(60);
}

void EngineInit::resize() {
  // setup(); // reset app
  ComponentDrivenApp::resize();
}

void EngineInit::setup() {
  Utils::printOpenGlVersionInfo();

  vector<string> args = getArgs();
  // if (args.size() == 1) {
  //  throw runtime_error(
  //      "The game engine needs an initial scene file as an argument.");
  //}
  cout << "args size: " << args.size() << endl;
  for (string &s : args) {
    cout << "arg: " << s << endl;
  }

  _fileAssetLoader = make_shared<FileAssetLoader>(this->getResourcePath());
  setAssetLoader(dynamic_pointer_cast<AssetLoaderBase>(_fileAssetLoader)
                     .get()); // TODO: Should it be a shared ptr?

  _bindingManager = BindingManager::Instance();
  _bindingManager->initialiseBindings();

  JobManagerRef jobManager = make_shared<JobManager>();
  BotManagerRef botManager = make_shared<BotManager>(jobManager);

  setJobManager(jobManager);
  setBotManager(botManager);

  scanAssetsAndExecuteScripts();

  //_gameGrid = new GameGrid();
  //_guiManager = new GuiManager();
  //_jobManager = new JobManager();

  // registerComponent(_camera);
  // registerComponent(_gameGrid);
  // RegisterComponent(_guiManager); Todo: render with quads so depth works
  // registerComponent(_jobManager);

  // Make sure that components get setup
  ComponentDrivenApp::setup();
}

void EngineInit::draw() {
  // clear out the window with black
  gl::clear(Color(0, 0, 0), true);

  gl::enableDepthRead();
  // gl::enableDepthWrite();
  gl::enableAlphaBlending();
  // Make sure that the components get drawn
  ComponentDrivenApp::draw();
}

void EngineInit::keyDown(KeyEvent event) {

  /*if (event.getCode() == KeyEvent::KEY_m) { // TODO: Implement proper control
                                            // system, this is for debugging
    ComponentSet *pSet =
        getState<ComponentSet *>(ToggleSelectionBehaviour::stateKeyName);
    for (GameComponent *tileComp : *pSet) {
      GameTile *tile = (GameTile *)tileComp;
      MiningJob *job = new MiningJob(_gameGrid, tile->getMapPoint(),
                                     _gameGrid->getAssetLoader());
      _jobManager->registerJob(JobRef(job));
    }
    pSet->clear();
  }*/
}

void EngineInit::scanAssetsAndExecuteScripts() {
  cout << "Checking asset definitions..." << endl;

  map<int, vector<ScriptDefRef>> scriptMap;
  filesystem::path rootPath = this->getResourcePath("assets");
  for (filesystem::recursive_directory_iterator end, dir(rootPath); dir != end;
       ++dir) {

    filesystem::path p = dir->path();
    if (p.filename() == "assetdef.yaml") {
      string pDir = p.parent_path().string();
      string assetRef =
          getRelativePath(pDir, rootPath); // Get the relative path
      cout << "--> Loading asset: " << assetRef << endl;
      try {
        AssetDefBaseRef asset = _fileAssetLoader->loadAsset(assetRef);
        cout << "--> --> Found asset: id: " << asset->getId()
             << " type: " << asset->getAssetType() << endl;
        if (asset->getAssetType() == AssetType::Script) {
          ScriptDefRef scriptDef = dynamic_pointer_cast<ScriptDef>(asset);
          scriptMap[scriptDef->getOrder()].push_back(scriptDef);
        }
      }
      catch (const AssetLoadException &e) {
        cout << "--> Error loading asset: " << e.what() << endl;
      }
      catch (const NotImplementedException &e) {
        cout << "--> Error loading asset: Asset loader for this type is not "
                "yet implemented. " << endl;
      }
    }
  }

  cout << "Executing Scripts..." << endl;
  bool errorOccurred = false;

  for (auto &kvp : scriptMap) {
    int order = kvp.first;
    vector<ScriptDefRef> scriptDefs = kvp.second;
    cout << "--> Executing scripts from order: " << order << endl;
    for (ScriptDefRef scriptDef : scriptDefs) {
      cout << "-->     Executing script: " << scriptDef->getAssetRef() << endl;
      int index = 0;
      for (string &script : *scriptDef->getAsset()) {
        try {
          _bindingManager->executeString(script);
        }
        catch (const LuaExecutionException &e) {
          cout << "-->    In filename: " << scriptDef->getFilename(index)
               << endl;
          cout << "-->    Exception when executing script: " << e.what()
               << endl;
          errorOccurred = true;
        }
        index++;
      }
    }
  }

  try {
    // TODO: Wrap in nicer function
    _bindingManager->executeString("LoadScene('/Users/seandawson/Development/"
                                   "spacestationkeeper/assets/scenes/"
                                   "mainscene.yaml')");
  }
  catch (const LuaExecutionException &e) {
    cout << "-->    Exception when loading scene: " << e.what() << endl;
  }
}

string EngineInit::getRelativePath(
    filesystem::path p, filesystem::path root = filesystem::current_path()) {
  return p.string().substr(root.string().length());
}
}

CINDER_APP_NATIVE(BlazeEngine::EngineInit, RendererGl)
