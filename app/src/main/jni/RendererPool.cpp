#include "RendererPool.h"
#include "CircleRenderer.h"
#include "GlassRenderer.h"
#include "ContainerRenderer.h"

RendererPool* RendererPool::instance = NULL;

RendererPool *RendererPool::getInstance() {
    if (instance == NULL) {
        instance = new RendererPool();
    }
    return instance;
}

RendererPool::RendererPool() {
    renderers.insert(std::pair<std::string, Renderer*>(std::string("circle"), new CircleRenderer()));
    renderers.insert(std::pair<std::string, Renderer*>(std::string("glass"), new GlassRenderer()));
    renderers.insert(std::pair<std::string, Renderer*>(std::string("container"), new ContainerRenderer()));
}
