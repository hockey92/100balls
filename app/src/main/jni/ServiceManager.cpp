#include "ServiceManager.h"

ServiceManager ServiceManager::instance;

ServiceManager::ServiceManager() : gameService(NULL),
                                   fileService(NULL),
                                   screenService(NULL),
                                   font(NULL) { }

ServiceManager::~ServiceManager() {

}

ScreenService *ServiceManager::getScreenService() {
    return screenService;
}

ServiceManager *ServiceManager::getInstance() {
    return &instance;
}

GameService *ServiceManager::getGameService() {
    return gameService;
}

void ServiceManager::init(AAssetManager *aAssetManager) {
    fileService = new FileService(aAssetManager);
    screenService = new ScreenService(fileService);
    screenService->addSurfaceChangedCallbackFunc(surfaceChangedFunc);
}

FileService *ServiceManager::getFileService() {
    return fileService;
}

void *ServiceManager::surfaceChangedFunc(void *param) {
    ServiceManager *serviceManager = ServiceManager::getInstance();
    if (serviceManager->gameService == NULL) {
        Vec2 screenSize = serviceManager->getScreenService()->getGameCoordinates();
        serviceManager->gameService = new GameService(
                screenSize.x(),
                screenSize.y(),
                serviceManager->getScreenService()->getRendererFactory());
        serviceManager->font = new Font(serviceManager->getScreenService()->getRendererFactory(),
                                        serviceManager->getFileService());
    }
}

Font *ServiceManager::getFont() {
    return font;
}
