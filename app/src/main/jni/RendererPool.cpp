#include "RendererPool.h"
#include "CircleRenderer.h"
#include "GlassRenderer.h"
#include "ContainerRenderer.h"
#include "TextureRenderer.h"

RendererPool *RendererPool::instance = NULL;

RendererPool *RendererPool::getInstance() {
    return instance;
}

RendererPool::RendererPool(struct android_app *state) {
    renderers.insert(std::pair<std::string, Renderer *>(std::string("circle"),
                                                        new TextureRenderer(state)));
//    renderers.insert(std::pair<std::string, Renderer *>(std::string("glass"), new GlassRenderer()));
//    renderers.insert(
//            std::pair<std::string, Renderer *>(std::string("container"), new ContainerRenderer()));
}

void RendererPool::initialize(struct android_app *state) {
//    if (RendererPool::instance == NULL) {
        RendererPool::instance = new RendererPool(state);
//    }
}
