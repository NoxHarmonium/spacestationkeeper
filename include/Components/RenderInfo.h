//
//  RenderInfo.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 26/04/2014.
//
//

#ifndef SpaceStationKeeper_Renderer_h
#define SpaceStationKeeper_Renderer_h

#include "pch.h"
#include "GameComponent.h"
#include "Transform.h"
#include "BaseMesh.h"
#include "Material.h"
#include "BatchedMesh.h"
#include "BatchInfo.h"

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
  /*! Called when the properties of this object have changed and the batch needs
   * to be regenerated to reflect them. */
  void invalidateBatch();

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
  /*! Sets the values of _batchInfoRef to reflect this current object. */
  void updateBatchInfo();

  // Fields
  /*! Determines whether this RenderComponent is batched or not. */
  bool _batchMode = false;
  /*! The reference to BatchedMesh used for batching. */
  BatchedMeshRef _batchedMeshRef = nullptr;
  /*! A reference to the information sent to the batcher. If this is modified
   * the batcher should be notified to regenerate the required batches. */
  BatchInfoRef _batchInfoRef = nullptr;
  /*! Determines whether the bounds need to be recalculated. */
  bool _boundsDirty = true;
  /*! A cached reference to this object's bounds (invalidated once per frame);
   */
  AxisAlignedBox3f _cachedBounds;
};

typedef std::shared_ptr<RenderInfo> RenderInfoRef;

#endif
