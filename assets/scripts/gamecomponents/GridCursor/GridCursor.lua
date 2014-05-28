-- Cursor Component - Shows a cursor over a grid

-- GameGrid
class 'GridCursor' (GameComponent)

function GridCursor:__init()
    GameComponent.__init(self)
    LuaDebug.Log('GridCursor:__init() called!')

    -- Serialisation properties
    self:serialiseField('gameGrid', 'GameGrid')
    self:serialiseField('cursorTileset', 'TileDef')
    self:serialiseField('shader', 'ShaderDef')
    self:serialiseField('timeThreshold', 'number')
    self:serialiseField('distanceThreshold', 'number')
    self:serialiseField('selectedFrame', 'number')
    self:serialiseField('selectedDepth', 'number')
    self:serialiseField('cursorDepth', 'number')
    self:serialiseField('cursorFrame', 'number')
    
    self._cursorDownPosition = Vec2i(0,0)
    self._cursorDownTime = Vec2i(0,0)
    self._cursorSize = Vec3f(0,0,0)
    self._oldCursorSize = Vec3f(0,0,0)
    self._mouseDown = false
end

function GridCursor:setup()
    LuaDebug.Log('GridCursor:setup()')
    self._cursorGameObject = GameObject()
    local renderer = self._cursorGameObject.renderer;

    self._frameWidth = self.cursorTileset:getFrameWidth()
    self._frameHeight = self.cursorTileset:getFrameHeight()
    self._cursorSize = Vec3f(self._frameWidth, self._frameHeight,0)

    local mat = Material()
    mat.texture = self.cursorTileset
    mat.shader = self.shader
    mat.baseColor = ColorAf(1,1,1,0) -- Initially disabled
    renderer.material = mat

    self:rebuildMeshIfNeeded()

    AddGameObject(self._cursorGameObject)

    local selectionMat = Material()
    selectionMat.texture = self.cursorTileset
    selectionMat.shader = self.shader
    self._selectionMat = selectionMat

end

function GridCursor:update(deltaTime)
        
end

function GridCursor:mouseDown(event)
    local mousePos = self:transformMousePos(event:getPos())
    self._anchor = mousePos
    self._cursorSize = Vec3f(self._frameWidth, self._frameHeight, 0)
    self._mouseDown = true
    self._cursorDownPosition = event:getPos()
    self._cursorDownTime = app_getElapsedSeconds()
end

function GridCursor:mouseUp(event)
    self._mouseDown = false

    local gridRenderer = self.gameObject.renderer
    local cursorRenderer = self._cursorGameObject.renderer

    local timeDelta = app_getElapsedSeconds() - self._cursorDownTime
    local posDelta = self._cursorDownPosition - event:getPos()

    local mousePos = self:snapToGrid(
        self:transformMousePos(event:getPos())
        )
    local bounds = gridRenderer.mesh:getBoundingBox()

    if timeDelta < self.timeThreshold and posDelta:length() < self.distanceThreshold then
        self:toggleBlock(bounds, mousePos)
    else 
        if self.selectionRange then
            local selectedTiles = self.gameGrid.selectedTiles;
            local minX = self.selectionRange.x
            local minY = self.selectionRange.y
            local maxX = self.selectionRange.z
            local maxY = self.selectionRange.w
            local firstTileSwitchedOn = nil
            for x = minX, maxX, self._frameWidth do
                for y = minY, maxY, self._frameHeight do
                    if firstTileSwitchedOn == nil then
                        firstTileSwitchedOn = self:toggleBlock(bounds, Vec2i(x, y))
                    else 
                        self:toggleBlock(bounds, Vec2i(x, y), firstTileSwitchedOn)
                    end
                end
            end
        end
    end

    self._cursorSize = Vec3f(self._frameWidth, self._frameHeight, 0)
    self.selectionRange = nil
    -- Move cursor back to the right spot
    self:mouseMove(event)
end

