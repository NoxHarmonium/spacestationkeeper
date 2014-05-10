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

function ConvertValue(key, value, instance)
    if not pTable[instance] then return value end;
    propInfo = pTable[instance][key]
    if not propInfo then return value end
    pType = propInfo.type;

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
    if pType == 'TextureDef' then 
        assetLoader = app_getAssetLoader()
        return assetLoader:loadAssetAsTextureDef(value)
    end
    if pType == 'ShaderDef' then 
        assetLoader = app_getAssetLoader()
        return assetLoader:loadAssetAsShaderDef(value)
    end

    return value


end