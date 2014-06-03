-- Lua Script to load scene files
require 'yaml'
require 'strict'

--result = yaml.load("lua: rocks\npeppers: [ habanero, chipotle, jalapeno ]\n")
--LuaDebug.Log(result.lua) 
--LuaDebug.Log(result.peppers[1])

gameObjectMap = {}

function GetString(path)
    local file = io.open(path, 'r')
    local text = file:read('*a')
    return text;
end

function LoadRenderer(go, gameObjectNode) 
    local transform = go.renderer.transform;
    local posNode = gameObjectNode.RenderInfo.localPosition
    local rotNode = gameObjectNode.RenderInfo.localRotation
    local sclNode = gameObjectNode.RenderInfo.localScale

    transform.localPosition = Vec3f(posNode[1], posNode[2], posNode[3])
    -- Disabled for now because LuaBind doesn't like it for some reason
    --transform.localRotation = Quatf(rotNode[1], rotNode[2], rotNode[3], rotNode[4])
    transform.localScale = Vec3f(sclNode[1], sclNode[2], sclNode[3])

end

function LoadComponent(componentNode, go) 
    local type = componentNode.type
    if not type then
        LuaDebug.Log('Component node has no type key. Skipping...')
        return nil
    end

    if not _G[type] then
        LuaDebug.Log('No component type ' .. type .. ' registered. Skipping...')
        return nil
    end

    local comp = _G[type]()

    -- First pass to set ids
    for key, value in pairs(componentNode) do
        if key == 'id' then
            GameComponent.setId(comp, value)
        end
    end

    -- Second pass to set fields that may depend on ids
    for key, value in pairs(componentNode) do
        if key ~= 'type' and key ~= 'id' then  -- Ignore type and id field
            local convertedValue, matchingField = ConvertValue(key, value, comp, go)
            if matchingField then
                -- Skip setting fields that are not registered
                if matchingField.useAccessors then
                    -- Special accessor is defined
                    local setterMethod = comp[matchingField.setterName]
                    setterMethod(comp,convertedValue)
                else 
                    comp[key] = convertedValue;
                end
            end
        end
    end

    if not CheckRequiredProperties(comp, type) then
        LuaDebug.Log('Component node does not define all required properties. Skipping...')
        return nil
    end

    return comp
end


function LoadScene(path) 
    local scene = {gameObjects = {}}
    local source = GetString(path)
    local result = yaml.load(source)
    for key, gameObjectNode in pairs(result.GameObjects) do
        local go = GameObject()
        local name = gameObjectNode["name"]
        if name then
            go:setId(name)
        end

        LoadRenderer(go, gameObjectNode) 
        
        for key, componentNode in pairs(gameObjectNode.Components) do
            local comp = LoadComponent(componentNode, go)
            if (comp) then
                go:addComponent(comp)
            end
        end
        AddGameObject(go)
        
    end
end

function AddGameObject(go) 
    app_registerGameObject(go)
    gameObjectMap[go:getId()] = go
end

function RemoveGameObject(go) 
    gameObjectMap[go:getId()] = nil
    app_destroyGameObject(go)
end

function RegisterJob(job) 
    app_registerJob(job)
end

function CancelJob(job) 
    app_cancelJob(job)
end

function GetBotManager() 
    return app_getBotManager()
end