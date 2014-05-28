class 'TestComponent' (GameComponent)

function TestComponent:__init()
    GameComponent.__init(self)
    LuaDebug.Log('TestComponent:__init() called!')
    
    self.updateCount = 0;

    -- Serialisation properties
    self:serialiseField('text', 'string')

end

function TestComponent:setup()
    LuaDebug.Log('The LUA TestComponent was initialised successfully! : ' .. self.text)
end

function TestComponent:update(deltaTime)
    --self.updateCount = self.updateCount + 1
    --if self.updateCount % 120 == 0 then
    --    LuaDebug.Log('Update')
    --end
end


