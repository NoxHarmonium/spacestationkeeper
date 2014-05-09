-- Lua Script to load scene files
require 'yaml'

--result = yaml.load("lua: rocks\npeppers: [ habanero, chipotle, jalapeno ]\n")
--LuaDebug.Log(result.lua) 
--LuaDebug.Log(result.peppers[1])

function GetString(path)
    file = io.open(path, 'r')
    text = file:read('*a')
    return text;
end

function LoadRenderer(go, gameObjectNode) 
    renderer = go:getRenderer()
    posNode = gameObjectNode.RenderInfo.localPosition
    rotNode = gameObjectNode.RenderInfo.localRotation
    sclNode = gameObjectNode.RenderInfo.localScale

    renderer.localPosition = Vec3f(tonumber(posNode[1]), tonumber(posNode[2]), tonumber(posNode[3]))
    renderer.localRotation = Quatf(rotNode[1], rotNode[2], rotNode[3], rotNode[4])
    renderer.localScale = Vec3f(sclNode[1], sclNode[2], sclNode[3])

end

function LoadComponent(componentNode) 


    type = componentNode.type
    compT = _G[type]
    LuaDebug.Log('a')
    comp = TestComponent()
    LuaDebug.Log('b')

    for key, value in pairs(componentNode) do
        if key ~= 'type' then
            comp[key] = value;
        end
    end

    -- Temptest method
    comp:setup();
end


function LoadScene(path) 
    scene = {gameObjects = {}}
    source = GetString(path)
    result = yaml.load(source)
    for key, gameObjectNode in pairs(result.GameObjects) do
        go = GameObject()
        LoadRenderer(go, gameObjectNode)
        
        for key, componentNode in pairs(gameObjectNode.Components) do
            LoadComponent(componentNode)
        end

        table.insert(scene.gameObjects, go)

    end



end
