-- Mining Job
class 'MiningJob' (Job)

function MiningJob:__init(gameGrid, coord, preReqTexture, postReqTexture)
    Job.__init(self)
    LuaDebug.Log('MiningJob:__init() called!')
    self._gameGrid = gameGrid
    self._coord = coord
    self._preReqTexture = preReqTexture
    self._postReqTexture = postReqTexture
    self._workUnitsDone = 0
    self._maxWorkUnits = 8
    self._workUnitPerWorker = 1 --TODO: put in config
    self._workUnitProgress = 0
end

function MiningJob:preRequisitesAreMet()
    local tile = self._gameGrid.tiles[self._coord.x..self._coord.y]
    local tex = tile.renderer.material.texture
    return tile ~= nil and tex == self._preReqTexture
end

function MiningJob:postRequistesAreMet()
    local tile = self._gameGrid.tiles[self._coord.x..self._coord.y]
    local tex = tile.renderer.material.texture
    return tile ~= nil and tex == self._postReqTexture
end

function MiningJob:isDone()
    return self._workUnitsDone >= self._maxWorkUnits
end

function MiningJob:getProgress()
    return self._workUnitsDone / self._maxWorkUnits
end

function MiningJob:update(deltaTime)
    local workPerSecond = self._workUnitPerWorker * self:getWorkerCount() 
    local workRate = workPerSecond * deltaTime
    self._workUnitProgress = self._workUnitProgress + workRate

    if (self._workUnitProgress >= 1) then
        self._workUnitsDone = self._workUnitsDone + 1
        self._workUnitProgress = 0
    end

    if (self:isDone()) then
        local tile = self._gameGrid.tiles[self._coord.x..self._coord.y]
        local sprite = GetComponentFromType(tile, 'Sprite')
        sprite:setSpriteTexture(self._postReqTexture)
        --sprite:setup()
        self._gameGrid:FixTileFrames(self._coord)
        GetBotManager():addCoord(self._coord)
    end
end

function MiningJob:getStartLocation() 
    return self._coord
end

function MiningJob:getEndLocation()
    return self._coord
end

function MiningJob:getRadius() 
    return 1 -- Mining happens on the adjacent tile not on the actual tile that is inaccessible
end

function MiningJob:getMaxWorkers()
    return 2
end

function MiningJob:getWorkerSlot(workerIndex) 
    if workerIndex == 0 then
        return Vec2f(-0.7, 0.7)
    end
    if workerIndex == 1 then
        return Vec2f(0.7, 0.7)
    end
    error("Invalid worker index: Should be between 0 and " .. tostring(self:getMaxWorkers() - 1))

end