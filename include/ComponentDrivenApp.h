//
//  ComponentManager.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#ifndef SpaceStationKeeper_ComponentManager_h
#define SpaceStationKeeper_ComponentManager_h

#include "pch.h"
#include "GameObject.h"
#include "cinder/app/AppNative.h"
#include <type_traits>
#include "JobManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GameComponent;
template <typename T> class GameComponentT;

class ComponentDrivenApp : public AppNative {

public:
  ComponentDrivenApp();
  ~ComponentDrivenApp();

  //! Registers a component to receive app events
  void registerGameObject(GameObjectRef component);

  //! Deregisters a GameObject and frees the memory used by it.
  void destroyGameObject(GameObjectRef gameObject);

  //! Get a list of currently registered components
  set<GameObjectRef> getGameObjects();

  template <typename T> vector<GameObjectRef> GetComponentsByType() {
    vector<GameObjectRef> selectedGos;
    for (auto &go : _registeredGameObjects) {
      if (dynamic_cast<T>(go) != nullptr) {
        selectedGos.push_back(go);
      }
    }
    return selectedGos;
  }

  template <typename T> std::shared_ptr<T> GetComponentByType() {
    // TODO: Can I make GetComponentsByType() an iterator and then return the
    // first value here?
    for (auto &comp : _registeredGameObjects) {
      std::shared_ptr<T> compT = dynamic_pointer_cast<T>(comp);
      if (compT != nullptr) {
        return compT;
      }
    }
    return nullptr;
  }

  // Get the time in seconds since the last update
  float getDeltaTime() { return _deltaTime; }

  // Sets the asset loader used by this app
  void setAssetLoader(AssetLoaderBase *assetLoader) {
    _assetLoader = assetLoader;
  }
  // Gets the asset loader used by this app
  AssetLoaderBase *getAssetLoader() { return _assetLoader; }

  /*! Sets the job manager used by this app. */
  void setJobManager(std::shared_ptr<JobManager> jobManager) {
    _jobManager = jobManager;
  }

  std::shared_ptr<JobManager> getJobManager() { return _jobManager; }

  //! Override to perform any application setup after the Renderer has been
  // initialized.
  virtual void setup();
  //! Override to perform any application cleanup before exiting.
  virtual void shutdown();

  //! Override to perform any once-per-loop computation.
  virtual void update();
  //! Override to perform any rendering once-per-loop or in response to
  // OS-prompted requests for refreshes.
  virtual void draw();

  //! Override to receive mouse-down events.
  virtual void mouseDown(MouseEvent event);
  //! Override to receive mouse-up events.
  virtual void mouseUp(MouseEvent event);
  //! Override to receive mouse-wheel events.
  virtual void mouseWheel(MouseEvent event);
  //! Override to receive mouse-move events.
  virtual void mouseMove(MouseEvent event);
  //! Override to receive mouse-drag events.
  virtual void mouseDrag(MouseEvent event);

  //! Override to respond to the beginning of a multitouch sequence
  virtual void touchesBegan(TouchEvent event);
  //! Override to respond to movement (drags) during a multitouch sequence
  virtual void touchesMoved(TouchEvent event);
  //! Override to respond to the end of a multitouch sequence
  virtual void touchesEnded(TouchEvent event);

  //! Override to receive key-down events.
  virtual void keyDown(KeyEvent event);
  //! Override to receive key-up events.
  virtual void keyUp(KeyEvent event);
  //! Override to receive window resize events.
  virtual void resize();
  //! Override to receive file-drop events.
  virtual void fileDrop(FileDropEvent event);

  // Templates
  // TODO: Use enable if (p796) to restrict to storing pointers
  template <typename T> void setState(string key, T data) {
    _stateMap[key] = (void *)data;
  }
  template <typename T> T getState(string key) {
    if (_stateMap[key] != nullptr) {
      return (T)_stateMap[key];
    }
    return nullptr;
  }

  // Static Getters/Setters
  static ComponentDrivenApp *Instance();

private:
  // Methods
  set<GameObjectRef> getRegisteredGameObjectsCopy();

  // Fields
  set<GameObjectRef> _registeredGameObjects;
  map<string, void *> _stateMap;
  float _lastElapsedTime = NAN;
  float _deltaTime = 0.0f;
  AssetLoaderBase *_assetLoader;
  std::shared_ptr<JobManager> _jobManager;
  BindingManager *_bindingManager;

  // Static Fields
  static ComponentDrivenApp *_instance;
};

#endif
