//
//  GameComponent.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#ifndef SpaceStationKeeper_GameComponent_h
#define SpaceStationKeeper_GameComponent_h

#include <boost/uuid/random_generator.hpp>

using namespace ci;
using namespace ci::app;
using namespace std;

// Forwards Decs
class GameObject;
typedef shared_ptr<GameObject> GameObjectRef;

struct SerialisedField {
  SerialisedField() {}
  SerialisedField(string name, string type, bool required)
      : name(name), type(type), required(required), useAccessors(false) {}
  SerialisedField(string name, string type, string getterName,
                  string setterName, bool required)
      : name(name), type(type), getterName(getterName), setterName(setterName),
        required(required), useAccessors(true) {}

  string name;
  string type;
  string getterName;
  string setterName;
  bool required = true;
  bool useAccessors = false;
};

typedef std::shared_ptr<SerialisedField> SerialisedFieldRef;
typedef vector<SerialisedFieldRef> SerialisedFieldList;
typedef std::shared_ptr<SerialisedFieldList> SerialisedFieldListRef;

//! A game component is a child of an app which has all the app events forwarded
// to it
class GameComponent {
public:
  //! Construct a new GameComponent
  GameComponent();
  GameComponent(string id);

  // Fields
  bool enabled = true;
  GameObject *gameObject = nullptr;

  // Cinder Event Methods

  //! Setup the component
  virtual void setup() {}
  //! Override to perform any component cleanup before exiting.
  virtual void shutdown() {}

  //! Override to perform any once-per-loop computation.
  virtual void update(float deltaTime) {}
  //! Override to perform any rendering once-per-loop or in response to
  // OS-prompted requests for refreshes.
  virtual void draw() {}

  //! Override to receive mouse-down events.
  virtual void mouseDown(MouseEvent event) {}
  //! Override to receive mouse-up events.
  virtual void mouseUp(MouseEvent event) {}
  //! Override to receive mouse-wheel events.
  virtual void mouseWheel(MouseEvent event) {}
  //! Override to receive mouse-move events.
  virtual void mouseMove(MouseEvent event) {}
  //! Override to receive mouse-drag events.
  virtual void mouseDrag(MouseEvent event) {}

  //! Override to respond to the beginning of a multitouch sequence
  virtual void touchesBegan(TouchEvent event) {}
  //! Override to respond to movement (drags) during a multitouch sequence
  virtual void touchesMoved(TouchEvent event) {}
  //! Override to respond to the end of a multitouch sequence
  virtual void touchesEnded(TouchEvent event) {}

  //! Override to receive key-down events.
  virtual void keyDown(KeyEvent event) {}
  //! Override to receive key-up events.
  virtual void keyUp(KeyEvent event) {}
  //! Override to receive window resize events.
  virtual void resize() {}
  //! Override to receive file-drop events.
  virtual void fileDrop(FileDropEvent event) {}

  // Getters/Setters
  //! Gets a list of fields that are marked for auto serialisation.
  SerialisedFieldListRef getSerialisedFields();

  // Methods
  //! Mark a field for auto serialisation.
  void serialiseField(string name, string type);
  //! Mark a field for auto serialisation and specify if the field is required.
  void serialiseField(string name, string type, bool required);
  //! Mark a field for auto serialisation and specify what methods Lua should
  // call to access the field.
  void serialiseField(string name, string type, string getterName,
                      string setterName);
  //! Mark a field for auto serialisation and specify what methods Lua should
  // call to access the field and specify if the field is required.
  void serialiseField(string name, string type, string getterName,
                      string setterName, bool required);

  // Static Methods
  /*! Gets the unique ID of this component. */
  static string getId(std::shared_ptr<GameComponent> component);
  /*! Sets the unique ID of this component. */
  static void setId(std::shared_ptr<GameComponent> component, string id);

private:
  // Fields
  string _id;
  SerialisedFieldListRef _serialisedFields;

  // Static fields
  static boost::uuids::random_generator _uuidGenerator;
};

typedef std::shared_ptr<GameComponent> GameComponentRef;

#endif
