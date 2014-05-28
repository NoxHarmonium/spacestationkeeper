//
//  BotManager.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 27/05/2014.
//
//

#include "BotManager.h"

BotManager::BotManager(JobManagerRef jobManager) : _jobManager(jobManager) {}

BotManager::~BotManager() {}

void BotManager::addCoord(Vec2i coord) { _passableCoords.insert(coord); }

void BotManager::removeCoord(Vec2i coord) { _passableCoords.erase(coord); }

void BotManager::addBot(BotRef bot) { _bots.insert(bot); }

void BotManager::removeBot(BotRef bot) { _bots.erase(bot); }
