-- Extentions to classes to allow better serialisation

function CheckRequiredProperties(instance, className) 
    local sFields = instance:getSerialisedFields()
    for field in sFields do
        --LuaDebug.Log('Checking property: ' .. field.name)
        local fieldValue
        if field.useAccessors then
            local getterMethod = instance[field.getterName]
            if getterMethod then
                fieldValue = getterMethod(instance)
            end
        else 
            fieldValue = instance[field.name]
        end

        if field.required and not fieldValue then
            LuaDebug.Log('Class: ' .. className .. ' required property: ' .. field.name)
            return false
        end
    end
    return true
end

function ConvertValue(key, value, instance, go)
    local sFields = instance:getSerialisedFields()
    local matchingField = nil;
    for field in sFields do
        if field.name == key then 
            matchingField = field;
        end
    end

    if not matchingField then 
        LuaDebug.Log('Warning: No registered field for key: ' .. key)
        return value, nil
    end

    if type(value)=="table" and value["type"] then
        -- If there is a subType then it is a reference to another component
        local childType = value["type"] 
        local targetId = value["id"]
        local component = go:getComponent(targetId)
        if childType ~= class_info(component).name then
            error('Component referenced by id: ' .. targetId .. ' is not of type: ' .. childType)
        end
        return component, matchingField
    end

    --LuaDebug.Log('matchingField.type: ' .. matchingField.type)
    if matchingField.type == 'Vec2f' then 
        value = Vec2f(value[1], value[2])
    end
    if matchingField.type == 'Vec2i' then 
       value = Vec2i(math.floor(value[1]), math.floor(value[2]))
    end
    if matchingField.type == 'Vec3f' then 
        value = Vec2f(value[1], value[2], value[3])
    end
    if matchingField.type == 'Vec3i' then 
        value = Vec3i(math.floor(value[1]), math.floor(value[2]), math.floor(value[3]))
    end
    if matchingField.type == 'TileDef' then 
        local assetLoader = app_getAssetLoader()
        value = assetLoader:loadAssetAsTileDef(value)
    end
    if matchingField.type == 'ShaderDef' then 
        local assetLoader = app_getAssetLoader()
        value = assetLoader:loadAssetAsShaderDef(value)
    end
    if matchingField.type == 'AnimationSetDef' then
        local assetLoader = app_getAssetLoader()
        value = assetLoader:loadAssetAsAnimationSetDef(value)
    end

    return value, matchingField
end

function GetComponentFromType(go, type)
    if (go == nil or type == nil) then
        error("GameObject or GameComponent type was passed in as nil.")
    end

    go:refreshComponentList();

    local components = go:getComponentList()
    for comp in components do
        if type == class_info(comp).name then
            return comp
        end
    end
    return nil
end