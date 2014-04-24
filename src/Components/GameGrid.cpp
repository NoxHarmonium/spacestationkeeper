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

  _eventManager = parentApp->GetComponentByType<EventManager>();
  assert(_eventManager != nullptr);

  _eventManager->SubscribeBehavior(
      Events::MouseOver, classFilter,
      BehaviourConstructor::Create<HighlightBehaviour>());

  _eventManager->SubscribeBehavior(
      Events::MouseClick, classFilter,
      BehaviourConstructor::Create<ToggleSelectionBehaviour>());

  _eventManager->SubscribeBehavior(
      Events::ComponentSelected, classFilter,
      BehaviourConstructor::Create<HighlightBehaviour, float, ColorAf>(
          1.0f, ColorAf(1.0f, 0.5f, 0.5f, 1.0f)));

  vector<GameTile *> tiles;
  FileAssetLoader *assetLoader = new FileAssetLoader(Utils::getResourcesPath());

  _gameDef = GameDef::GetTestBoard(assetLoader, 10, 10);
  TextureDefRef f;

  // TODO: Cast shared pointers how??
  TextureDefRef asteroidTd =
      assetLoader->LoadAsset<TextureDef>("tilesets/asteroid");

  ShaderDefRef defaultShader =
      assetLoader->LoadAsset<ShaderDef>("shaders/default");

  // TextureDef *corridorTd =
  //    (TextureDef *)assetLoader->LoadAsset("tilesets/corridor");

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
      GameTile *t = new GameTile(material, frameIndex, offset, this->parentApp);
      t->transform.parent = &this->transform;
      _gameMap[MapPoint(i, j)] = t;

      t->setup();
      parentApp->RegisterComponent(t);

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
  this->transform.localPosition.x =
      50.0f + ((sin(ci::app::getElapsedSeconds())) * 25.0f);
}

void GameGrid::draw() {}
