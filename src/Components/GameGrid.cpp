//
//  GameGrid.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 15/03/2014.
//
//

#include "GameGrid.h"
#include "FileAssetLoader.h"
#include "MouseOverTrigger.h"
#include "BehaviourConstructor.h"
#include "HighlightBehaviour.h"
#include "ToggleSelectionBehaviour.h"
#include <math.h>
#include "ShaderDef.h"
#include "EventManager.h"
#include "Events.h"

using namespace std;

GameGrid::GameGrid(ComponentDrivenApp *parent) : RenderComponent(parent) {}

void GameGrid::setup() {

  cout << "GameGrid::setup()" << endl;

  string classFilter = "asteroidRock";

  _eventManager = _parentApp->GetComponentByType<EventManager>();
  assert(_eventManager != nullptr);

  _eventManager->subscribeBehavior(
      Events::MouseOver, classFilter,
      BehaviourConstructor::Create<HighlightBehaviour>());

  _eventManager->subscribeBehavior(
      Events::MouseClick, classFilter,
      BehaviourConstructor::Create<ToggleSelectionBehaviour>());

  _eventManager->subscribeBehavior(
      Events::ComponentSelected, classFilter,
      BehaviourConstructor::Create<HighlightBehaviour, float, ColorAf>(
          1.0f, ColorAf(1.0f, 0.5f, 0.5f, 1.0f)));

  vector<GameTile *> tiles;
  _assetLoader = new FileAssetLoader(Utils::getResourcesPath());

  _gameDef = GameDef::getTestBoard(_assetLoader, 10, 10);
  TextureDefRef f;

  // TODO: Cast shared pointers how??
  TextureDefRef asteroidTd =
      _assetLoader->loadAsset<TextureDef>("tilesets/asteroid");

  ShaderDefRef defaultShader =
      _assetLoader->loadAsset<ShaderDef>("shaders/default");

  // TextureDef *corridorTd =
  //    (TextureDef *)assetLoader->loadAsset("tilesets/corridor");

  // int frameCount = asteroidTd->getFrameCount();

  for (int i = 0; i < _gameDef.getWidth(); i++) {
    for (int j = 0; j < _gameDef.getHeight(); j++) {
      MaterialRef material = make_shared<Material>();
      material->shader = defaultShader;
      material->texture = asteroidTd;
      // TODO: Should there be one material ref and each tile gets its own
      // brightness/baseColor somehow? I think unity does something strange like
      // copy materials on access. Investigate

      int frameIndex = asteroidTd->getFrameFromPassibility(
          _gameDef.getMapSquare(MapPoint(i, j)).getPassability());
      Vec3f offset = Vec3f(i * asteroidTd->getFrameWidth(),
                           j * asteroidTd->getFrameHeight(), 0.0f);
      GameTile *t = new GameTile(material, MapPoint(i, j), frameIndex, offset,
                                 this->_parentApp);
      t->transform->parent = this->transform;
      _gameMap[MapPoint(i, j)] = t;

      t->setup();
      _parentApp->registerComponent(t);

      t->classFilter = classFilter;
      t->setEventManager(_eventManager);

      // mouseOverTrigger->RegisterBehaviour(
      //    t, new HighlightBehaviour(t)); // TODO: component is passed in
      // twice??
      // cout << "create: (" << i << "," << j << "): " << t << endl;
    }
  }
}

void GameGrid::update() {
  this->transform->localPosition.x =
      50.0f + ((sin(ci::app::getElapsedSeconds())) * 25.0f);
}

void GameGrid::draw() {}

void GameGrid::fixTileFrameFromAdjacent(MapPoint point) {
  if (!isPassable(point)) {
    return;
  }

  Passibility p;
  ThreeInt adjacentChecks[] = {make_tuple(-1, 0, E_Passibility::West),
                               make_tuple(0, -1, E_Passibility::North),
                               make_tuple(1, 0, E_Passibility::East),
                               make_tuple(0, 1, E_Passibility::South)};

  for (auto t : adjacentChecks) {
    if (isPassable(MapPoint(point.x + get<0>(t), point.y + get<1>(t)))) {
      p.setFlag(get<2>(t));
    }
  }

  cout << "GameGrid::fixTileFrameFromAdjacent(): p:" << p << endl;

  GameTile *tile = getTile(point);
  if (tile != nullptr) {
    TextureDefRef tDef = tile->material->texture;
    int frame = tDef->getFrameFromPassibility(p);
    tile->setTileIndex(frame);
  }
}

void GameGrid::fixMultipleTileFrameFromAdjacent(MapPoint point) {
  fixTileFrameFromAdjacent(point);
  fixTileFrameFromAdjacent(MapPoint(point.x - 1, point.y));
  fixTileFrameFromAdjacent(MapPoint(point.x, point.y - 1));
  fixTileFrameFromAdjacent(MapPoint(point.x + 1, point.y));
  fixTileFrameFromAdjacent(MapPoint(point.x, point.y + 1));
}

bool GameGrid::isPassable(MapPoint point) {
  bool canPass = _gameMap.count(point) > 0 &&
                 _gameMap[point]->material->texture->getCanWalk();
  return canPass;
}
