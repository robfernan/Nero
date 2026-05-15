// platform.h — tiny platform abstraction
#pragma once

struct Platform {
    virtual ~Platform() = default;
    virtual bool init(int width, int height, const char* title) = 0;
    virtual void poll_events() = 0;
    virtual bool should_close() = 0;
    virtual void swap_buffers() = 0;
};

Platform* create_platform();
