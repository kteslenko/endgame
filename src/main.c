#include <stdio.h>
#include "app.h"

int main() {
    t_app *app;
    
    if (!init_libs()) {
        psdlerror("Init error");
        return 1;
    }

    app = new_app();
    if (app == NULL) {
        psdlerror("App creation error");
        return 1;
    }

    event_loop(app);
    del_app(app);
    SDL_Quit(); //free memory
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
}
