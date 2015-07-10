#include <pebble.h>

Window *window;

TextLayer *text_layer;
#define TEXT_LEN (32)
char text[TEXT_LEN + 1];

BitmapLayer *bitmap_layer;
GBitmap *bitmap;

// TickTimerService ハンドラ（1 秒ごとに呼ばれる）
void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    // 表示する文字を作成
    strftime(text, TEXT_LEN, "%Y-%m-%d%n%H:%M:%S", tick_time);

    // 表示する文字を text_layer に設定
    text_layer_set_text(text_layer, text);

    // ログを表示
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", text);
}

// 初期化
void handle_init(void) {
    // window を作成
    window = window_create();
    Layer *root_layer = window_get_root_layer(window);

    // bitmap_layer
    {
        // リソース "IMAGE_BACKGROUND" から画像を生成
        bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);

        // bitmap_layer を作成
        bitmap_layer = bitmap_layer_create(layer_get_bounds(root_layer));

        // bitmap_layer に画像を設定
        bitmap_layer_set_bitmap(bitmap_layer, bitmap);

        // bitmap_layer を root_layer に重ねる
        layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bitmap_layer));
    }

    // text_ayer
    {
        // text_layer を作成
        text_layer = text_layer_create(layer_get_bounds(root_layer));

        // text_layer のフォントを GOTHIC ボールド 28px に設定
        text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));

        // text_layer をセンタリング
        text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

        // text_layer の文字色を 白 に設定
        text_layer_set_text_color(text_layer, GColorWhite);

        // text_layer の背景色を 透明 に設定
        text_layer_set_background_color(text_layer, GColorClear);

        // text_layer を root_layer に重ねる
        layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    }

    // window をウィンドウ・スタックに重ねる
    window_stack_push(window, true);

    // TickTimerService を使用して 1 秒ごとにハンドラが呼ばれるように設定
    tick_timer_service_subscribe(SECOND_UNIT, tick_handler);

    // ログを表示
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

// 終了関数
void handle_deinit(void) {
    // text_layer を破棄
    text_layer_destroy(text_layer);

    // bitmap_layer を破棄
    bitmap_layer_destroy(bitmap_layer);

    // 画像を破棄
    gbitmap_destroy(bitmap);

    // window を破棄
    window_destroy(window);
}

int main(void) {
    handle_init();
    app_event_loop();
    handle_deinit();
}
