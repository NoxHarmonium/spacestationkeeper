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
    local bounds = gridRenderer.mesh:getBoundingBox()
    
    local mousePos = Vec3f(event:getX(), event:getY(), self.gameGrid.depth)
    mousePos = gridRenderer.transform:getTransformMatrixWorld() * mousePos

    if timeDelta < self.timeThreshold and posDelta:length() < self.distanceThreshold then
        self:toggleBlock(bounds, mousePos)
    else
        local downMousePos = Vec3f(self._cursorDownPosition.x, self._cursorDownPosition.y, self.gameGrid.depth)
        downMousePos = gridRenderer.transform:getTransformMatrixWorld() * downMousePos

        local downX = math.floor(downMousePos.x / self._frameWidth) 
        local downY = math.floor(downMousePos.y / self._frameHeight)
        local upX = math.floor(mousePos.x / self._frameWidth) 
        local upY = math.floor(mousePos.y / self._frameHeight)

        if math.abs(upX-downX) > 0 and math.abs(upY-downY) > 0 then 
            local minX = math.min(downX, upX)
            local maxX = math.max(downX, upX)
            local minY = math.min(downY, upY)
            local maxY = math.max(downY, upY)
           

            for x = minX, maxX do
                for y = minY, maxY do
                    self:toggleBlock(bounds, Vec2i(x * self._frameWidth, y * self._frameHeight))
                end
            end
        end
    end

    -- Move cursor back to the right spot
    self:mouseMove(event)
end

function ToggleSelectTileOnClick:toggleBlock(bounds, mousePos) 
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

function ToggleSelectTileOnClick:setupGameObject(go, x, y) 
    local renderer = go.renderer
    local dims = Rectf(0, 0, 1 * self._frameWidth, 1 * self._frameHeight)
    local uvCoords = self._tileMaterial.texture:getFrameUvCoords(self.selectedFrame)
    renderer.mesh = SimpleMesh.generateQuad(dims, uvCoords)
    renderer.material = self._tileMaterial 
    renderer.transform.localPosition = Vec3f(x * self._frameWidth, y * self._frameHeight, self.depth)
    renderer.transform.parent = self.gameObject.renderer.transform

end
