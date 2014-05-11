-- GameGrid
class 'GameGrid' (GameComponent)

function GameGrid:__init()
    GameComponent.__init(self)
    LuaDebug.Log('GameGrid:__init() called!')

    -- Serialisation properties
    Property(self, 'defaultTileset', 'TextureDef')
    Property(self, 'shader', 'ShaderDef')
    Property(self, 'size', 'Vec2i')
    Property(self, 'depth', 'number')
end

function GameGrid:setup()
    LuaDebug.Log('GameGrid:setup()')
    local renderer = self.gameObject.renderer;
    renderer.transform.localPosition.z = self.depth;
    -- Create the batched mesh
    -- The materials are handled by the batched mesh so 
    -- we don't have to set self.gameObject.renderer.material
    local batchedMesh = BatchedMesh()
    renderer.mesh = batchedMesh

    local frameWidth = self.defaultTileset:getFrameWidth()
    local frameHeight = self.defaultTileset:getFrameHeight()

    local mat = Material()
    mat.texture = self.defaultTileset
    mat.shader = self.shader

    for x = 1 , self.size.x do
        for y = 1, self.size.y do
            local tile = GameObject()
            tile.renderer.transform.localPosition = Vec3f(
                x * frameWidth,
                y * frameHeight,
                self.depth
            )
            
            local passibility = GetPassibility(x, y, self.size.x, self.size.y)
            local texFrame = mat.texture:getFrameFromPassibility(passibility)

            local dims = Rectf(0, 0, frameWidth, frameHeight)
            local uvCoords = mat.texture:getFrameUvCoords(texFrame)

            local mesh = SimpleMesh.generateQuad(dims, uvCoords)

            tile.renderer.material = mat
            tile.renderer.mesh = mesh

            tile.renderer:batch(batchedMesh)

            AddGameObject(tile)
        end
    end

end

function GameGrid:update()
        
end

function GetPassibility(x, y, maxX, maxY)
    local passibility = Passibility()

    if x == 1 then
      passibility:setFlag(Passibility.West)
    end
    if y == 1 then
      passibility:setFlag(Passibility.North)
    end
    if x == maxX then
      passibility:setFlag(Passibility.East)
    end
    if y == maxY then
      passibility:setFlag(Passibility.South)
    end
    -- All others are set to none
    if passibility:getInternalValue() == 0  then
      passibility:setFlag(Passibility.None)
    end

    return passibility;

end


