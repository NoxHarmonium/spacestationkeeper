class 'TestComponent' (GameComponent)

function TestComponent:__init()
    GameComponent.__init(self)
end

function TestComponent:setup()
    print('The LUA TestComponent was initialised successfully!')
end

RegisterLuaComponent(TestComponent)