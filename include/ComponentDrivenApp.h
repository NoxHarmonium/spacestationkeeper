//
//  ComponentManager.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#ifndef SpaceStationKeeper_ComponentManager_h
#define SpaceStationKeeper_ComponentManager_h

#include "cinder/app/AppNative.h"
#include <type_traits>

using namespace ci;
using namespace ci::app;
using namespace std;

class GameComponent;
template <typename T> class GameComponentT;

class ComponentDrivenApp : public AppNative {

public:
  //! Registers a component to receive app events
  void registerComponent(GameComponent *component);

  //! Get a list of currently registered components
  vector<GameComponent *> getComponents();

  template <typename T> vector<GameComponent *> GetComponentsByType() {
    vector<GameComponent *> selectedComps;
    for (auto &comp : _registeredComponents) {
      if (dynamic_cast<T>(comp) != nullptr) {
        selectedComps.push_back(comp);
      }
    }
    return selectedComps;
  }

  template <typename T> T *GetComponentByType() {
    // TODO: Can I make GetComponentsByType() an iterator and then return the
    // first value here?
    for (auto &comp : _registeredComponents) {
      T *compT = dynamic_cast<T *>(comp);
      if (compT != nullptr) {
        return compT;
      }
    }
    return nullptr;
  }

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

private:
  vector<GameComponent *> getRegisteredComponentsCopy();
  vector<GameComponent *> _registeredComponents;
  map<string, void *> _stateMap;
};

#endif
