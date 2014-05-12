//
//  RenderInfo.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_Renderer_h
#define SpaceStationKeeper_Renderer_h

#include "GameComponent.h"
#include "Transform.h"
#include "BaseMesh.h"
#include "Material.h"
#include "BatchedMesh.h"

// TODO: Rename to renderer
class RenderInfo : public GameComponent {
public:
  // Constructors/Destructors
  RenderInfo();
  ~RenderInfo();

  // Public Fields
  bool renderEnabled = true;
  TransformRef transform;
  BaseMeshRef mesh = nullptr;
  MaterialRef material;

  // Methods
  RenderInfo *clone();
  /*! Gets the transform adjusted bounds of this RenderComponent. */
  virtual AxisAlignedBox3f getBounds();
  /*! The draw call that is executed automatically every frame. */
  void draw();
  /*! Add this RenderComponent to a render batch. */
  void batch(BatchedMeshRef batchedMeshRef);

protected:
  // Methods
  /*! Gets the RenderInfo component of this object. */
  virtual RenderInfo *getRenderInfo() { return this; }

private:
  // Methods
  /*! Called before draw is called. */
  void startDraw(RenderInfo *renderInfo);
  /*! Called after draw is called. */
  void endDraw(RenderInfo *renderInfo);
  /*! Applies a nested transform to the current transform stack. */
  void applyTransfromRecursive(TransformRef t);

  // Fields
  /*! Determines whether this RenderComponent is batched or not. */
  bool _batchMode = false;
  /*! Determines whether this RenderComponent has been added to the batch or
   * not. */
  bool _addedToBatch = false;
  /*! The reference to BatchedMesh used for batching. */
  BatchedMeshRef _batchedMeshRef = nullptr;
  /*! Determines whether the bounds need to be recalculated. */
  bool _boundsDirty = true;
  /*! A cached reference to this object's bounds (invalidated once per frame);
   */
  AxisAlignedBox3f _cachedBounds;
};

typedef std::shared_ptr<RenderInfo> RenderInfoRef;

#endif
