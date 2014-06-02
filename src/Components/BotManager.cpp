//
//  BotManager.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 27/05/2014.
//
//

#include "BotManager.h"
#include "CoordSearch.h"

BotManager::BotManager(JobManagerRef jobManager) : _jobManager(jobManager) {}

BotManager::~BotManager() {}

void BotManager::addCoord(Vec2i coord) { _passableCoords.insert(coord); }

void BotManager::removeCoord(Vec2i coord) { _passableCoords.erase(coord); }

void BotManager::addBot(BotRef bot) { _bots.insert(bot); }

void BotManager::removeBot(BotRef bot) { _bots.erase(bot); }

float BotManager::distanceTo(Vec2i source, Vec2i destination) {
  return (float)getPath(source, destination)->size();
}

float BotManager::distanceTo(Vec2i source, Vec2i destination, int radius) {
  return (float)getPath(source, destination, radius)->size();
}

CoordListRef BotManager::getPath(Vec2i source, Vec2i destination) {
  CoordListRef steps = make_shared<CoordList>();
  CoordSearch::findPath(source, destination, getCostFunction(), steps);
  return steps;
}

CoordListRef BotManager::getPath(Vec2i source, Vec2i destination, int radius) {
  CoordListRef steps = make_shared<CoordList>();
  CoordSearch::findPath(source, destination, getCostFunction(), steps, radius);
  return steps;
}

bool BotManager::isPassable(Vec2i coord) {
  return (_passableCoords.count(coord) > 0);
}

void BotManager::update(float deltaTime) {
  vector<JobRef> pendingJobs = _jobManager->getPendingJobs();

  vector<tuple<float, BotRef, JobRef>> candidateBots;

  for (BotRef bot : _bots) {
    if (bot->canAcceptJobs()) {
      for (JobRef job : pendingJobs) {
        float d = distanceTo(bot->getCoord(), job->getEndLocation());
        candidateBots.push_back(make_tuple(d, bot, job));
      }
    }
  }

  if (candidateBots.size() == 0) {
    return;
  }

  std::sort(candidateBots.begin(), candidateBots.end(),
            [](const tuple<float, BotRef, JobRef> a,
               const tuple<float, BotRef, JobRef> b) {
    return std::get<0>(a) < std::get<0>(b);
  });

  set<BotRef> availableBots = set<BotRef>(_bots);

  for (auto &t : candidateBots) {
    BotRef bot = std::get<1>(t);
    JobRef job = std::get<2>(t);
    if (availableBots.count(bot) > 0) {
      bot->acceptJob(job);
      availableBots.erase(bot);
    }
    if (availableBots.size() == 0) {
      return;
    }
  }
}

std::function<float(Vec2i)> BotManager::getCostFunction() {
  set<Vec2i, VecComparison> *reference = &_passableCoords;
  // Passable tile is 0/ Unpassable = infinity
  // TODO: More complex cost function (if needed)
  // Corridors lest cost than rooms?
  return [reference](Vec2i coord) {
    if (reference->count(coord) > 0) {
      return 0.0f;
    }
    return INFINITY;
  };
}
