-- Lua Script to load scene files
require 'yaml'

--result = yaml.load("lua: rocks\npeppers: [ habanero, chipotle, jalapeno ]\n")
--LuaDebug.Log(result.lua) 
--LuaDebug.Log(result.peppers[1])

gameObjectMap = {}

function GetString(path)
    file = io.open(path, 'r')
    text = file:read('*a')
    return text;
end

function LoadRenderer(go, gameObjectNode) 
    renderer = go.renderer;
    posNode = gameObjectNode.RenderInfo.localPosition
    rotNode = gameObjectNode.RenderInfo.localRotation
    sclNode = gameObjectNode.RenderInfo.localScale

    renderer.localPosition = Vec3f(posNode[1], posNode[2], posNode[3])
    renderer.localRotation = Quatf(rotNode[1], rotNode[2], rotNode[3], rotNode[4])
    renderer.localScale = Vec3f(sclNode[1], sclNode[2], sclNode[3])

end

function LoadComponent(componentNode) 
    type = componentNode.type
    if not type then
        LuaDebug.Log('Component node has no type key. Skipping...')
        return nil
    end

    if not _G[type] then
        LuaDebug.Log('No component type ' .. type .. ' registered. Skipping...')
        return nil
    end

    comp = _G[type]()

    for key, value in pairs(componentNode) do
        if key ~= 'type' then
            comp[key] = value;
        end
    end

    if not CheckRequiredProperties(comp, type) then
        LuaDebug.Log('Component node does not define all required properties. Skipping...')
        return nil
    end

    return comp
end


function LoadScene(path) 
    scene = {gameObjects = {}}
    source = GetString(path)
    result = yaml.load(source)
    for key, gameObjectNode in pairs(result.GameObjects) do
        go = GameObject()
        LoadRenderer(go, gameObjectNode) 
        
        for key, componentNode in pairs(gameObjectNode.Components) do
            comp = LoadComponent(componentNode)
            if (comp) then
                go:addComponent(comp)
            end
        end

        app_registerGameObject(go)
        table.insert(gameObjectMap,go)
    end
end
