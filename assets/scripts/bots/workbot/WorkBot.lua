-- WorkBot
class 'WorkBot' (Bot)

local round = require 'round'

function WorkBot:__init(gameGrid, homeCoord)
    Bot.__init(self)
    LuaDebug.Log('WorkBot:__init() called!')

    self._gameGrid = gameGrid
    self._homeCoord = homeCoord
    self._state = Bot.WaitingForJob
    self._job = nil
    self._coord = homeCoord
    self._depth = 30  
    self._elipsis = 1
end

function WorkBot:setup()
    local renderer = self.gameObject.renderer
    renderer.transform.localPosition = self:coordToPos(self._homeCoord)
end

function WorkBot:getCoord()
    local renderer = self.gameObject.renderer
    return self:posToCoord(renderer.transform.localPosition)
end

function WorkBot:getDestination()
    if self._state == Bot.WaitingForJob then
        return self._homeCoord;
    end
    if self._state == Bot.MovingToJob then
        if not self._job then error('ASSERT FAIL: In mining state without a job.') end
        return self._job:getStartLocation()
    end
    if self._state == Bot.Working then
        return self:getCoord()
    end

    error('ASSERT FAIL: Workbot: Invalid State.')
end

function WorkBot:getSpeed()
    return 1.0
end

function WorkBot:canAcceptJobs(job)
    return self._state == Bot.WaitingForJob
end

function WorkBot:willAcceptJob(job)
    return class_info(job).name == 'MiningJob' 
end

function WorkBot:acceptJob(job)
    LuaDebug.Log('Accepting job. State == WorkBot.States.MOVING_TO_JOB')
    if (self._state == Bot.Working) then
        self._job:deallocateWorker()
    end

    self._job = job
    self._state = Bot.MovingToJob
    self._targetPoint = nil
    self._path = nil
end

function WorkBot:getCurrentJob() 
    return self._job;
end

function WorkBot:update(deltaTime)  
    local t = self.gameObject.renderer.transform
    
    -- MOVING
    if self._state == Bot.MovingToJob or self._state == Bot.WaitingForJob then
        if not self._path then
            LuaDebug.Log('WorkBot: Finding path to ' .. tostring(self:getDestination()))
            local radius = 0
            if self._job then
                radius = self._job:getRadius()
            end
            local coords = GetBotManager():getPath(self:getCoord(), self:getDestination(), radius)
            self._path = {}
            for coord in coords do 
                table.insert(self._path, self:coordToPos(coord))
            end
            self._targetPoint = nil
        end

        if not self._targetPoint or t.localPosition:distance(self._targetPoint) < self._elipsis then
            self._targetPoint = table.remove(self._path, 1)
        end
    
       
        if self._targetPoint == nil and self._state == Bot.MovingToJob then
            LuaDebug.Log('WorkBot: Target point reached. Switching to Working.')
            self._path = nil
            self._state = Bot.Working
            self._job:allocateWorker()
            
            -- Move to job slot relative to forward
            local jobSlotIndex = self._job:getWorkerCount() - 1
            local jobSlotPos = self._job:getWorkerSlot(jobSlotIndex)
            local texDef = self._gameGrid.defaultTileset
            local frameWidth = texDef:getFrameWidth()
            local frameHeight = texDef:getFrameHeight()
            local dir = self:coordToPos(self._job:getStartLocation()) - t.localPosition
            dir:normalize()
            local angle = math.atan2(-dir.x, dir.y)
            jobSlotPos:rotate(angle)

            self._targetPoint = t.localPosition + Vec3f(
                frameWidth * (jobSlotPos.x / 2),
                frameHeight * (jobSlotPos.y / 2),
                self._depth
                )
            
        end
    end

    if self._state == Bot.Working then
        if self._job:isDone() then
            LuaDebug.Log('WorkBot: Job is finished. Switching to WaitingForJob.')
            self._state = Bot.WaitingForJob
            self._job = nil
        end
        if t.localPosition:distance(self._targetPoint) < self._elipsis then
            self._targetPoint = nil
        end
    end

    if self._targetPoint ~= nil then
        local direction = self._targetPoint - t.localPosition
        direction:normalize()

        local v = direction * self:getSpeed()
        t.localPosition = t.localPosition + Vec3f(v.x, v.y, 0);
        local angle = math.atan2(direction.x, -direction.y)
        t.localRotation = Quatf(0,0,angle)
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
        round(pos.x  / frameWidth), 
        round(pos.y  / frameHeight)
        )

end

function WorkBot:getState()
    return self._state;
end


