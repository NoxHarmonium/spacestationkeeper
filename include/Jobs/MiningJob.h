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
public:
  MiningJob(GameGrid *gameGrid, MapPoint targetMapPoint,
            AssetLoaderBase *assetLoader);
  virtual ~MiningJob();

  virtual bool preRequisitesAreMet();
  virtual bool postRequistesAreMet();
  virtual bool isDone();
  virtual float getProgress();
  virtual void update(float deltaTime);

  static constexpr char *preReqTileSet = "tilesets/asteroid";
  static constexpr char *postReqTileSet = "tilesets/corridor";
  static constexpr int workUnitPerWorker = 1; // TODO: Put these in config files
  static constexpr int maxWorkUnits = 8;

private:
  GameGrid *_gameGrid;
  MapPoint _targetMapPoint;
  int _workUnitsDone = 0;
  float _workUnitProgress = 0.0f;
  AssetLoaderBase *_assetLoader = nullptr;
};

#endif
