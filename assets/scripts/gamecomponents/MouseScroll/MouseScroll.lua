-- Moves the gameobject on the xy plane when the mouse is moved to the edges of the screen.
class 'MouseScroll' (GameComponent)

function MouseScroll:__init()
    GameComponent.__init(self)
    LuaDebug.Log('MouseScroll:__init() called!')
    
    -- Private fields
    self._velocity = Vec2f(0, 0)       -- Pixels/Second
    self._mousePos = Vec2f(0, 0)

    -- Serialisation properties
    Property(self, 'EdgeSensitivity', 'number', false)
    Property(self, 'Acceleration', 'Vec2f', false)
    Property(self, 'Deceleration', 'number', false)
    Property(self, 'MaxSpeed', 'number', false)
    Property(self, 'MouseWheelMult', 'number', false)

    -- Property default values
    self.EdgeSensitivity = 25.0            -- Pixels
    self.Acceleration = Vec2f(15.0, 15.0) -- Pixels/Second/Second
    self.Deceleration = 0.92
    self.MaxSpeed = 40.0 -- Pixels/Second
    self.MouseWheelMult = 0.05

end

function MouseScroll:setup()

end

function MouseScroll:update()
    local mp = self._mousePos;
    local dt = app_getDeltaTime()
    local ww = app_getWindowWidth()
    local wh = app_getWindowHeight()
    local go = self.gameObject;
    local rd = go.renderer;

    if (mp.x > 0 and mp.x < ww and mp.y > 0 and mp.y < wh) then
        if mp.x < self.EdgeSensitivity then
            local multiplier = 1.0 - (mp.x / self.EdgeSensitivity)
            self._velocity = self._velocity + Vec2f(-self.Acceleration.x * multiplier, 0) * dt
        end

        if mp.x > ww - self.EdgeSensitivity then
            local multiplier = 1.0 - ((ww - mp.x) / self.EdgeSensitivity)
            self._velocity = self._velocity + Vec2f(self.Acceleration.x * multiplier, 0) * dt
        end

        if (mp.y < self.EdgeSensitivity) then
            local multiplier = 1.0 - (mp.y / self.EdgeSensitivity);
            self._velocity = self._velocity +  Vec2f(0, -self.Acceleration.y * multiplier) * dt
        end

        if mp.y > wh - self.EdgeSensitivity then
            local multiplier = 1.0 - ((wh - mp.y) / self.EdgeSensitivity)
            self._velocity  = self._velocity + Vec2f(0.0, self.Acceleration.y * multiplier) * dt
        end
    end

    self._velocity:limit(self.MaxSpeed)

    rd.transform.localPosition = rd.transform.localPosition + Vec3f(self._velocity.x, self._velocity.y, 0)

    self._velocity = self._velocity * self.Deceleration


end

function MouseScroll:draw()
    --go = self.gameObject;
    --rd = go.renderer;

    --LuaDebug.Log('Position: x: ' .. rd.transform.localPosition.x .. ' y: ' .. rd.transform.localPosition.y)
end

function MouseScroll:mouseMove(event)
    local ww = app_getWindowWidth()
    local wh = app_getWindowHeight()
    local pos = event:getPos()
    local x = pos.x;
    local y = pos.y;

    -- Clamp within screen bounds
    x = math.max(0, x);
    x = math.min(x, ww);
    y = math.max(0, y);
    y = math.min(y, wh);

    self._mousePos = Vec2f(x, y);
end

function MouseScroll:mouseDown(event)

end

function MouseScroll:mouseWheel(event)
    local rd = self.gameObject.renderer;
    local scale = event.getWheelIncrement() * self.MouseWheelMult
    rd.transform.localScale = rd.transform.localScale + Vec3f(scale, scale, scale);
end



