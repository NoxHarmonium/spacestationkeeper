-- ToggleSelectTileOnClick

-- GameGrid
class 'ToggleSelectTileOnClick' (GameComponent)

function ToggleSelectTileOnClick:__init()
    GameComponent.__init(self)
    LuaDebug.Log('ToggleSelectTileOnClick:__init() called!')

    -- Serialisation properties
    Property(self, 'gameGrid', 'GameGrid')
    Property(self, 'gridCursor', 'GridCursor')
    Property(self, 'timeThreshold', 'number')
    Property(self, 'distanceThreshold', 'number')
    Property(self, 'selectedFrame', 'number')
    Property(self, 'depth', 'number')

    self._cursorDownPosition = Vec2i(0,0)
    self._cursorDownTime = Vec2i(0,0)
     
end

function ToggleSelectTileOnClick:setup(event)
    local renderer = self.gameObject.renderer
    local mat = Material()
    mat.texture = self.gridCursor.cursorTileset
    mat.shader = self.gridCursor.shader
    self._tileMaterial = mat

    self._frameWidth = self.gameGrid.defaultTileset:getFrameWidth()
    self._frameHeight = self.gameGrid.defaultTileset:getFrameHeight()
end

function ToggleSelectTileOnClick:mouseDown(event)
   self._cursorDownPosition = event:getPos()
   self._cursorDownTime = app_getElapsedSeconds()
end

function ToggleSelectTileOnClick:mouseUp(event)
   local timeDelta = app_getElapsedSeconds() - self._cursorDownTime
   local posDelta = self._cursorDownPosition - event:getPos()
   local gridRenderer = self.gameObject.renderer
   

   if timeDelta < self.timeThreshold and posDelta:length() < self.distanceThreshold then
        local mousePos = Vec3f(event:getX(), event:getY(), self.gameGrid.depth)

        local bounds = gridRenderer.mesh:getBoundingBox()
        local mousePos = gridRenderer.transform:getTransformMatrixWorld() * mousePos
        if Utils.isInside(bounds, Vec2f(mousePos.x, mousePos.y)) then
            local x = math.floor(mousePos.x / self._frameWidth) 
            local y = math.floor(mousePos.y / self._frameHeight)
            local coord = x..y -- hacky way to have a 2d key but it works!
            local selectedTiles = self.gameGrid.selectedTiles;
            
            if selectedTiles[coord] then
                app_destroyGameObject(selectedTiles[coord])
                selectedTiles[coord] = nil -- remove value
            else
                local go = GameObject()
                selectedTiles[coord] = go
                self:setupGameObject(go, x, y)
                AddGameObject(go)
            end
        end
   end

    -- Move cursor back to the right spot
    self:mouseMove(event)
end

function ToggleSelectTileOnClick:setupGameObject(go, x, y) 
    local renderer = go.renderer
    local dims = Rectf(0, 0, 1 * self._frameWidth, 1 * self._frameHeight)
    local uvCoords = self._tileMaterial.texture:getFrameUvCoords(self.selectedFrame)
    renderer.mesh = SimpleMesh.generateQuad(dims, uvCoords)
    renderer.material = self._tileMaterial 
    renderer.transform.localPosition = Vec3f(x * self._frameWidth, y * self._frameHeight, self.depth)
    renderer.transform.parent = self.gameObject.renderer.transform

end
