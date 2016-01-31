#ifndef NATIVE_ACTIVITY_RENDERERPOOL_H
#define NATIVE_ACTIVITY_RENDERERPOOL_H

#include <map>
#include <string>
#include "Renderer.h"

class RendererPool {
public:
    static RendererPool *getInstance();

    Renderer *getRenderer(std::string renderName) {
        std::map<std::string, Renderer *>::iterator iter = renderers.find(renderName);
        if (iter == renderers.end()) {

        }
        return renderers.find(renderName)->second;
    }

private:
    static RendererPool *instance;
    std::map<std::string, Renderer *> renderers;

    RendererPool();
};

#endif //NATIVE_ACTIVITY_RENDERERPOOL_H
