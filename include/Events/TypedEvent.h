//
//  TypedEvent.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/05/2014.
//
//

#ifndef SpaceStationKeeper_TypedEvent_h
#define SpaceStationKeeper_TypedEvent_h

#include <functional>
#include <map>

using namespace std;

// Enums
/*! Determines whether an event is transient or continuous. */
enum class EventType {
  /*! A transient event only has a beginning. (i.e. MouseClick) */
  Transient,
  /*! A continous event has a beginning and an end. (i.e. MouseOver) */
  Continuous
};

template <typename... T> class TypedEvent {
public:
  typedef std::function<void(void *, T...)> TypedEventHandler;

  // Constructors/Destructors
  TypedEvent() {}
  TypedEvent(EventType eventType) : _eventType(eventType) {}
  virtual ~TypedEvent() {}

  // Methods
  /*! Attach a function to this event. When the event is triggered the function
   will be executed. Returns an id which can be used to unsubscribe. */
  int Subscribe(TypedEventHandler onBegin) {
    ++_currentEventId;

    _onBeginHandlers[_currentEventId] = onBegin;
    return _currentEventId;
  }

  /*! Attach a function to this event. When the event is triggered the function
   will be executed. Returns an id which can be used to unsubscribe. */
  int Subscribe(TypedEventHandler onBegin, TypedEventHandler onEnd) {
    if (_eventType == EventType::Transient) {
      throw new runtime_error(
          "You cannot attach an onEnd handler to a transient event.");
    }

    ++_currentEventId;

    _onBeginHandlers[_currentEventId] = onBegin;
    _onEndHandlers[_currentEventId] = onEnd;

    return _currentEventId;
  }

  /*! Disattaches a function from this event. The subscription id is returned
   * when subscribing to the event. */
  void Unsubscribe(int subscriptionId) {
    _onBeginHandlers.erase(subscriptionId);
    if (_eventType == EventType::Continuous) {
      _onEndHandlers.erase(subscriptionId);
    }
  }

  /*! Triggers this event causing all subscribed onBegin handlers to execute. */
  void Begin(void *sender, T... args) {
    for (auto &kvp : _onBeginHandlers) {
      TypedEventHandler f = kvp.second;
      f(sender, args...);
    }
  }

  /*! Triggers this event causing all subscribed onEnd handlers to execute. */
  void End(void *sender, T... args) {
    for (auto &kvp : _onEndHandlers) {
      TypedEventHandler f = kvp.second;
      f(sender, args...);
    }
  }

private:
  /*! A vector containing all the handlers fired on begin. */
  map<int, TypedEventHandler> _onBeginHandlers;
  /*! A vector containing all the handlers fired on end. */
  map<int, TypedEventHandler> _onEndHandlers;
  /*! Stores the type of this event. */
  EventType _eventType = EventType::Transient;
  /*! The current unique subscription id that will be returned to subscribers.
   */
  int _currentEventId = 0;
};

#endif
