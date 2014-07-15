//
//  BotManager.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 27/05/2014.
//
//

#ifndef SpaceStationKeeper_BotManager_h
#define SpaceStationKeeper_BotManager_h

#include <set>
#include <memory>
#include <functional>
#include "VecComparison.h"
#include "Bot.h"
#include "Job.h"
#include "JobManager.h"
#include "CoordSearch.h"
#include "GameObject.h"
#include <list>

namespace BlazeEngine {
namespace Components {

using namespace std;
using namespace ci;

typedef list<BotRef> BotList;
typedef std::shared_ptr<BotList> BotListRef;

/*! The BotManager is class that helps the autonomous bots coordinate with other
 * bots and navigate. */
class BotManager : public GameComponent {
public:
  // Constructors/Destructors
  BotManager(JobManagerRef jobManager);
  virtual ~BotManager();

  // Methods
  void addCoord(Vec2i coord);
  void removeCoord(Vec2i coord);
  void addBot(BotRef bot);
  void removeBot(BotRef bot);

  float distanceTo(Vec2i source, Vec2i destination);
  float distanceTo(Vec2i source, Vec2i destination, int radius);
  CoordListRef getPath(Vec2i source, Vec2i destination);
  CoordListRef getPath(Vec2i source, Vec2i destination, int radius);
  bool isPassable(Vec2i coord);
  BotListRef getBots(Vec3f center, float radius);

  // GameComponent Methods
  void update(float deltaTime) override;

protected:
  // Fields
  set<Vec2i, VecComparison> _passableCoords;
  set<BotRef> _bots;
  JobManagerRef _jobManager;
  map<BotRef, CoordListRef> _botPathCache;
  float _moveThreshold =
      0.1f; // Amount the bot has to be moving to be considered moving

  // Methods
  std::function<float(Vec2i)> getCostFunction();
  void assignJobs();
  void moveBots();
  bool isSnappedToGrid(Vec3f location);
};

typedef std::shared_ptr<BotManager> BotManagerRef;
}
}

#endif
