#include "inc/scene.h"
#include "raylib.h"

#define MAX_SCENE_STACK 10

Scene *nextScene; 
static Scene *sceneStack[MAX_SCENE_STACK];
static int sceneIndex = -1; 

void gameLoop(double delta) {
    // if the sceneStack is empty, try to populate it
    int sceneChange = -1; 
    int render = 1; 
    int update = 1; 

    if(sceneIndex == -1 && nextScene) {
        sceneChange = SCENE_UPDATE_PUSH; 
        sceneStack[sceneIndex] = nextScene;
    }

    int curScene = sceneIndex;

    // first, update top down

    while(curScene > -1) {
        sceneStack[curScene]->_render = render;
        sceneStack[curScene]->_update = update;
        int retCode = -1; 

        if(sceneStack[curScene]->_update) {
            retCode = sceneStack[curScene]->update_cb(delta); 
        }
        if(retCode >= 0 && ((retCode & SCENE_UPDATE_PROPOGATE_MASK) == SCENE_UPDATE_CAPTURE)) {
            update = 0; 
        }
        if(retCode >= 0 && (retCode & SCENE_UPDATE_CHANGE_MASK)) {
            sceneChange = retCode & SCENE_UPDATE_CHANGE_MASK;
        }
        if(retCode >= 0 && (retCode & SCENE_UPDATE_DELAY_UNLOAD)) {
            sceneStack[curScene]->_unload = 0; 
        } else {
            sceneStack[curScene]->_unload = 1; 
        }
        if(render == 1 && retCode >= 0 && ((retCode & SCENE_UPDATE_RENDER_MASK) == SCENE_UPDATE_PARENT_NO_RENDER)) {
            render = 0; 
        }
        --curScene;
    }

    ++curScene;
    // then render bottom up
    BeginDrawing();
    ClearBackground(RAYWHITE);
    while(curScene <= sceneIndex) {
        if(sceneStack[curScene]->_render) {
            sceneStack[curScene]->render_cb();
        }
        ++curScene; 
    }
    EndDrawing();
    // finally, load the new scene if needed
    if(sceneChange != -1) {
        switch(sceneChange) {
            case SCENE_UPDATE_POP:
                if(sceneStack[sceneIndex]->_unload) {
                    sceneStack[sceneIndex]->unload_cb();
                    sceneStack[sceneIndex]->_loaded = 0; 
                }
                --sceneIndex; 
                break;
            case SCENE_UPDATE_SWITCH:
                while(sceneIndex > -1) {
                    if(sceneStack[sceneIndex]->_unload) {
                        sceneStack[sceneIndex]->unload_cb();
                        sceneStack[sceneIndex]->_loaded = 0; 
                    }
                    --sceneIndex; 
                }
                sceneIndex = 0; 
                sceneStack[sceneIndex] = nextScene; 
                break;
            case SCENE_UPDATE_PUSH:
                ++sceneIndex; 
                sceneStack[sceneIndex] = nextScene; 
                break;
        }
        if(nextScene != 0 && nextScene->_loaded == 0) {
            nextScene->load_cb(); 
        }
        nextScene = 0;
    }
}