-- sample Lua gameplay script

local angle = 0

function update(dt)
    angle = angle + dt * 1.0
    if angle > 6.2831853 then angle = angle - 6.2831853 end
    -- This is where gameplay logic would run; rendering hooks can be used if host exposes draws
end

function render()
    -- optional Lua-side render hook (not used in this minimal host)
    -- print("Lua render hook")
end
