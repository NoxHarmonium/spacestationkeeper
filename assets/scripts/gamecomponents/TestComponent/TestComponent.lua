class 'TestComponent' (GameComponent)

function TestComponent:__init()
    GameComponent.__init(self)
    LuaDebug:Log('TestComponent:__init() called!')
end

function TestComponent:setup()
    LuaDebug:Log('The LUA TestComponent was initialised successfully!')
end