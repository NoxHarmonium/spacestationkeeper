//
//  GridHighlighter.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 7/05/2014.
//
//

#ifndef SpaceStationKeeper_GridHighlighter_h
#define SpaceStationKeeper_GridHighlighter_h

#include "GameComponent.h"
#include "GameGrid.h"

class GridHighlighter : public GameComponent {
public:
  // Constructors/Destructors
  GridHighlighter(GameGrid *_parentGrid);
  ~GridHightlighter();

  // Methods
  /*! Called by the application once every frame. */
  void update();

private:
  // Methods
  /*! Event handler for when a user puts their mouse over a grid coord. */
  void handleGridMouseOverBegin(void *sender, Vec2i coord);
  /*! Event handler for when a user removes their mouse from a grid coord. */
  void handleGridMouseOverEnd(void *sender, Vec2i coord);

  // Fields
  GameGrid *_parentGrid;
};

#endif
