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
#include "VecComparison.h"
#include "Bot.h"
#include "Job.h"
#include "JobManager.h"

using namespace std;
using namespace ci;

/*! The BotManager is class that helps the autonomous bots coordinate with other
 * bots and navigate. */
class BotManager {
public:
  // Constructors/Destructors
  BotManager(JobManagerRef jobManager);
  virtual ~BotManager();

  // Methods
  void addCoord(Vec2i coord);
  void removeCoord(Vec2i coord);
  void addBot(BotRef bot);
  void removeBot(BotRef bot);

protected:
  set<Vec2i, VecComparison> _passableCoords;
  set<BotRef> _bots;
  JobManagerRef _jobManager;
};

typedef std::shared_ptr<BotManager> BotManagerRef;

#endif
