-- WorkBot
class 'WorkBot' (Bot)

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
    self._job = job
    self._state = Bot.MovingToJob
    self._targetPoint = nil
    self._path = nil
end

function WorkBot:getCurrentJob() 
    return self._job;
end

function WorkBot:update(deltaTime) 
    if  self._job then 
        
        -- MOVING
        if self._state == Bot.MovingToJob or self._state == Bot.WaitingForJob then
            local t = self.gameObject.renderer.transform

            if not self._path then
                local coords = GetBotManager():getPath(self:getCoord(), self:getDestination(), self._job:getRadius())
                self._path = {}
                for coord in coords do 
                    table.insert(self._path, self:coordToPos(coord))
                end
            end

            if not self._targetPoint or t.localPosition:distance(self._targetPoint) < self._elipsis then
                self._targetPoint = table.remove(self._path, 1)
            end
        
            if self._targetPoint ~= nil then
               
                local direction = self._targetPoint - t.localPosition
                direction:normalize()

        
              --cout << "targetCoord: " << targetCoord
               --    << " currentCoord: " << bot->getCoord()
               --    << " direction: " << direction << endl;

                local v = direction * self:getSpeed()
                t.localPosition = t.localPosition + Vec3f(v.x, v.y, 0);
            else
                if self._state == Bot.MovingToJob then
                    self._path = nil
                    self._targetPoint = nil
                    self._state = Bot.Working
                    self._job:allocateWorker()
                end
            end
        end

        if self._state == Bot.Working then
            if self._job:isDone() then
                self._state = Bot.WaitingForJob
            end
        end

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

function WorkBot:getState()
    return self._state;
end


