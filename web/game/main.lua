-- browser-side Lua script (same API as desktop)
local angle = 0

function update(dt)
  angle = angle + dt * 60.0
  if angle > 6.2831853 then angle = angle - 6.2831853 end
  -- Draw a moving rectangle via draw_rect(x,y,w,h,r,g,b,a)
  local cx = 200 + math.sin(angle) * 100
  local cy = 200
  draw_rect(cx, cy, 64, 64, 0.2, 0.7, 0.9, 1.0)
end

function render()
  -- JS performs rendering, Lua schedules draw commands via draw_rect
end
