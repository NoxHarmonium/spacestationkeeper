//
//  VectorTraits.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/06/2014.
//
//

#ifndef SpaceStationKeeper_VectorTraits_h
#define SpaceStationKeeper_VectorTraits_h

#include <boost/geometry.hpp>
#include <boost/geometry/core/cs.hpp>

using namespace ci;

namespace boost {
namespace geometry {
// Adapt cinder vector2f to the concept defined by boost geometry
namespace traits {

template <typename CoordinateElemType> struct tag<Vec2<CoordinateElemType>> {
  typedef point_tag type;
};

template <typename CoordinateElemType>
struct coordinate_type<Vec2<CoordinateElemType>> {
  typedef float type;
};

template <typename CoordinateElemType>
struct coordinate_system<Vec2<CoordinateElemType>> {
  typedef cs::cartesian type;
};

template <typename CoordinateElemType>
struct dimension<Vec2<CoordinateElemType>> : boost::mpl::int_<2> {};

template <typename CoordinateElemType, std::size_t Dimension>
struct access<Vec2<CoordinateElemType>, Dimension> {
  static inline CoordinateElemType get(Vec2<CoordinateElemType> const &p) {
#if K == 0
    return p.x;
#elif K == 1
    return p.y;
#else
#error Coord access out of range.
#endif
  }

  static inline void set(Vec2<CoordinateElemType> &p,
                         CoordinateElemType const &value) {
#if K == 0
    p.x = value;
#elif K == 1
    p.y = value;
#else
#error Coord access out of range.
#endif
  }
};
}
}
}

#endif
