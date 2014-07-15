//
//  GameGraph.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 9/06/2014.
//
//

#ifndef SpaceStationKeeper_GameGraph_h
#define SpaceStationKeeper_GameGraph_h

namespace BlazeEngine {
namespace AI {
namespace Pathing {

#include <set>
#include <list>

#include <boost/graph/adjacency_list.hpp>
  

template <typename CoordinateType> class GameGraph {

  typedef adjacency_list<vecS, listS, undirectedS, no_property,
                         property<edge_weight_t, cost>> Graph;
  typedef property_map<Graph, edge_weight_t>::type WeightMap;
  typedef Graph::vertex_descriptor Vertex;
  typedef Graph::edge_descriptor EdgeDescriptor;
  typedef std::pair<CoordinateType, CoordinateType> Edge;

public:
  // Constructors/Destructors
  GameGraph();
  ~GameGraph();

  // Methods
  void AddCoord(CoordinateType coord) {
    _vertexSet.insert(coord);
    list<CoordinateType> adjacentCoords = {
        coord + CoordinateType(-1, -1), coord + CoordinateType(-1, 1),
        coord + CoordinateType(1, -1), coord + CoordinateType(-1, -1)};

    for (CoordinateType &c : adjacentCoords) {
      if (_vertexSet.count(c) > 0) {
        add_edge(coord, c, _graph);
      }
    }
  }

  void RemoveCoord(CoordType coord) {
    if (_vertexSet.count(coord) > 0) {
      remove_vertex(coord, _graph);
      _vertexSet.erase(coord);
    }
  }

private:
  Graph _graph;
  set<CoordinateType> _vertexSet;
};
}
}
}
#endif
