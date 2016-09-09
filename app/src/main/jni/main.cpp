#include <android_native_app_glue.h>
#include "Application.h"

extern "C" {
void android_main(struct android_app *state);
};

void android_main(struct android_app *app) {
    app_dummy();
    Application *application = new Application(app);
    application->loop();
    delete application;
}
