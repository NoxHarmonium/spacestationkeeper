//
//  RenderComponent.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 12/04/2014.
//
//

#ifndef SpaceStationKeeper_RenderComponent_h
#define SpaceStationKeeper_RenderComponent_h

#include "GameComponent.h"
#include "BatchedMesh.h"
#include "RenderInfo.h"

class RenderComponent : public GameComponent, public RenderInfo {
public:
  // Constructors/Destructors
  RenderComponent(ComponentDrivenApp *parent);
  ~RenderComponent();

  // Methods
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
};

#endif
