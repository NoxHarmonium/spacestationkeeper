-- GameGrid
class 'GameGrid' (GameComponent)
local tuple = require 'tuple'

function GameGrid:__init()
    GameComponent.__init(self)
    LuaDebug.Log('GameGrid:__init() called!')

    -- Serialisation properties
    self:serialiseField('defaultTileset', 'TileDef')
    self:serialiseField('targetTileset', 'TileDef')
    self:serialiseField('shader', 'ShaderDef')
    self:serialiseField('size', 'Vec2i')
    self:serialiseField('depth', 'number')

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

    self.tiles = {}

    for x = 0 , self.size.x do
        for y = 0, self.size.y do
            local tile = GameObject()
            
            tile.renderer.transform.localPosition = Vec3f(
                x * frameWidth,
                y * frameHeight,
                self.depth
            )

            local passibility = self:GetPassibility(x, y, self.size.x, self.size.y)
            self:SetupTile(tile, passibility, self.defaultTileset)
            tile.renderer:batch(batchedMesh)
            self.tiles[x..y] = tile

            AddGameObject(tile)
        end
    end

end

function GameGrid:update(deltaTime)
        
end

function GameGrid:keyUp(keyEvent)
    -- Filter out every key but m
    -- TODO: Make this key configurable (under confirm action?)
    local doMine = keyEvent:getCode() == KeyEvent.KEY_x or keyEvent:getCode() == KeyEvent.KEY_m
    local doInstant = keyEvent:getCode() == KeyEvent.KEY_x

    if (doMine) then
       
        local frameWidth = self.defaultTileset:getFrameWidth()
        local frameHeight = self.defaultTileset:getFrameHeight()

        for id, tile in pairs(self.selectedTiles) do
            local tilePos = tile.renderer.transform.localPosition
            local coord = Vec2i(tilePos.x / frameWidth, tilePos.y / frameHeight)
            if doInstant then
                 -- Instant mine so you can create test maps without bots
                local sprite = GetComponentFromType(self.tiles[coord.x..coord.y], 'Sprite')
                sprite:setSpriteTexture(self.targetTileset)
                self:FixTileFrames(coord)
            else 
                -- Create mining job (requires bots)
                local job = MiningJob(self, coord, self.defaultTileset, self.targetTileset)
                RegisterJob(job)
            end
            RemoveGameObject(tile) -- Remove selection gameobject
        end
    end

    self.selectedTiles = {} -- Deselect all
end

function GameGrid:SetupTile(tile, passibility, texture) 
    
    local texFrame = texture:getFrameFromPassibility(passibility)
    local sprite = Sprite(texture, texFrame)
    tile:addComponent(sprite)
   
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

    if not self:PointInRange(point) or not self:TileIsPassable(point) then
        return
    end

    --LuaDebug.Log('GameGrid:FixTileFrame: point: ' .. point.x .. ',' .. point.y)

    local p = Passibility()
    local checks = {
        tuple(-1, 0, Passibility.West),
        tuple(0, -1, Passibility.North),
        tuple(1, 0, Passibility.East),
        tuple(0, 1, Passibility.South)
    }

    for i, check in ipairs(checks) do
        local checkPoint = Vec2i(point.x + check[1], point.y + check[2])
        if self:PointInRange(checkPoint) and self:TileIsPassable(checkPoint) then
            p:setFlag(check[3])
        end
    end

    local tile = self.tiles[point.x..point.y]
    local sprite = GetComponentFromType(tile, 'Sprite')
    local texture = sprite:getSpriteTexture()
    local texFrame = texture:getFrameFromPassibility(p)
    sprite:setSpriteFrame(texFrame)

    --self:SetupTile(tile, p)
    --tile.renderer:invalidateBatch()
end

function GameGrid:TileIsPassable(point)
    local tile = self.tiles[point.x..point.y]
    local sprite = GetComponentFromType(tile, 'Sprite')
    local texture = sprite:getSpriteTexture()
    return tile and texture:getCanWalk()
end

function GameGrid:PointInRange(point) 
    return point.x >= 0 and point.x <= self.size.x and point.y > 0 and point.y < self.size.y;
end