#ifndef NATIVE_ACTIVITY_RENDERERPOOL_H
#define NATIVE_ACTIVITY_RENDERERPOOL_H

#include <map>
#include <string>
#include <android_native_app_glue.h>
#include "Renderer.h"

class RendererPool {
public:
    static RendererPool *getInstance();

    Renderer *getRenderer(std::string renderName) {
        std::map<std::string, Renderer *>::iterator iter = renderers.find(renderName);
        if (iter == renderers.end()) {
            return NULL;
        }
        return renderers.find(renderName)->second;
    }

    static void initialize(struct android_app *state);

private:
    static RendererPool *instance;
    std::map<std::string, Renderer *> renderers;

    RendererPool(android_app *state);
};

#endif //NATIVE_ACTIVITY_RENDERERPOOL_H
