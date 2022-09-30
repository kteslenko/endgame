#include "scenes.h"

static void handle_event(t_scene *scene, SDL_Event *e) {
    t_menu_scene *menu_scene = (t_menu_scene*)scene;

    if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
        SDL_Point point = {e->button.x, e->button.y};
        SDL_Rect start_rect = frect_to_rect(&menu_scene->start_game.rect);
        SDL_Rect exit_rect = frect_to_rect(&menu_scene->exit_game.rect);

        if (SDL_PointInRect(&point, &start_rect)) {
            SDL_Event event;
            SDL_zero(event);
            event.type = scene->event_number + ACTIVE_SCENE_CHANGED;
            event.user.code = GAME_SCENE;
            SDL_PushEvent(&event);
        }
        else if (SDL_PointInRect(&point, &exit_rect)) {
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
        }
    }
}

static void render(t_scene *scene, t_renderer *renderer) {
    SDL_Point center = {renderer->screen.w / 2, renderer->screen.h / 2};
    t_menu_scene *menu_scene = (t_menu_scene*)scene;
    SDL_Point text_pos;
    SDL_Color name_text_color = {79, 43, 20, 255};
    SDL_Color start_text_color = {48, 48, 48, 255};
    SDL_Color exit_text_color = {180, 180, 180, 255};
    mode_screen(renderer);
    render_texture(renderer, renderer->textures[BACKGROUND], NULL, &renderer->screen);

    SDL_Rect text_size = text_rect(renderer, "Medieval Cringe", menu_scene->name_font);

    text_pos = (SDL_Point){center.x - text_size.w / 2, center.y - text_size.h / 2 - 100}; 
    render_text(renderer, "Medieval Cringe", menu_scene->name_font, text_pos, name_text_color);

    menu_scene->start_game.rect.x = 100;
    menu_scene->start_game.rect.y = renderer->screen.h - menu_scene->start_game.rect.h - 100;
    menu_scene->exit_game.rect.x = renderer->screen.w - menu_scene->start_game.rect.w - 100;
    menu_scene->exit_game.rect.y = renderer->screen.h - menu_scene->start_game.rect.h - 100;

    render_texturef(renderer, menu_scene->start_game.texture, NULL, &menu_scene->start_game.rect);
    text_pos = (SDL_Point){menu_scene->start_game.rect.x + 80, menu_scene->start_game.rect.y + 15};
    render_text(renderer, "PLAY", menu_scene->font, text_pos, start_text_color);

    render_texturef(renderer, menu_scene->exit_game.texture, NULL, &menu_scene->exit_game.rect);
    text_pos = (SDL_Point){menu_scene->exit_game.rect.x + 85, menu_scene->exit_game.rect.y + 15};
    render_text(renderer, "EXIT", menu_scene->font, text_pos, exit_text_color);
}

t_menu_scene *new_menu_scene(t_renderer *renderer, uint32_t event_number) {
    t_menu_scene *menu_scene = malloc(sizeof(t_menu_scene));

    menu_scene->scene.event_number = event_number;
    menu_scene->scene.handle_event = handle_event;
    menu_scene->scene.update = NULL;
    menu_scene->scene.render = render;
    menu_scene->start_game = (t_block){true, {0, 0, 256, 88}, renderer->textures[BUTTON_PLAY]};
    menu_scene->exit_game = (t_block){true, {0, 0, 256, 88}, renderer->textures[BUTTON_EXIT]};
    
    menu_scene->font = TTF_OpenFont("resource/text/PixelMiddle.ttf", 64);
    menu_scene->name_font = TTF_OpenFont("resource/text/PixelMiddle.ttf", 150);

    return menu_scene;
}


