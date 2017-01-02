#ifndef INC_100BALLS_SERVICEMANAGER_H
#define INC_100BALLS_SERVICEMANAGER_H

#include "PhysicsService.h"
#include "ScreenService.h"
#include "GameService.h"
#include "FileService.h"
#include "Font.h"

class ServiceManager {
public:
    virtual ~ServiceManager();

    ScreenService *getScreenService();

    GameService *getGameService();

    FileService *getFileService();

    Font *getFont();

    static ServiceManager *getInstance();

    void init(AAssetManager *aAssetManager);

private:
    static ServiceManager instance;

    GameService *gameService;
    ScreenService *screenService;
    FileService *fileService;
    Font *font;

    ServiceManager();

    static void *surfaceChangedFunc(void *param);
};

#endif //INC_100BALLS_SERVICEMANAGER_H
