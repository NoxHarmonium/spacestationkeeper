//
//  MiningJob.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 28/04/2014.
//
//

#ifndef SpaceStationKeeper_MiningJob_h
#define SpaceStationKeeper_MiningJob_h

class MiningJob : public Job {
  MiningJob(GameGrid *gameGrid, MapPoint targetMapPoint);
  virtual ~MiningJob();

  virtual bool preRequisitesAreMet();
  virtual bool postRequistesAreMet();
  virtual bool isDone();
  virtual float getProgress();
  virtual void update(float deltaTime);
};

#endif
