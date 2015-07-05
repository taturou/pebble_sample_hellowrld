#include <pebble.h>

Window *window;
TextLayer *text_layer;

void handle_init(void) {
    // window と text_layer を作成
    window = window_create();
    text_layer = text_layer_create(GRect(0, 0, 144, 154));

    // 表示する文字を text_layer に設定
    text_layer_set_text(text_layer, "Hi, I'm a Pebble!");
    
    // フォントと表示位置を設定
    text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
    text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

    // text_layer を root_layer に重ねる
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

    // window 
    window_stack_push(window, true);

    // ログを表示
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) {
    // text_layer を破棄
    text_layer_destroy(text_layer);

    // window を破棄
    window_destroy(window);
}

int main(void) {
    handle_init();
    app_event_loop();
    handle_deinit();
}
