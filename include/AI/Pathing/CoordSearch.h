//
//  CoordSearch.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/05/2014.
//
//

#ifndef SpaceStationKeeper_CoordSearch_h
#define SpaceStationKeeper_CoordSearch_h

#include <stlastar.h>
#include <functional>
#include "Path.h"

namespace BlazeEngine {
namespace AI {
namespace Pathing {

using namespace ci;

typedef Path<float> CoordList;
typedef std::shared_ptr<CoordList> CoordListRef;
typedef std::function<float(Vec2i)> CostFunction;

class CoordSearchNode {
public:
  // Fields
  Vec2i pos;

  // Constructors/Destructor
  CoordSearchNode() {}
  CoordSearchNode(CostFunction costFunction) : _costFunction(costFunction) {}
  CoordSearchNode(CostFunction costFunction, int x, int y)
      : _costFunction(costFunction), pos(Vec2i(x, y)) {}
  CoordSearchNode(CostFunction costFunction, Vec2i pos)
      : _costFunction(costFunction), pos(pos) {}
  CoordSearchNode(CostFunction costFunction, Vec2i pos, int radius)
      : _costFunction(costFunction), pos(pos), _radius(radius) {}

  // AStar Methods
  float GoalDistanceEstimate(CoordSearchNode &nodeGoal);
  bool IsGoal(CoordSearchNode &nodeGoal);
  bool GetSuccessors(AStarSearch<CoordSearchNode> *astarsearch,
                     CoordSearchNode *parent_node);
  float GetCost(CoordSearchNode &successor);
  bool IsSameState(CoordSearchNode &rhs);

  // Util Methods
  void PrintNodeInfo();

private:
  CostFunction _costFunction;
  int _radius = 0;
};

class CoordSearch {
public:
  static bool findPath(Vec2i origin, Vec2i goal, CostFunction costFunction,
                       CoordListRef steps);
  static bool findPath(Vec2i origin, Vec2i goal, CostFunction costFunction,
                       CoordListRef steps, int radius);
};
}
}
}
#endif
