class 'TestComponent' (GameComponent)

function TestComponent:__init()
    GameComponent.__init(self)
    print('TestComponent:__init() called!')
end

function TestComponent:setup()
    print('The LUA TestComponent was initialised successfully!')
end
