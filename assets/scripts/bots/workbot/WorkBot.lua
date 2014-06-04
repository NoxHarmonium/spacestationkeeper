-- WorkBot
class 'WorkBot' (Bot)

local round = require 'round'
local pi = 3.14 -- todo: Global constant?

function WorkBot:__init(gameGrid, homeCoord, miningAnimSet)
    Bot.__init(self)
    LuaDebug.Log('WorkBot:__init() called!')

    self._gameGrid = gameGrid
    self._homeCoord = homeCoord
    self._state = Bot.WaitingForJob
    self._job = nil
    self._coord = homeCoord
    self._depth = 30  
    self._elipsis = 1
    self._miningAnimSet = miningAnimSet
    self._miningRange = 57
end

function WorkBot:setup()
    local renderer = self.gameObject.renderer
    renderer.transform.localPosition = self:coordToPos(self._homeCoord)

    -- Animation Setup
    self._miningAnimGo = GameObject()
    self._miningAnimComp = AnimatedSprite()
    self._miningAnimGo:addComponent(self._miningAnimComp)
    self._miningAnimComp:setAnimationSet(self._miningAnimSet)
    self._miningAnimComp:play()
    local r = self._miningAnimGo.renderer
    local t = r.transform
    t.parent = renderer.transform
    t.localPosition = Vec3f(0, -12, 3)
    t.localRotation = Quatf(0, 0, -pi/2)
    t.localScale = Vec3f(0.4, 0.4, 0.4)
    AddGameObject(self._miningAnimGo)
    r.renderEnabled = false

    self:addBehaviour(AvoidOtherBotsBehaviour())
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
        self._job:deactivateWorker()
        self._job:deallocateWorker()
    end

    self._job = job
    self._job:allocateWorker()
    self._state = Bot.MovingToJob
    self._targetPoint = nil
    self._path = nil

    if self._gotoLocationBehaviour then
        self:removeBehaviour(self._gotoLocationBehaviour)
        self._gotoLocationBehaviour = nil
    end
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
            
            if self._gotoLocationBehaviour then
                self:removeBehaviour(self._gotoLocationBehaviour)
                self._gotoLocationBehaviour = nil
            end

            if self._targetPoint then
                self._gotoLocationBehaviour = GotoLocationBehaviour(self._targetPoint, self:getSpeed())
                self:addBehaviour(self._gotoLocationBehaviour)
            end
        end

        if self._targetPoint == nil and self._state == Bot.MovingToJob then
            LuaDebug.Log('WorkBot: Target point reached. Switching to Working.')
            self._path = nil
            self._job:activateWorker()
            self._state = Bot.Working
            self._miningAnimGo.renderer.renderEnabled = true

            local sLoc = self:coordToPos(self._job:getStartLocation())
            local dir = sLoc - t.localPosition 
            dir:normalize()

            self._targetPoint = sLoc - (dir * self._miningRange)
            LuaDebug.Log("TargetPoint: " .. tostring(self._targetPoint))

            self._gotoLocationBehaviour = GotoLocationBehaviour(self._targetPoint, self:getSpeed())
            self:addBehaviour(self._gotoLocationBehaviour)
            
        end
    end

    if self._state == Bot.Working then
        if self._job:isDone() then
            LuaDebug.Log('WorkBot: Job is finished. Switching to WaitingForJob.')
            self._state = Bot.WaitingForJob
            self._miningAnimGo.renderer.renderEnabled = false
            self._job = nil
        end

        if self._targetPoint ~= nil and t.localPosition:distance(self._targetPoint) < self._elipsis then
            self._targetPoint = nil
            self:removeBehaviour(self._gotoLocationBehaviour)
            self._gotoLocationBehaviour = nil
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
        round(pos.x  / frameWidth), 
        round(pos.y  / frameHeight)
        )

end

function WorkBot:getState()
    return self._state;
end


