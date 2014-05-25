//
//  Sprite.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 24/05/2014.
//
//

#include "Sprite.h"
#include "GameObject.h"
#include "SimpleMesh.h"
#include "ComponentDrivenApp.h"
#include "Material.h"

// Constructors/Destructors
Sprite::Sprite() : GameComponent() {}

Sprite::Sprite(TextureDefRef texture, int spriteFrame) : GameComponent() {
  this->_spriteTexture = texture;
  this->_spriteFrame = spriteFrame;
}

Sprite::~Sprite() {}

// Getters/Setters

TextureDefRef Sprite::getSpriteTexture() { return _spriteTexture; }

int Sprite::getSpriteFrame() { return _spriteFrame; }

void Sprite::setSpriteTexture(TextureDefRef texture) {
  _spriteTexture = texture;
  refresh();
}

void Sprite::setSpriteFrame(int frame) {
  _spriteFrame = frame;
  refresh();
}

// Methods
void Sprite::setup() {
  _assetLoader = ComponentDrivenApp::Instance()->getAssetLoader();

  if (_spriteTexture != nullptr) {
    if (_spriteFrame < 0 || _spriteFrame >= _spriteTexture->getFrameCount()) {
      cout << "Warning: Frame '" << _spriteFrame
           << "' is out of range for texture '" << _spriteTexture->getAssetRef()
           << "'. Setting to 0." << endl;
      _spriteFrame = 0;
    }

    Rectf dims = Rectf(0, 0, _spriteTexture->getFrameWidth(),
                       _spriteTexture->getFrameHeight());
    Rectf uvCoords = _spriteTexture->getFrameUvCoords(_spriteFrame);

    RenderInfoRef renderer = this->gameObject->renderer;
    renderer->mesh = SimpleMesh::generateQuad(dims, uvCoords);
    MaterialRef mat = make_shared<Material>();

    mat->texture = _spriteTexture;

    cout << "Sprite using tex: " << mat->texture << endl;
    mat->shader = _assetLoader->loadAsset<ShaderDef>(SpriteShader);
    renderer->material = mat;

    if (renderer->getIsBatched()) {
      renderer->invalidateBatch();
      cout << "Invalidate batch because sprite regenerated." << endl;
    }
  }
}

void Sprite::refresh() { setup(); }
