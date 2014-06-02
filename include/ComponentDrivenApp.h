//
//  ComponentManager.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#ifndef SpaceStationKeeper_ComponentManager_h
#define SpaceStationKeeper_ComponentManager_h

#include "GameObject.h"
#include "cinder/app/AppNative.h"
#include "GameObject.h"
#include "yaml-cpp/yaml.h"
#include "Utils.h"
#include "ScriptDef.h"
#include "JobManager.h"
#include "BotManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;

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

  // Get the time in seconds since the last update
  float getDeltaTime();

  // TODO: Maybe think of a better way to store these manager classes
  //      This class should be more generic and not have actual game logic in
  // it.
  // Sets the asset loader used by this app
  void setAssetLoader(AssetLoaderBase *assetLoader);

  // Gets the asset loader used by this app
  AssetLoaderBase *getAssetLoader();

  /*! Sets the job manager used by this app. */
  void setJobManager(JobManagerRef jobManager);

  /*! Gets the job manager used by this app. */
  JobManagerRef getJobManager();

  /*! Sets the bot manager used by this app. */
  void setBotManager(BotManagerRef botManager);

  /*! Gets the bot manager used by this app. */
  BotManagerRef getBotManager();

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
  JobManagerRef _jobManager;
  BotManagerRef _botManager;
  BindingManager *_bindingManager;
  GameObjectRef _engineGameObject;

  // Static Fields
  static ComponentDrivenApp *_instance;
};

#endif
