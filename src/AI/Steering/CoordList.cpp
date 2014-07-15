//
//  CoordList.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 6/06/2014.
//
//

//#include "CoordList.h"
//#include <stdexcept>
//#include <map>

// using namespace ci;

// CoordList::CoordList(float radius) : _radius(radius) {}
// CoordList::~CoordList() {}

// Vec2f CoordList::getPointFromPathDistance(float pathDistance) {}

// float CoordList::getPathDistanceFromPoint(Vec2f point) {}

// bool CoordList::pointIsInsidePath(Vec2f point) {}

// std::list<Vec2i> CoordList::getClosestNCoords(Vec2f point, int n) {}

/* if (this->size() < 2) {
 throw std::runtime_error(
 "Cannot do path calculations with only one point.");
 }

 std::map<float, Vec2i> coordMap;
 for (Vec2i &coord : *this) {
 coordMap[point.distance(coord)] = coord;
 }

 list<Vec2i> outList;
 int count = 0;
 for (auto &kvp : coordMap) {
 outList.push_back(kvp.second);
 if (count++ > n) {
 break;
 }
 }
 return outList;*/

/*
 if (this->size() < 2) {
 throw std::runtime_error(
 "Cannot do path calculations with only one point.");
 }

 float totalD = 0.0f;
 Vec2f currCoord;
 Vec2f prevCoord;
 int count = 0;
 float d;

 for (Vec2i &coord : *this) {
 prevCoord = currCoord;
 currCoord = Vec2f(coord);

 d = coord.distance(prevCoord);

 if (totalD + d > pathDistance) {
 break;
 }

 if (count > 0) {
 totalD += d;
 }

 ++count;
 }

 float min = totalD;
 float max = (totalD + d);
 float mult = (max - pathDistance) / (max - min);

 Vec2f diff = (currCoord - prevCoord) * mult;
 return prevCoord + diff;*/