function GridCursor:mouseMove(event)
    local cursorRenderer = self._cursorGameObject.renderer
    local gridRenderer = self.gameObject.renderer

    local mousePos = self:transformMousePos(event:getPos())

    local bounds = gridRenderer.mesh:getBoundingBox()
    
    self:rebuildMeshIfNeeded()
    
    -- Need a Vec2f to use the 2D overload of isInside()
    if Utils.isInside(bounds, Vec2f(mousePos.x, mousePos.y)) then
        cursorRenderer.material.baseColor = ColorAf(1,1,1,1)
        local coords = self:snapToGrid(mousePos)
        cursorRenderer.transform.localPosition = Vec3f(coords.x, coords.y, self.cursorDepth)
    else
        cursorRenderer.material.baseColor = ColorAf(1,1,1,0)
    end

end

function GridCursor:mouseDrag(event) 
    local mousePos = self:snapToGrid(
        self:transformMousePos(event:getPos())
        )
    local anchorPos = self:snapToGrid(self._anchor)


    local downX = anchorPos.x 
    local downY = anchorPos.y 
    local upX = mousePos.x 
    local upY = mousePos.y 
    
    local minX = math.min(downX, upX)
    local maxX = math.max(downX, upX)
    local minY = math.min(downY, upY)
    local maxY = math.max(downY, upY)
 
    local cursorRenderer = self._cursorGameObject.renderer
    cursorRenderer.transform.localPosition = Vec3f(minX, minY, self.cursorDepth)
    self._cursorSize = Vec3f(
            ((maxX + self._frameWidth) - minX),
            ((maxY + self._frameHeight) - minY),
            0
            )

    self.selectionRange = Vec4f(minX, minY, maxX, maxY)
    self:rebuildMeshIfNeeded()
end

function GridCursor:transformMousePos(mousePos) 
    local pos = Vec3f(mousePos.x, mousePos.y, 0) -- Allow for multiple vector types to be passed in
    local gridRenderer = self.gameObject.renderer
    return gridRenderer.transform:getTransformMatrixWorld() * pos
end

function GridCursor:snapToGrid(mousePos)
    local x = math.floor(mousePos.x / self._frameWidth) * self._frameWidth
    local y = math.floor(mousePos.y / self._frameHeight) * self._frameHeight
    return Vec2i(x,y)
end

function GridCursor:rebuildMeshIfNeeded()
    if (self._cursorSize ~= self._oldCursorSize) then
        local renderer = self._cursorGameObject.renderer;
        local mat = renderer.material
        local dims = Rectf(0, 0, self._cursorSize.x, self._cursorSize.y)
        local uvCoords = mat.texture:getFrameUvCoords(self.cursorFrame)
        renderer.mesh = SimpleMesh.generateQuad(dims, uvCoords)
        self._oldCursorSize = self._cursorSize
    end
end

function GridCursor:toggleBlock(bounds, mousePos, switchOn) 
    if Utils.isInside(bounds, Vec2f(mousePos.x, mousePos.y)) then
        local x = mousePos.x
        local y = mousePos.y
        local coord = x..y -- hacky way to have a 2d key but it works!
        local selectedTiles = self.gameGrid.selectedTiles;
        
        if switchOn == nil then
            switchOn = not selectedTiles[coord]
        end


        if selectedTiles[coord] and not switchOn then
            RemoveGameObject(selectedTiles[coord])
            selectedTiles[coord] = nil -- remove value
            return false
        end
        if not selectedTiles[coord] and switchOn then
            local go = GameObject()
            selectedTiles[coord] = go
            self:setupSelectedGameObject(go, x, y)
            AddGameObject(go)
            return true
        end
    end
end

function GridCursor:setupSelectedGameObject(go, x, y) 
    local renderer = go.renderer
    local dims = Rectf(0, 0, 1 * self._frameWidth, 1 * self._frameHeight)
    local uvCoords = self._selectionMat.texture:getFrameUvCoords(self.selectedFrame)
    renderer.mesh = SimpleMesh.generateQuad(dims, uvCoords)
    renderer.material = self._selectionMat 
    renderer.transform.localPosition = Vec3f(x, y, self.selectedDepth)
    renderer.transform.parent = self.gameObject.renderer.transform
end
