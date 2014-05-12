-- Cursor Component - Shows a cursor over a grid

-- GameGrid
class 'GridCursor' (GameComponent)

function GridCursor:__init()
    GameComponent.__init(self)
    LuaDebug.Log('GridCursor:__init() called!')

    -- Serialisation properties
    Property(self, 'gameGrid', 'GameGrid')
    Property(self, 'cursorTileset', 'TextureDef')
    Property(self, 'shader', 'ShaderDef')
    Property(self, 'depth', 'number')
    Property(self, 'cursorFrame', 'number')
    

    self._cursorSize = Vec3f(1,1,0)
    self._oldCursorSize = Vec3f(0,0,0)
    self._mouseDown = false
end

function GridCursor:setup()
    LuaDebug.Log('GridCursor:setup()')
    self._cursorGameObject = GameObject()
    local renderer = self._cursorGameObject.renderer;

    self._frameWidth = self.cursorTileset:getFrameWidth()
    self._frameHeight = self.cursorTileset:getFrameHeight()

    local mat = Material()
    mat.texture = self.cursorTileset
    mat.shader = self.shader
    mat.baseColor = ColorAf(1,1,1,0) -- Initially disabled
    renderer.material = mat

    self:rebuildMeshIfNeeded()

    AddGameObject(self._cursorGameObject)

end

function GridCursor:update()
        
end

function GridCursor:mouseDown(event)
    local coords = self:snapToGrid(event:getPos())
    self._anchor = Vec3f(coords.x, coords.y, self.gameGrid.depth)
    self._cursorSize = Vec3f(1,1,0)
    self._mouseDown = true
end

function GridCursor:mouseUp(event)
    self._cursorSize = Vec3f(1,1,0)
    self._mouseDown = false

    -- Move cursor back to the right spot
    self:mouseMove(event)
end

function GridCursor:mouseMove(event)
    local cursorRenderer = self._cursorGameObject.renderer
    local gridRenderer = self.gameObject.renderer

    local mousePos = Vec3f(event:getX(), event:getY(), self.gameGrid.depth)

    local bounds = gridRenderer.mesh:getBoundingBox()
    local mousePos = gridRenderer.transform:getTransformMatrixWorld() * mousePos
    
    self:rebuildMeshIfNeeded()
    
    -- Need a Vec2f to use the 2D overload of isInside()
    if Utils.isInside(bounds, Vec2f(mousePos.x, mousePos.y)) then
        cursorRenderer.material.baseColor = ColorAf(1,1,1,1)
        local coords = self:snapToGrid(mousePos)
        cursorRenderer.transform.localPosition = Vec3f(coords.x, coords.y, self.depth)
    else
        cursorRenderer.material.baseColor = ColorAf(1,1,1,0)
    end

end

function GridCursor:mouseDrag(event) 
    self._cursorSize = Vec3f(
            math.floor((event:getX() - self._anchor.x) / self._frameWidth),
            math.floor((event:getY() - self._anchor.y) / self._frameHeight),
            0
            )
    self:rebuildMeshIfNeeded()
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
        local dims = Rectf(0, 0, self._cursorSize.x * self._frameWidth, self._cursorSize.y * self._frameHeight)
        local uvCoords = mat.texture:getFrameUvCoords(self.cursorFrame)
        renderer.mesh = SimpleMesh.generateQuad(dims, uvCoords)
        self._oldCursorSize = self._cursorSize
    end
end
