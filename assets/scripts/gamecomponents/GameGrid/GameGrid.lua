-- GameGrid
class 'GameGrid' (GameComponent)
local tuple = require 'tuple'

function GameGrid:__init()
    GameComponent.__init(self)
    LuaDebug.Log('GameGrid:__init() called!')

    -- Serialisation properties
    Property(self, 'defaultTileset', 'TextureDef')
    Property(self, 'targetTileset', 'TextureDef')
    Property(self, 'shader', 'ShaderDef')
    Property(self, 'size', 'Vec2i')
    Property(self, 'depth', 'number')

    self.selectedTiles = {}
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

    local defaultMat = Material()
    defaultMat.texture = self.defaultTileset
    defaultMat.shader = self.shader
    self._defaultMaterial = defaultMat;

    local targetMat = Material()
    targetMat.texture = self.targetTileset
    targetMat.shader = self.shader
    self._targetMaterial = targetMat

    self.tiles = {}

    for x = 0 , self.size.x do
        for y = 0, self.size.y do
            local tile = GameObject()
            tile.renderer.transform.localPosition = Vec3f(
                x * frameWidth,
                y * frameHeight,
                self.depth
            )

            tile.renderer.material = defaultMat

            local passibility = self:GetPassibility(x, y, self.size.x, self.size.y)
            self:SetupTileMesh(tile, passibility)
            tile.renderer:batch(batchedMesh)
            self.tiles[x..y] = tile

            AddGameObject(tile)
        end
    end

end

function GameGrid:update()
        
end

function GameGrid:keyUp(keyEvent)
    local frameWidth = self.defaultTileset:getFrameWidth()
    local frameHeight = self.defaultTileset:getFrameHeight()

    for id, tile in pairs(self.selectedTiles) do
        local tilePos = tile.renderer.transform.localPosition
        local coord = Vec2i(tilePos.x / frameWidth, tilePos.y / frameHeight)
        local job = MiningJob(self, coord, self._defaultMaterial, self._targetMaterial)
        RegisterJob(job)
        RemoveGameObject(tile) -- Remove selection gameobject
    end

    self.selectedTiles = {} -- Deselect all
end

function GameGrid:SetupTileMesh(tile, passibility) 
    local tex = tile.renderer.material.texture
    local frameWidth = tex:getFrameWidth()
    local frameHeight = tex:getFrameHeight()
    local texFrame = tex:getFrameFromPassibility(passibility)
    local dims = Rectf(0, 0, frameWidth, frameHeight)
    local uvCoords = tex:getFrameUvCoords(texFrame)
    LuaDebug.Log('texFrame: ' .. texFrame)
    local mesh = SimpleMesh.generateQuad(dims, uvCoords)
    tile.renderer.mesh = mesh
end

function GameGrid:GetPassibility(x, y, maxX, maxY)
    local passibility = Passibility()

    if x == 0 then
      passibility:setFlag(Passibility.West)
    end
    if y == 0 then
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

function GameGrid:FixTileFrames(point) 
    self:FixTileFrame(point);
    self:FixTileFrame(Vec2i(point.x - 1, point.y))
    self:FixTileFrame(Vec2i(point.x, point.y - 1))
    self:FixTileFrame(Vec2i(point.x + 1, point.y))
    self:FixTileFrame(Vec2i(point.x, point.y + 1))

end

function GameGrid:FixTileFrame(point)
    
    if (not self:TileIsPassable(point)) then
        return
    end

    LuaDebug.Log('GameGrid:FixTileFrame: point: ' .. point.x .. ',' .. point.y)

    local p = Passibility()
    local checks = {
        tuple(-1, 0, Passibility.West),
        tuple(0, -1, Passibility.North),
        tuple(1, 0, Passibility.East),
        tuple(0, 1, Passibility.South)
    }

    for i, check in ipairs(checks) do
        if self:TileIsPassable(Vec2i(point.x + check[1], point.y + check[2])) then
            p:setFlag(check[3])
        end
    end

    local tile = self.tiles[point.x..point.y]
    self:SetupTileMesh(tile, p)
    tile.renderer:invalidateBatch()
end

function GameGrid:TileIsPassable(point)
    local tile = self.tiles[point.x..point.y]
    return tile and tile.renderer.material.texture:getCanWalk()
end
