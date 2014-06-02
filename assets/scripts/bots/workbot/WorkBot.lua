-- Mining Job
class 'WorkBot' (Bot)

WorkBot.States = {
    WAITING_FOR_JOB = 0,
    MOVING_TO_JOB = 1,
    MINING = 2
}

function WorkBot:__init(gameGrid, homeCoord)
    Bot.__init(self)
    LuaDebug.Log('WorkBot:__init() called!')
    local renderer = self.gameObject.renderer

    self._gameGrid = gameGrid
    self._homeCoord = homeCoord
    self._state = WorkBot.States.WAITING_FOR_JOB
    self._job = nil
    self._coord = homeCoord
    self._depth = 30

    renderer.transform.localPosition = self:coordToPos(homeCoord);
    
end

function WorkBot:getCoord()
    local renderer = self.gameObject.renderer
    return self:posToCoord(renderer.transform.localPosition)
end

function WorkBot:getDestination()
    if self._state == WorkBot.States.WAITING_FOR_JOB then
        return self._homeCoord;
    end
    if self._state == WorkBot.States.MINING then
        if not self._job then error('ASSERT FAIL: In mining state without a job.') end
        return self._job:getStartLocation()
    end

    error('ASSERT FAIL: Workbot: Invalid State.')
end

function WorkBot:getSpeed()
    return 1.0
end

function WorkBot:willAcceptJob(job)
    return class_info(job).name == 'MiningJob' 
end

function WorkBot:acceptJob(job)
    _self._job = job
    self._state = WorkBot.States.MOVING_TO_JOB
end

function WorkBot:update(deltaTime) 
    if (self._state == WorkBot.States.MOVING_TO_JOB) then
        

    end
end

function WorkBot:coordToPos(coord)
    local texDef = self._gameGrid.defaultTileset
    local frameWidth = texDef:getFrameWidth()
    local frameHeight = texDef:getFrameHeight()

    return Vec3f(
        (coord.x * frameWidth), 
        (coord.y * frameHeight),
        self._depth
        )
end

function WorkBot:posToCoord(pos)
    local texDef = self._gameGrid.defaultTileset
    local frameWidth = texDef:getFrameWidth()
    local frameHeight = texDef:getFrameHeight()

    return Vec2i(
        math.floor(pos.x  / frameWidth), 
        math.floor(pos.y  / frameHeight)
        )

end


