//
//  AnimationDef.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 21/05/2014.
//
//

#ifndef SpaceStationKeeper_AnimationDef_h
#define SpaceStationKeeper_AnimationDef_h

#include "TextureDef.h"

using namespace std;

class AnimationDef : public TextureDef {
public:
  // Constructors/Destructors
  AnimationDef(Node node, string animationName);
  virtual ~AnimationDef();

  // Getters/Setters
  /*! Gets the name of the animation. */
  string getName();
  /*! Gets the frame that the animation starts on. */
  int getFrameStart();
  /*! Gets the frame that the animation stops on. */
  int getFrameEnd();
  /*! Gets the rate (in fps) that the animation should play by default. */
  float getRate();
  /*! Gets if the animation should loop by default. */
  bool getLoop();
  /*! Gets if the TextureDef can be used for animation. */
  bool getIsAnimated();

  // Static Methods
  /*! Constructs an instance of TextureDef from a loaded YAML node. This should
   * be called by an AssetLoader and not directly through scripts. */
  static std::shared_ptr<AnimationDef> FromYamlNode(Node node,
                                                    string animationName);

private:
  // Fields
  /*! The name of the animation. */
  string _name;
  /*! The frame that the animation starts on. */
  int _frameStart;
  /*! The frame that the animation stops on. */
  int _frameEnd;
  /*! The rate (in fps) that the animation should play by default. */
  float _rate;
  /*! Determines if the animation should loop by default. */
  bool _loop;
};

/*! A shared pointer reference to a TextureDef object. */
typedef std::shared_ptr<AnimationDef> AnimationDefRef;

/*! A specilization of GetAssetType to allow compile time definition of this
 * classes AssetType. */
template <> struct GetAssetType<AnimationDef> {
  static const AssetType value = AssetType::Animation;
};

#endif
