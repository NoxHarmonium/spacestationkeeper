class 'AvoidOtherBotsBehaviour' (BotBehaviour)

function AvoidOtherBotsBehaviour:__init()
    BotBehaviour.__init(self)
    LuaDebug.Log('AvoidOtherBotsBehaviour:__init() called!')

    self._elipsis = 0.1
    
end

function AvoidOtherBotsBehaviour:getForce(bot)
    local t = bot.gameObject.renderer.transform
    local botMan = GetBotManager()
    local bots = botMan:getBots(t.localPosition, 50)
    local combinedDir = Vec3f(0,0,0)
    for adjacentBot in bots do
        if adjacentBot ~= bot then
            local botPos = adjacentBot.gameObject.renderer.transform.localPosition
            local d = botPos:distance(t.localPosition) 
            if d < 1 then d = 1 end
            local dir = botPos - t.localPosition
            dir:normalize()
            local inverseDir = (dir * (1 / d))
            combinedDir = combinedDir - inverseDir

        end
    end

    return combinedDir
end

        
