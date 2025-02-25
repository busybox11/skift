#pragma once

#include <libgraphic/Shape.h>
#include <libwidget/Cursor.h>
#include <libwidget/Event.h>

enum CompositorMessageType
{
    COMPOSITOR_MESSAGE_INVALID,
    COMPOSITOR_MESSAGE_ACK,
    COMPOSITOR_MESSAGE_GREETINGS,

    COMPOSITOR_MESSAGE_CREATE_WINDOW,
    COMPOSITOR_MESSAGE_DESTROY_WINDOW,
    COMPOSITOR_MESSAGE_RESIZE_WINDOW,
    COMPOSITOR_MESSAGE_MOVE_WINDOW,
    COMPOSITOR_MESSAGE_FLIP_WINDOW,
    COMPOSITOR_MESSAGE_EVENT_WINDOW,
    COMPOSITOR_MESSAGE_CURSOR_WINDOW,
    COMPOSITOR_MESSAGE_SET_RESOLUTION,
    COMPOSITOR_MESSAGE_SET_WALLPAPER,
};

#define WINDOW_NONE (0)
#define WINDOW_BORDERLESS (1 << 0)
#define WINDOW_RESIZABLE (1 << 1)
#define WINDOW_ALWAYS_FOCUSED (1 << 2)
#define WINDOW_POP_OVER (1 << 3)

typedef unsigned int WindowFlag;

struct CompositorGreetings
{
    Rectangle screen_bound;
};

struct CompositorCreateWindow
{
    int id;
    WindowFlag flags;

    int frontbuffer;
    Vec2i frontbuffer_size;
    int backbuffer;
    Vec2i backbuffer_size;

    Rectangle bound;
};

struct CompositorDestroyWindow
{
    int id;
};

struct CompositorResizeWindow
{
    int id;

    Rectangle bound;
};

struct CompositorMoveWindow
{
    int id;

    Vec2i position;
};

struct CompositorFlipWindow
{
    int id;

    int frontbuffer;
    Vec2i frontbuffer_size;
    int backbuffer;
    Vec2i backbuffer_size;

    Rectangle bound;
};

struct CompositorEventWindow
{
    int id;

    Event event;
};

struct CompositorCursorWindow
{
    int id;

    CursorState state;
};

struct CompositorSetResolution
{
    int width;
    int height;
};

struct CompositorSetWallaper
{
    int wallpaper;
    Vec2i resolution;
};

struct CompositorMessage
{
    CompositorMessageType type;

    union {
        CompositorGreetings greetings;
        CompositorCreateWindow create_window;
        CompositorDestroyWindow destroy_window;
        CompositorResizeWindow resize_window;
        CompositorMoveWindow move_window;
        CompositorFlipWindow flip_window;
        CompositorEventWindow event_window;
        CompositorCursorWindow cursor_window;
        CompositorSetResolution set_resolution;
        CompositorSetWallaper set_wallaper;
    };
};
