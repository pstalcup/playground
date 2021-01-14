#ifndef SCENE_H
#define SCENE_H

typedef int (*load_cb_t)();
typedef int (*update_cb_t)(double delta);
typedef void (*render_cb_t)();
typedef int (*unload_cb_t)();

// this does not hold data for the scene. All this holds is call backs for the scene
// in order to ease memory management, each scene can only exist once in memory
// there is a strict "each scene can only appear in the stack once" requirement, not enforced in the code. 
typedef struct {
    load_cb_t load_cb;
    update_cb_t update_cb; 
    render_cb_t render_cb; 
    unload_cb_t unload_cb; 

    // these are used by the scene manager
    int _loaded; 
    int _render; 
    int _update;
    int _unload; 
} Scene;

#define SCENE(_load_cb, _update_cb, _render_cb, _unload_cb) (Scene) { (_load_cb), (_update_cb), (_render_cb), (_unload_cb), 0, 0, 0, 0}

// this is exposed so that different scenes have a method for controlling which scene will be set next
extern Scene *nextScene; 

// scene update return default: SCENE_UPDATE_BUBBLE | SCENE_UPDATE_NOOP | SCENE_UPDATE_ALWAYS_ACT | SCENE_UPDATE_UNLOAD | SCENE_UPDATE_PARENT_NO_RENDER

#define SCENE_UPDATE_BUBBLE 0x00
#define SCENE_UPDATE_CAPTURE 0x01
#define SCENE_UPDATE_PROPOGATE_MASK 0x01

#define SCENE_UPDATE_NOOP 0x00
#define SCENE_UPDATE_POP 0x02
#define SCENE_UPDATE_PUSH 0x04
#define SCENE_UPDATE_SWITCH 0x06
#define SCENE_UPDATE_CHANGE_MASK 0x06

#define SCENE_UPDATE_UNLOAD 0x00 
#define SCENE_UPDATE_DELAY_UNLOAD 0x08
#define SCENE_UPDATE_LOAD_MASK 0x08

#define SCENE_UPDATE_PARENT_NO_RENDER 0x00
#define SCENE_UPDATE_PARENT_RENDER 0x10
#define SCENE_UPDATE_RENDER_MASK 0x10

// this is the main game loop, and should not be invoked recursively
void gameLoop(double delta);

#endif