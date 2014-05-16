-- Mining Job
class 'MiningJob' (Job)

function MiningJob:__init(gameGrid, coord, preReqMaterial, postReqMaterial)
    Job.__init(self)
    LuaDebug.Log('MiningJob:__init() called!')
    self._gameGrid = gameGrid
    self._coord = coord
    self._preReqMaterial = preReqMaterial
    self._postReqMaterial = postReqMaterial
    self._workUnitsDone = 0
    self._maxWorkUnits = 8
    self._workUnitPerWorker = 1 --TODO: put in config
    self._workUnitProgress = 0
end

function MiningJob:preRequisitesAreMet()
    local tile = self._gameGrid.tiles[self._coord.x..self._coord.y]
    local mat = tile.renderer.material
    return tile ~= nil and mat == self._preReqMaterial
end

function MiningJob:postRequistesAreMet()
    local tile = self._gameGrid.tiles[self._coord.x..self._coord.y]
    local mat = tile.renderer.material
    return tile ~= nil and mat == self._postReqMaterial
end

function MiningJob:isDone()
    return self._workUnitsDone >= self._maxWorkUnits
end

function MiningJob:getProgress()
    return self._workUnitsDone / self._maxWorkUnits
end

function MiningJob:update(deltaTime)
    local workPerSecond = self._workUnitPerWorker * 2 -- TODO: Use assigned resources
    local workRate = workPerSecond * deltaTime
    self._workUnitProgress = self._workUnitProgress + workRate

    if (self._workUnitProgress >= 1) then
        self._workUnitsDone = self._workUnitsDone + 1
        self._workUnitProgress = 0
    end

    if (self:isDone()) then
        local tile = self._gameGrid.tiles[self._coord.x..self._coord.y]
        tile.renderer.material = self._postReqMaterial
        self._gameGrid:FixTileFrames(self._coord)
        tile.renderer:invalidateBatch()
    end
end
