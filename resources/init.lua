-- Initialisation LUA code for the game engine. Should be embedded as a resource and always executed.
registeredComponents = {}

function RegisterLuaComponent (c)
    -- Prevents garbage collecti on by keeping local reference
    instance = c();
    table.insert(registeredComponents, instance)
    RegisterLuaComponentNative(instance)
end