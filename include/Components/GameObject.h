//
//  GameObject.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 7/05/2014.
//
//

#ifndef SpaceStationKeeper_GameObject_h
#define SpaceStationKeeper_GameObject_h

#include <map>
#include "GameComponent.h"
#include "RenderInfo.h"
#include "BindingManager.h"

using namespace ci::app;

// Forward Declarations
class BindingManager;

class GameObject {
public:
  // Constructors/Destructors
  GameObject();
  ~GameObject();

  // Public Fields
  RenderInfo *renderer = nullptr;

  // Methods
  void addComponent(GameComponent *component);
  void removeComponent(GameComponent *component);
  void reassignId(GameComponent *component, string newId);
  GameComponent *getComponent(string id);

  // Event Methods
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

  // Getters/Setters
  virtual RenderInfo *getRenderer(); // Depricated

private:
  // Methods
  map<string, GameComponent *> getRegisteredComponentsCopy();
  void checkIdValidity(string id);

  // Fields
  map<string, GameComponent *> _components;

  BindingManager *_bindingManager = nullptr; // For catching lua exceptions
};

typedef std::shared_ptr<GameObject> GameObjectRef;

#endif
