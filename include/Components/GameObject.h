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
#include "BindingManager.h"
#include "Renderable.h"

namespace BlazeEngine {
namespace Binding {
// Forward Declarations
class BindingManager;
}
}

namespace BlazeEngine {
namespace Components {

using namespace ci::app;
using namespace BlazeEngine::Binding;

typedef vector<GameComponentRef> GameComponentList;
typedef std::shared_ptr<GameComponentList> GameComponentListRef;

class GameObject : public Renderable {
public:
  // Constructors/Destructors
  GameObject();
  ~GameObject();

  // Methods
  void reassignId(GameComponentRef component, string newId);
  GameComponentRef getComponent(string id);
  void refreshComponentList();
  GameComponentListRef getComponentList();

  // Event Methods
  //! Override to perform any application cleanup before exiting.
  virtual void shutdown();

  //! Override to perform any once-per-loop computation.
  virtual void update(float deltaTime);
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
  virtual RenderInfoRef getRenderer(); // Depricated
  string getId();
  void setId(string id);

  // These are static because an object can't get a reference to it's own
  // shared_ptr object with the 'this' keyword.
  // TODO: Make this more intutive, users will not expect this to be a static
  // method at all. There has to be a way.
  static void addComponent(GameObjectRef gameObject,
                           GameComponentRef component);
  static void removeComponent(GameObjectRef gameObject,
                              GameComponentRef component);

private:
  // Methods
  map<string, GameComponentRef> getRegisteredComponentsCopy();
  void checkIdValidity(string id);

  // Fields
  bool _componentListDirty = true;
  map<string, GameComponentRef> _componentMap;
  string _id;
  vector<GameComponentRef> _setupQueue;
  GameComponentListRef _componentList;

  BindingManager *_bindingManager = nullptr; // For catching lua exceptions

  // Static Fields
  static boost::uuids::random_generator _uuidGenerator;
};

typedef std::shared_ptr<GameObject> GameObjectRef;
}
}

#endif
