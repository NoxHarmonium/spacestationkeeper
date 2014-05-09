
#include "SpaceStationKeeperApp.h"
#include "AssetLoadException.h"
#include "ScriptDef.h"
#include "LuaExecutionException.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace boost;

void SpaceStationKeeperApp::prepareSettings(Settings *settings) {
  // Utils::printOpenGlVersionInfo();

  settings->setFrameRate(60);
}

void SpaceStationKeeperApp::resize() {
  // setup(); // reset app
  ComponentDrivenApp::resize();
}

void SpaceStationKeeperApp::setup() {
  Utils::printOpenGlVersionInfo();

  _camera = new GameCamera();

  _fileAssetLoader = make_shared<FileAssetLoader>(Utils::getResourcesPath());
  _bindingManager = std::unique_ptr<BindingManager>(new BindingManager());
  _bindingManager->initialiseBindings();
  scanAssetsAndExecuteScripts();

  //_gameGrid = new GameGrid();
  //_guiManager = new GuiManager();
  //_jobManager = new JobManager();

  registerComponent(_camera);
  // registerComponent(_gameGrid);
  // RegisterComponent(_guiManager); Todo: render with quads so depth works
  // registerComponent(_jobManager);

  // Make sure that components get setup
  ComponentDrivenApp::setup();
}

void SpaceStationKeeperApp::draw() {
  // clear out the window with black
  gl::clear(Color(0, 0, 0), true);

  // gl::enableDepthRead();
  // gl::enableDepthWrite();
  gl::enableAlphaBlending();
  // Make sure that the components get drawn
  ComponentDrivenApp::draw();
}

void SpaceStationKeeperApp::keyDown(KeyEvent event) {

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

void SpaceStationKeeperApp::scanAssetsAndExecuteScripts() {
  cout << "Checking asset definitions..." << endl;

  map<int, vector<ScriptDefRef>> scriptMap;
  filesystem::path rootPath =
      Utils::getResourcesPath() / filesystem::path("assets");
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

      try {
        _bindingManager->executeString(*scriptDef->getAsset());
      }
      catch (const LuaExecutionException &e) {
        cout << "-->    Exception when executing script: " << e.what() << endl;
        errorOccurred = true;
      }
    }
  }
}

string SpaceStationKeeperApp::getRelativePath(
    filesystem::path p, filesystem::path root = filesystem::current_path()) {
  return p.string().substr(root.string().length());
}

CINDER_APP_NATIVE(SpaceStationKeeperApp, RendererGl)
