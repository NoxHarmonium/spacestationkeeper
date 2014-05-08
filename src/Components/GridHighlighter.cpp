//
//  GridHighlighter.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 7/05/2014.
//
//

#include "GridHighlighter.h"

// Constructors/Destructors
GridHighlighter::GridHighlighter(GameGrid *parentGrid)
    : _parentGrid(parentGrid), GameComponent() {}
GridHighlighter::~GridHighlighter() {}

// Methods
void GridHighlighter::update() {}

// Methods
void GridHighlighter::handleGridMouseOverBegin(void *sender, Vec2i coord) {}

void GridHighlighter::handleGridMouseOverEnd(void *sender, Vec2i coord) {}
