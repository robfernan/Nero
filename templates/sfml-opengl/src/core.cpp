#include "core.h"
#include <cstdio>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <vector>

static lua_State* G_L = nullptr;
static std::vector<core::DrawRect> g_draw_queue;

static int l_draw_rect(lua_State* L) {
    // args: x,y,w,h,r,g,b,a (all numbers)
    float x = (float)luaL_optnumber(L, 1, 0.0);
    float y = (float)luaL_optnumber(L, 2, 0.0);
    float w = (float)luaL_optnumber(L, 3, 0.0);
    float h = (float)luaL_optnumber(L, 4, 0.0);
    float r = (float)luaL_optnumber(L, 5, 1.0);
    float g = (float)luaL_optnumber(L, 6, 1.0);
    float b = (float)luaL_optnumber(L, 7, 1.0);
    float a = (float)luaL_optnumber(L, 8, 1.0);
    core::push_draw_rect(x,y,w,h,r,g,b,a);
    return 0;
}

namespace core {

bool init(const char* script_path) {
    G_L = luaL_newstate();
    if (!G_L) return false;
    luaL_openlibs(G_L);
    // register helper draw function
    lua_register(G_L, "draw_rect", l_draw_rect);
    if (script_path) {
        if (luaL_dofile(G_L, script_path) != LUA_OK) {
            const char* err = lua_tostring(G_L, -1);
            std::fprintf(stderr, "Error loading script %s: %s\n", script_path, err ? err : "(unknown)");
            return false;
        }
    }
    return true;
}

void update(float dt) {
    if (!G_L) return;
    lua_getglobal(G_L, "update");
    if (lua_isfunction(G_L, -1)) {
        lua_pushnumber(G_L, dt);
        if (lua_pcall(G_L, 1, 0, 0) != LUA_OK) {
            const char* err = lua_tostring(G_L, -1);
            std::fprintf(stderr, "Lua update error: %s\n", err ? err : "(unknown)");
            lua_pop(G_L, 1);
        }
    } else {
        lua_pop(G_L, 1);
    }
}

void render() {
    // call optional Lua render hook
    if (!G_L) return;
    lua_getglobal(G_L, "render");
    if (lua_isfunction(G_L, -1)) {
        if (lua_pcall(G_L, 0, 0, 0) != LUA_OK) {
            const char* err = lua_tostring(G_L, -1);
            std::fprintf(stderr, "Lua render error: %s\n", err ? err : "(unknown)");
            lua_pop(G_L, 1);
        }
    } else {
        lua_pop(G_L, 1);
    }
}

void shutdown() {
    if (G_L) {
        lua_close(G_L);
        G_L = nullptr;
    }
    g_draw_queue.clear();
}

void push_draw_rect(float x, float y, float w, float h, float r, float g, float b, float a) {
    core::DrawRect d{ x,y,w,h,r,g,b,a };
    g_draw_queue.push_back(d);
}

std::vector<DrawRect> consume_draws() {
    auto tmp = g_draw_queue;
    g_draw_queue.clear();
    return tmp;
}

} // namespace core
