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