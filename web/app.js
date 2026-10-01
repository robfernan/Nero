// Minimal WebGL + Fengari example
(function(){
  const canvas = document.getElementById('glcanvas');
  const gl = canvas.getContext('webgl2') || canvas.getContext('webgl');
  if (!gl) {
    document.body.innerHTML = '<p>WebGL not available</p>';
    return;
  }

  function resize() {
    const w = Math.floor(window.innerWidth);
    const h = Math.floor(window.innerHeight);
    canvas.width = w; canvas.height = h;
    gl.viewport(0,0,w,h);
  }
  window.addEventListener('resize', resize);
  resize();

  // create a persistent Lua state using fengari C API
  const lua = fengari.lua;
  const lauxlib = fengari.lauxlib;
  const to_luastring = fengari.to_luastring;

  const L = lauxlib.luaL_newstate();
  lauxlib.luaL_openlibs(L);

  // Provide a simple Lua draw_rect implementation that appends rect tables into global `rects`
  const setupDrawLua = `
rects = {}
function draw_rect(x,y,w,h,r,g,b,a)
  table.insert(rects, {x,y,w,h,r or 1,g or 1,b or 1,a or 1})
end
`;

  lauxlib.luaL_dostring(L, to_luastring(setupDrawLua));

  function loadAndRunLua(src) {
    if (lauxlib.luaL_loadstring(L, to_luastring(src)) !== 0) {
      const err = fengari.to_jsstring(lua.lua_tostring(L, -1));
      console.error('Lua load error:', err);
      return;
    }
    if (lua.lua_pcall(L, 0, 0, 0) !== 0) {
      const err = fengari.to_jsstring(lua.lua_tostring(L, -1));
      console.error('Lua runtime error:', err);
    }
  }

  fetch('game/main.lua').then(r=>r.text()).then(src=>{
    loadAndRunLua(src);
    console.log('Lua script loaded into persistent state');
  });

  // WebGL setup: simple shader for colored rectangles
  function compileShader(src, type) {
    const s = gl.createShader(type);
    gl.shaderSource(s, src);
    gl.compileShader(s);
    if (!gl.getShaderParameter(s, gl.COMPILE_STATUS)) {
      console.error(gl.getShaderInfoLog(s));
      gl.deleteShader(s);
      return null;
    }
    return s;
  }

  const vs = `#version 100
attribute vec2 a_pos;
uniform vec2 u_scale;
uniform vec2 u_translate;
void main(){
  vec2 pos = a_pos * u_scale + u_translate;
  vec2 clip = pos / vec2(${canvas.width.toFixed(1)}, ${canvas.height.toFixed(1)}) * 2.0 - 1.0;
  gl_Position = vec4(clip * vec2(1.0, -1.0), 0.0, 1.0);
}
`;

  const fs = `#version 100
precision mediump float;
uniform vec4 u_color;
void main(){ gl_FragColor = u_color; }`;

  const prog = gl.createProgram();
  const vsObj = compileShader(vs, gl.VERTEX_SHADER);
  const fsObj = compileShader(fs, gl.FRAGMENT_SHADER);
  gl.attachShader(prog, vsObj);
  gl.attachShader(prog, fsObj);
  gl.linkProgram(prog);
  gl.useProgram(prog);

  // unit quad centered at origin
  const quad = new Float32Array([-0.5,-0.5, 0.5,-0.5, -0.5,0.5, 0.5,0.5]);
  const vbo = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
  gl.bufferData(gl.ARRAY_BUFFER, quad, gl.STATIC_DRAW);

  const aPos = gl.getAttribLocation(prog, 'a_pos');
  gl.enableVertexAttribArray(aPos);
  gl.vertexAttribPointer(aPos, 2, gl.FLOAT, false, 0, 0);

  const uScale = gl.getUniformLocation(prog, 'u_scale');
  const uTrans = gl.getUniformLocation(prog, 'u_translate');
  const uColor = gl.getUniformLocation(prog, 'u_color');

  let last = performance.now();
  function frame(now) {
    const dt = (now - last) / 1000;
    last = now;
    // call Lua update(dt) if present
    lua.lua_getglobal(L, to_luastring('update'));
    if (lua.lua_isfunction(L, -1)) {
      lua.lua_pushnumber(L, dt);
      if (lua.lua_pcall(L, 1, 0, 0) !== 0) {
        const err = fengari.to_jsstring(lua.lua_tostring(L, -1));
        console.error('Lua update error:', err);
      }
    } else {
      lua.lua_pop(L, 1);
    }

    gl.clearColor(0.08, 0.1, 0.14, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // read rects table from Lua
    lua.lua_getglobal(L, to_luastring('rects'));
    if (lua.lua_istable(L, -1)) {
      const len = lua.lua_rawlen(L, -1);
      for (let i=1;i<=len;i++) {
        lua.lua_rawgeti(L, -1, i); // push rect table
        // read numeric fields 1..8
        const vals = [];
        for (let j=1;j<=8;j++) {
          lua.lua_rawgeti(L, -1, j);
          vals.push(lua.lua_isnumber(L, -1) ? lua.lua_tonumber(L, -1) : 0);
          lua.lua_pop(L,1);
        }
        // pop rect table
        lua.lua_pop(L,1);

        const x = vals[0], y = vals[1], w = vals[2], h = vals[3];
        const r = vals[4], g = vals[5], b = vals[6], a = vals[7];

        gl.useProgram(prog);
        gl.uniform2f(uScale, w, h);
        gl.uniform2f(uTrans, x, y);
        gl.uniform4f(uColor, r, g, b, a);
        gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
      }
      // clear Lua rects after reading
      lauxlib.luaL_dostring(L, to_luastring('rects = {}'));
    } else {
      lua.lua_pop(L,1);
    }

    requestAnimationFrame(frame);
  }
  requestAnimationFrame(frame);

})();
