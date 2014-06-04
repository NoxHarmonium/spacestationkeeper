class 'GotoLocationBehaviour' (BotBehaviour)

function GotoLocationBehaviour:__init(targetPos, speed)
    BotBehaviour.__init(self)
    LuaDebug.Log('GotoLocationBehaviour:__init() called!')

    self._targetPos = targetPos
    self._speed = speed
    self._elipsis = 0.1
    
end

function GotoLocationBehaviour:getForce(bot)
    local t = bot.gameObject.renderer.transform;
    if (t.localPosition:distance(self._targetPos) > self._elipsis) then
        local dir = self._targetPos - t.localPosition
        dir:normalize()
        return dir * self._speed
    else
        return Vec3f(0,0,0)
    end
end

        
