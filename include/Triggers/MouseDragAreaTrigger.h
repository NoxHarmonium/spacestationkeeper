//
//  MouseDragAreaTrigger.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 4/05/2014.
//
//

#ifndef SpaceStationKeeper_MouseDragAreaTrigger_h
#define SpaceStationKeeper_MouseDragAreaTrigger_h

#include <map>
#include "Trigger.h"
#include "GameComponent.h"
#include "Utils.h"

class MouseDragAreaTrigger : public Trigger, public GameComponent {
public:
  // Should match these with MouseClickTrigger so this is triggered
  // when the click event expires

  static constexpr float moveThreshold = 10.0f;
  static constexpr float timeThreshold = 0.33f;

  MouseDragAreaTrigger(ComponentDrivenApp *parentApp, bool triggerOnRelease);

  bool isActive(RenderComponent *renderComponent);

  // GameComponent Methods
  void mouseDown(MouseEvent event);
  void mouseUp(MouseEvent event);
  void mouseDrag(MouseEvent event);
  void update();

private:
  Vec2f _mouseDownPoint;
  Vec2f _currentMousePoint;
  bool _doDragTrigger = false;
  bool _mouseDown = false;
  float _mouseDownTime = 0.0f;
  Rectf _dragArea;
  bool _triggerOnRelease;
  bool _triggered = false;
};

#endif
