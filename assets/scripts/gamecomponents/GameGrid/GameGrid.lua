-- GameGrid
class 'GameGrid' (GameComponent)

function GameGrid:__init()
    GameComponent.__init(self)
    LuaDebug.Log('GameGrid:__init() called!')

    -- Serialisation properties
    Property(self, 'defaultTileset', 'TextureDef')
    Property(self, 'defaultShader', 'ShaderDef')
    Property(self, 'size', 'Vec2i')
    Property(self, 'depth', 'number')
end

function GameGrid:setup()
    LuaDebug.Log('GameGrid:setup()')

    -- Create the batched mesh
    -- The materials are handled by the batched mesh so 
    -- we don't have to set self.gameObject.renderer.material
    batchedMesh = BatchedMesh()
    self.gameObject.renderer.mesh = batchedMesh

    frameWidth = self.defaultTileset:getFrameWidth()
    frameHeight = self.defaultTileset:getFrameHeight()

    mat = Material()
    mat.texture = self.defaultTileset
    mat.shader = self.defaultShader

    for x = 1 , self.size.x do
        for y = 1, self.size.y do
            tile = GameObject()
                LuaDebug.Log("d");
            tile.renderer.transform.localPosition = Vec3f(
                x * frameWidth,
                y * frameHeight,
                self.depth
            )
            
            dims = Rectf(0, 0, frameWidth, frameHeight)
            uvCoords = mat.texture:getFrameUvCoords(1)

            mesh = SimpleMesh.generateQuad(dims, uvCoords)

            tile.renderer.material = mat
            tile.renderer.mesh = mesh

            tile.renderer:batch(batchedMesh)

            app_registerGameObject(tile)
            table.insert(gameObjectMap,tile)
        end
    end

end

function GameGrid:update()
        
end


