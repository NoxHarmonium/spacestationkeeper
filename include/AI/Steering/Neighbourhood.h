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
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include "VectorTraits.h"

namespace BlazeEngine {
namespace AI {
namespace Steering {

using namespace boost::geometry;
namespace bgi = boost::geometry::index;
namespace bgm = boost::geometry::model;

template <typename T, typename PointType = ci::Vec2f> class Neighbourhood {
  typedef std::shared_ptr<T> TRef;
  typedef std::list<TRef> TList;
  typedef std::pair<PointType, TRef> Value;
  typedef bgi::rtree<Value, bgi::linear<8>> RTree;
  typedef std::map<TRef, Value> RefMap;

public:
  void AddNeighbour(PointType point, TRef neighbour) {
    if (_refMap.count(neighbour) > 0) {
      throw std::runtime_error(
          "This TRef object is already registered in the rTree "
          "at different coordinates. Use refresh or remove "
          "it first.");
    }

    Value v = make_pair(point, neighbour);
    _refMap.insert(neighbour);
    _rTree.insert(v);
  }

  void RefreshNeighbour(PointType point, TRef neighbour) {
    if (_refMap.count(neighbour) == 0) {
      throw std::runtime_error("This TRef object is not registered in the "
                               "rTree. Use AddNeighbour() to add it first.");
    }

    // TODO:
    // Very nieve but only way I know how at the moment.
    // Later I might have a more efficient way to reindex moving points
    RemoveNeighbour(neighbour);
    AddNeighbour(point, neighbour);
  }

  void RemoveNeighbour(TRef neighbour) {
    if (_refMap.count(neighbour) > 0) {
      Value v = _refMap[neighbour];
      _rTree.remove(v);
      _refMap.remove(neighbour);
    }
  }

  TList getNeighbors() {
    TList list;
    for (Value &v : _rTree) {
      list.insert(v.second);
    }
    return list;
  }

  TList getNeighbors(Vec2f center, float radius) {
    TList list;
    PointType offset(radius / 2.0f, radius / 2.0f);
    bgm::box<Vec2f> box(center - offset, center + offset);
    _rTree.query(bgi::contains(box), std::back_inserter(list));
    return list;
  }

  TList getNeighbors(Vec2f center, float radius, float angle) {
    TList list;
    T x = math<T>::cos(angle);
    T y = math<T>::sin(angle);

    PointType segEnd = center + (Vec2f(x, y) * radius);
    bgm::segment<PointType> segment(center, segEnd);
    _rTree.query(bgi::intersects(segment), std::back_inserter(list));
  }

private:
  RTree _rTree;
  RefMap _refMap;
};
}
}
}
#endif
