-- Lua Script to load scene files
require 'yaml'

result = yaml.load("lua: rocks\npeppers: [ habanero, chipotle, jalapeno ]\n")

LuaDebug.Log(result.lua) 
LuaDebug.Log(result.peppers[1])

function LoadScene(path) 

end