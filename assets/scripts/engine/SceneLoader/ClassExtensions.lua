-- Extentions to classes to allow better serialisation

pTable = {}

function Property(instance, name, type, required)
    -- Default to required
    if required == nil then required = true end

    if not pTable[instance] then
        pTable[instance] = {}
    end
   
    pTable[instance][name] = { type=type, required=required }
end

function CheckRequiredProperties(instance, className) 

    if pTable[instance] then
        for name, prop in pairs(pTable[instance]) do
            LuaDebug.Log('Checking property: ' .. name)
            if prop.required and not instance[name] then
                LuaDebug.Log('Class: ' .. className .. ' required property: ' .. name)
                return false
            end
        end
    end
    return true
end

function ConvertValue(key, value, instance, go)
    if not pTable[instance] then return value end;
    local propInfo = pTable[instance][key]
    if not propInfo then 
        LuaDebug.Log('Warning: No registered field for key: ' .. key)
        return value 
    end
    local pType = propInfo.type;

    if type(value)=="table" and value["type"] then
        -- If there is a subType then it is a reference to another component
        local pType = value["type"] 
        local targetId = value["id"]
        local component = go:getComponent(targetId)
        if pType ~= class_info(component).name then
            error('Component referenced by id: ' .. targetId .. ' is not of type: ' .. pType)
        end
        return component
    end

    LuaDebug.Log('ptype: ' .. pType)
    if pType == 'Vec2f' then 
        return Vec2f(value[1], value[2])
    end
    if pType == 'Vec2i' then 
        return Vec2i(math.floor(value[1]), math.floor(value[2]))
    end
    if pType == 'Vec3f' then 
        return Vec2f(value[1], value[2], value[3])
    end
    if pType == 'Vec3i' then 
        return Vec3i(math.floor(value[1]), math.floor(value[2]), math.floor(value[3]))
    end
    if pType == 'TileDef' then 
        local assetLoader = app_getAssetLoader()
        return assetLoader:loadAssetAsTileDef(value)
    end
    if pType == 'ShaderDef' then 
        local assetLoader = app_getAssetLoader()
        return assetLoader:loadAssetAsShaderDef(value)
    end
    if pType == 'AnimationSetDef' then
        local assetLoader = app_getAssetLoader()
        return assetLoader:loadAssetAsAnimationSetDef(value)
    end

    return value
end

function GetComponentFromType(go, type)
    if (go == nil or type == nil) then
        error("GameObject or GameComponent type was passed in as nil.")
    end

    go:refreshComponentList();

    local components = go.componentList
    for comp in components do
        if type == class_info(comp).name then
            return comp
        end
    end
    return nil
end