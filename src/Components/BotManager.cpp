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
  CoordListRef path = getPath(source, destination);
  if (path == nullptr) {
    cout << "Cannot get distance to destination if path cannot be found!"
         << endl;
    return -1.0f;
  }

  return (float)path->size();
}

float BotManager::distanceTo(Vec2i source, Vec2i destination, int radius) {
  CoordListRef path = getPath(source, destination, radius);
  if (path == nullptr) {
    cout << "Cannot get distance to destination if path cannot be found!"
         << endl;
    return -1.0f;
  }

  return (float)path->size();
}

CoordListRef BotManager::getPath(Vec2i source, Vec2i destination) {
  CoordListRef steps = make_shared<CoordList>();
  bool success =
      CoordSearch::findPath(source, destination, getCostFunction(), steps);
  if (!success) {
    cout << "Cannot find path to destination: (" << source << "-" << destination
         << ")" << endl;

    return nullptr;
  }
  cout << "BotManager::getPath(" << source << ", " << destination
       << "):" << endl;
  cout << "--start path--" << endl;
  for (Vec2i &coord : *steps) {
    cout << "step: " << coord;
  }
  cout << endl << "--end path--" << endl;
  return steps;
}

CoordListRef BotManager::getPath(Vec2i source, Vec2i destination, int radius) {
  CoordListRef steps = make_shared<CoordList>();
  bool success = CoordSearch::findPath(source, destination, getCostFunction(),
                                       steps, radius);
  if (!success) {
    cout << "Cannot find path to destination: (" << source << "-" << destination
         << ")" << endl;
    return nullptr;
  }
  cout << "BotManager::getPath(" << source << ", " << destination << ", "
       << radius << "):" << endl;
  cout << "--start path--" << endl;
  for (Vec2i &coord : *steps) {
    cout << ", step: " << coord;
  }
  cout << endl << "--end path--" << endl;
  return steps;
}

bool BotManager::isPassable(Vec2i coord) {
  return (_passableCoords.count(coord) > 0);
}

void BotManager::update(float deltaTime) {
  assignJobs();
  moveBots();
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

void BotManager::assignJobs() {
  vector<JobRef> pendingJobs = _jobManager->getActiveJobs();

  vector<std::tuple<float, BotRef, JobRef>> candidateBots;

  for (BotRef bot : _bots) {
    if (bot->canAcceptJobs()) {
      for (JobRef job : pendingJobs) {
        float d = distanceTo(bot->getCoord(), job->getEndLocation(),
                             job->getRadius());
        if (d >= 0.0f) { // Distance < 0 means error
          candidateBots.push_back(std::make_tuple(d, bot, job));
        }
      }
    }
  }

  if (candidateBots.size() == 0) {
    return;
  }

  std::sort(candidateBots.begin(), candidateBots.end(),
            [](const std::tuple<float, BotRef, JobRef> a,
               const std::tuple<float, BotRef, JobRef> b) {
    return std::get<0>(a) < std::get<0>(b);
  });

  set<BotRef> availableBots = set<BotRef>(_bots);

  for (auto &t : candidateBots) {
    BotRef bot = std::get<1>(t);
    JobRef job = std::get<2>(t);
    if (availableBots.count(bot) > 0) {
      cout << "Bot: " << bot << " acceptJob: " << job << endl;
      bot->acceptJob(job);
      availableBots.erase(bot);
    }
    if (availableBots.size() == 0) {
      return;
    }
  }
}

void BotManager::moveBots() {}
