#include <pebble.h>

Window *window;
TextLayer *text_layer;

#define TEXT_LEN (32)
char text[TEXT_LEN + 1];

// TickTimerService ハンドラ（1 秒ごとに呼ばれる）
void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    // 表示する文字を作成
    strftime(text, TEXT_LEN, "%Y-%m-%d%n%H:%M:%S", tick_time);

    // 表示する文字を text_layer に設定
    text_layer_set_text(text_layer, text);

    // ログを表示
    APP_LOG(APP_LOG_LEVEL_DEBUG, text);
}

void handle_init(void) {
    // window を作成
    window = window_create();

    // text_layer を作成
    text_layer = text_layer_create(GRect(0, 0, 144, 168));

    // text_layer のフォントを GOTHIC ボールド 28px に設定
    text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));

    // text_layer をセンタリング
    text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

    // text_layer の文字色を 白 に設定
    text_layer_set_text_color(text_layer, GColorWhite);

    // text_layer の背景色を 赤 に設定
    text_layer_set_background_color(text_layer, GColorRed);

    // text_layer を root_layer に重ねる
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

    // window をウィンドウ・スタックに重ねる
    window_stack_push(window, true);

    // TickTimerService を使用して 1 秒ごとにハンドラが呼ばれるように設定
    tick_timer_service_subscribe(SECOND_UNIT, tick_handler);

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
