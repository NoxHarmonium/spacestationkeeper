//
//  Neighbourhood.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/06/2014.
//
//

#ifndef SpaceStationKeeper_Neighbourhood_h
#define SpaceStationKeeper_Neighbourhood_h

#include <list>
#include <memory>
#include <map>
#include <stdexcept>
#include <limits>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include "VectorTraits.h"
#include "Transform.h"
#include "SteeringBehaviour.h"
#include "GameComponent.h"

namespace BlazeEngine {
namespace AI {
namespace Steering {

using namespace boost::geometry;
using namespace BlazeEngine::Components;
namespace Components = BlazeEngine::Components;

namespace bgi = boost::geometry::index;
namespace bgm = boost::geometry::model;

template <typename T, typename PointType = ci::Vec2f>
class Neighbourhood : public GameComponent {
public:
  typedef std::shared_ptr<T> TRef;
  typedef std::list<TRef> TList;
  typedef std::pair<PointType, TRef> Value;
  typedef bgi::rtree<Value, bgi::linear<8>> RTree;
  typedef std::set<TRef> RefMap;

  Neighbourhood(int resolution) : _resolution(resolution) {}

  void addNeighbour(TRef neighbour) {
    if (_refMap.count(neighbour) > 0) {
      throw std::runtime_error(
          "This TRef object is already registered in the rTree "
          "at different coordinates. Use refresh or remove "
          "it first.");
    }

    _refMap.insert(neighbour);
  }

  void removeNeighbour(TRef neighbour) {
    if (_refMap.count(neighbour) > 0) {
      _refMap.erase(neighbour);
    }
  }

  TList getNeighbors() {
    refreshNeighbours(); // TODO: Call this only when needed (i.e. updated
                         // transform)

    // TODO: Do we need to convert from set->list. Is there a more efficient
    // way?
    TList list;
    for (TRef neighbour : _refMap) {
      list.push_back(neighbour);
    }
    return list;
  }

  TList getNeighbors(Vec2f center, float radius) {
    refreshNeighbours(); // TODO: Call this only when needed (i.e. updated
                         // transform)

    TList list;
    PointType offset(radius / 2.0f, radius / 2.0f);
    bgm::box<Vec2f> box(center - offset, center + offset);
    _rTree.query(bgi::contains(box), std::back_inserter(list));
    return list;
  }

  TList getNeighbors(Vec2f center, float radius, float angle) {
    refreshNeighbours(); // TODO: Call this only when needed (i.e. updated
                         // transform)

    TList list;
    T x = math<T>::cos(angle);
    T y = math<T>::sin(angle);

    PointType segEnd = center + (Vec2f(x, y) * radius);
    bgm::segment<PointType> segment(center, segEnd);
    _rTree.query(bgi::intersects(segment), std::back_inserter(list));
  }

  void addBehaviour(TRef neighbour, SteeringBehaviourRef behaviour) {
    _behaviourMap[neighbour].push_back(behaviour);
  }

  void removeBehaviour(TRef neighbour, SteeringBehaviourRef behaviour) {
    _behaviourMap[neighbour].remove(behaviour);
  }

  void update(float deltaTime) override {
    for (auto kvp : _behaviourMap) {
      TRef neighbour = kvp.first;
      list<SteeringBehaviourRef> behaviours = kvp.second;

      // Resolution * 2 because of interest and danger
      ContextSlots contextSlots(new float[_resolution * 2]);
      for (SteeringBehaviourRef behaviour : behaviours) {
        behaviour->fillContextSlots(contextSlots);
      }

      // Choose an angle from the provided danger/interest data
      bool success;
      float targetAngle = chooseAngleFromSlots(contextSlots, success);

      if (success) {
        // Apply angle to transform
        float magnitude = _speed * deltaTime;
        Components::TransformRef t = neighbour->getTransformRef();

        t->localPosition.x += cosf(targetAngle) * magnitude;
        t->localPosition.y += cosf(targetAngle) * magnitude;
      }
    }
  }

private:
  void refreshNeighbours() {
    _rTree = RTree();
    for (TRef neighbour : _refMap) {
      Components::TransformRef t = neighbour->getTransformRef();
      // TODO: Need a way to easy cast between cinder vectors
      Value v = make_pair(PointType(t->localPosition.x, t->localPosition.y),
                          neighbour);
      _rTree.insert(v);
    }
  }

  float chooseAngleFromSlots(const ContextSlots &slots, bool &success) {
    int dangerSlotStart = _resolution;
    int dangerSlotEnd = _resolution * 2;
    list<int> availIndexes;

    // For the initial implementation any amount of danger discounts the
    // direction entirely.
    for (int i = dangerSlotStart; i < dangerSlotEnd; i++) {
      float dangerValue = slots[i];
      if (dangerValue < std::numeric_limits<float>::epsilon()) {
        // No danger
        availIndexes.push_back(i);
      }
    }

    int bestIndex = -1;
    float bestInterest = std::numeric_limits<float>::min();
    // Choose direction with greatest interest that is not masked by danger.
    for (int index : availIndexes) {
      float interestValue = slots[index];
      if (interestValue > bestInterest) {
        bestIndex = index;
        bestInterest = interestValue;
      }
    }

    if (bestIndex == -1) {
      // No interesting slot that is not masked by danger. Don't do anything.
      success = false;
      return 0.0f;
    } else {
      success = true;
      // Return angle of best slot in radians
      return ((M_PI * 2) / _resolution) * bestIndex;
    }
  }

  int _resolution;
  float _speed = 1.0f; // (TEMP) Pixels per second of steering targets
  RTree _rTree;
  RefMap _refMap;
  map<TRef, std::list<SteeringBehaviourRef>> _behaviourMap;
};
}
}
}
#endif
