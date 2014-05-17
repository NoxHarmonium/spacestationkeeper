//
//  BatchInfo.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 16/05/2014.
//
//

#ifndef SpaceStationKeeper_BatchInfo_h
#define SpaceStationKeeper_BatchInfo_h

#include "pch.h"
#include <memory>

// Forward decs
class Material;
class BaseMesh;
class Transform;
typedef std::shared_ptr<Material> MaterialRef;
typedef std::shared_ptr<BaseMesh> BaseMeshRef;
typedef std::shared_ptr<Transform> TransformRef;

class BatchInfo {
public:
  BatchInfo() {};
  ~BatchInfo() {};

  MaterialRef material;
  BaseMeshRef mesh;
  TransformRef transform;
};

typedef std::shared_ptr<BatchInfo> BatchInfoRef;

#endif
