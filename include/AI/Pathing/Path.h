//
//  Path.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/06/2014.
//
//

#ifndef SpaceStationKeeper_Path_h
#define SpaceStationKeeper_Path_h

#include <list>
#include <vector>
#include "NotImplementedException.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include "VectorTraits.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ci;

namespace BlazeEngine {
namespace AI {
namespace Pathing {

namespace geo = boost::geometry;
namespace bgm = geo::model;

template <typename NumericType = float>
class Path : public std::list<Vec2<NumericType>> {
  typedef Vec2<NumericType> PointType;
  typedef PointType Value;
  typedef bgm::segment<PointType> Segment;
  typedef bgm::linestring<PointType> LineString;

public:
  Path() {
    _cumulativeDistance = {0.0};
  }
  virtual ~Path() {}

  void appendCoord(PointType coord) {
    _lineString.push_back(coord);
    int coordCount = _lineString.size();
    if (coordCount > 1) {
      PointType prevCoord = _lineString[coordCount - 1];
      float prevDistance = _cumulativeDistance.back();
      float cDistance = prevDistance + geo::distance(prevCoord, coord);
      _cumulativeDistance.push_back(cDistance);
    }
  }

  PointType getPointFromPathDistance(NumericType distance) {
    // Calculate a point along a path at a specific distance.
    int lowerIndex = std::lower_bound(_cumulativeDistance.begin(),
                                      _cumulativeDistance.end(), distance);
    // Not just lowerIndex + 1 because could be the same
    int upperIndex = std::upper_bound(_cumulativeDistance.begin(),
                                      _cumulativeDistance.end(), distance);
    NumericType lowerValue = _cumulativeDistance[lowerIndex];
    NumericType upperValue = _cumulativeDistance[upperIndex];

    NumericType splitValue =
        (upperValue - distance) / (upperValue - lowerValue);
    PointType lowerPoint = _lineString[lowerIndex];
    PointType upperPoint = _lineString[upperIndex];

    PointType diff = (upperPoint - lowerPoint) * splitValue;
    return lowerPoint + diff;
  }

  float getPathDistanceFromPoint(PointType targetPoint) {
    if (_lineString.size() < 2) {
      return 0.0f;
    }

    NumericType minD = std::numeric_limits<NumericType>::max();
    PointType lastPoint;
    PointType closestPoint;
    PointType closestPointDir;
    float pathLength = -1.0f;
    int index = 0;

    for (PointType &p : _lineString) {
      float d = geo::comparable_distance(p, targetPoint);

      Vec2f targetDir = (targetPoint - p).normalized();

      if (index > 0 && d < minD) {
        minD = d;
        closestPoint = p;

        PointType pathDir = p - lastPoint;
        pathDir.normalize();

        float angleBtwn =
            M_PI - atan2(targetDir.y - targetDir.y, pathDir.x - pathDir.x);

        bool sameDir = angleBtwn < (M_PI / 2.0);

        if (sameDir) {
          pathLength = _cumulativeDistance[index] + d;
        } else {
          pathLength = _cumulativeDistance[index] - d;
        }

        index++;
      }
      lastPoint = p;
    }

    return pathLength;
  }

  bool pointIsInsidePath(PointType point) {
    throw Exceptions::NotImplementedException();
  }

  std::list<PointType> getClosestNCoords(PointType point, int n) {
    throw Exceptions::NotImplementedException();
  }

  float getTotalDistance() { return _cumulativeDistance.back(); }

private:
  NumericType _radius;
  LineString _lineString;
  std::vector<NumericType> _cumulativeDistance;
};

typedef std::shared_ptr<Path<>> PathRef;
}
}
}

#endif
