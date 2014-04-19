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
#include "HighlightBehaviour.h"
#include <math.h>
#include "ShaderDef.h"

using namespace std;

GameGrid::GameGrid(ComponentDrivenApp *parent) : RenderComponent(parent) {}

void GameGrid::setup() {

  cout << "GameGrid::setup()" << endl;

  vector<GameTile *> tiles;
  FileAssetLoader *assetLoader = new FileAssetLoader(Utils::getResourcesPath());

  MouseOverTrigger *mouseOverTrigger = new MouseOverTrigger(parentApp);
  parentApp->RegisterComponent(mouseOverTrigger);

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

      mouseOverTrigger->RegisterBehaviour(
          t, new HighlightBehaviour(t)); // TODO: component is passed in twice??
      // cout << "create: (" << i << "," << j << "): " << t << endl;
    }
  }
}

void GameGrid::update() {
  this->transform.localPosition.x =
      50.0f + ((sin(ci::app::getElapsedSeconds())) * 25.0f);
}

void GameGrid::draw() {}
