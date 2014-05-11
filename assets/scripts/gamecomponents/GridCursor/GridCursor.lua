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
    Property(self, 'frame', 'number')
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
    renderer.material = mat

    local dims = Rectf(0, 0, self._frameWidth, self._frameHeight)
    local uvCoords = mat.texture:getFrameUvCoords(self.frame)
    renderer.mesh = SimpleMesh.generateQuad(dims, uvCoords)

    AddGameObject(self._cursorGameObject)

end

function GridCursor:update()
        
end

function GridCursor:mouseMove(event)
    local cursorRenderer = self._cursorGameObject.renderer
    local gridRenderer = self.gameObject.renderer

    local mousePos = Vec3f(event:getX(), event:getY(), self.gameGrid.depth)

    local bounds = gridRenderer.mesh:getBoundingBox()
    local mousePos = gridRenderer.transform:getTransformMatrixWorld() * mousePos
    --LuaDebug.Log('MousePos: ' .. tostring(mousePos))
    
    -- Need a Vec2f to use the 2D overload of isInside()
    if Utils.isInside(bounds, Vec2f(mousePos.x, mousePos.y)) then
        cursorRenderer.material.baseColor = ColorAf(1,1,1,1)
        local x = math.floor(mousePos.x / self._frameWidth) * self._frameWidth
        local y = math.floor(mousePos.y / self._frameHeight) * self._frameHeight
        cursorRenderer.transform.localPosition = Vec3f(x, y, self.depth)
        LuaDebug.Log('Now at: ' .. tostring(renderer.transform.localPosition))
    else
        cursorRenderer.material.baseColor = ColorAf(1,1,1,0)
    end

end