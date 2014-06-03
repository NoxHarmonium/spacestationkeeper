//
//  CoordSearch.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/05/2014.
//
//

#include "CoordSearch.h"

// CoordSearchNode::*

bool CoordSearchNode::IsSameState(CoordSearchNode &rhs) {
  return this->pos == rhs.pos;
}

void CoordSearchNode::PrintNodeInfo() { cout << this->pos << endl; }

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float CoordSearchNode::GoalDistanceEstimate(CoordSearchNode &nodeGoal) {
  return this->pos.distance(nodeGoal.pos);
}

bool CoordSearchNode::IsGoal(CoordSearchNode &nodeGoal) {
  // The radius field increases the goal size
  if (_radius > 0) {

    // Sqaure radius // TODO: Make this switchable
    // for (int x = -_radius; x <= _radius; ++x) {
    //  for (int y = -_radius; y <= _radius; ++y) {
    //    if (this->pos == nodeGoal.pos + Vec2i(x, y)) {
    //      return true;
    //    }
    //  }
    //}

    // Plus radius
    for (int x = -_radius; x <= _radius; ++x) {
      if (this->pos == nodeGoal.pos + Vec2i(x, 0)) {
        return true;
      }
    }
    for (int y = -_radius; y <= _radius; ++y) {
      if (this->pos == nodeGoal.pos + Vec2i(0, y)) {
        return true;
      }
    }

  } else {
    return this->pos == nodeGoal.pos;
  }
  return false;
}

// This generates the successors to the given Node. It uses a helper function
// called
// AddSuccessor to give the successors to the AStar class. The A* specific
// initialisation
// is done for each node internally, so here you just set the state information
// that
// is specific to the application
bool CoordSearchNode::GetSuccessors(AStarSearch<CoordSearchNode> *aStarSearch,
                                    CoordSearchNode *parent_node) {

  // push each possible move except allowing the search to go backwards
  Vec2i nextPositions[] = {Vec2i(0, -1), Vec2i(0, 1), Vec2i(-1, 0),
                           Vec2i(1, 0)};

  for (int i = 0; i < 4; i++) {
    Vec2i newPos = this->pos + nextPositions[i];
    if (parent_node == nullptr || newPos != parent_node->pos) {

      if (!isinf(_costFunction(newPos))) {
        CoordSearchNode newNode =
            CoordSearchNode(_costFunction, newPos, _radius);
        // std::cout << "adding successor: " << newNode.pos
        //          << " radius: " << _radius << endl;
        aStarSearch->AddSuccessor(newNode);
      }
    }
  }

  return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float CoordSearchNode::GetCost(CoordSearchNode &successor) {
  return _costFunction(successor.pos);
}

// CoordSearch::*

bool CoordSearch::findPath(Vec2i origin, Vec2i goal, CostFunction costFunction,
                           CoordListRef steps) {
  return findPath(origin, goal, costFunction, steps, 0);
}

bool CoordSearch::findPath(Vec2i origin, Vec2i goal, CostFunction costFunction,
                           CoordListRef steps, int radius) {

  AStarSearch<CoordSearchNode> aStarSearch;

  int SearchState;
  int SearchSteps = 0;
  bool success = false;

  CoordSearchNode originNode = CoordSearchNode(costFunction, origin, radius);
  CoordSearchNode goalNode = CoordSearchNode(costFunction, goal, radius);
  aStarSearch.SetStartAndGoalStates(originNode, goalNode);

  do {
    SearchState = aStarSearch.SearchStep();
    SearchSteps++;
  } while (SearchState == AStarSearch<CoordSearchNode>::SEARCH_STATE_SEARCHING);

  if (SearchState == AStarSearch<CoordSearchNode>::SEARCH_STATE_SUCCEEDED) {
    CoordSearchNode *node = aStarSearch.GetSolutionStart();
    for (;;) {
      node = aStarSearch.GetSolutionNext();

      if (!node) {
        break;
      }

      steps->push_back(node->pos);
    };

    // Once you're done with the solution you can free the nodes up
    aStarSearch.FreeSolutionNodes();
    success = true;

  } else if (SearchState == AStarSearch<CoordSearchNode>::SEARCH_STATE_FAILED) {
    success = false;
  }

  aStarSearch.EnsureMemoryFreed();
  return success;
}