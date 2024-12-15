// Arduino IDE 2.3.3
// megaTinyCore by SpenceKonde 2.6.10
// Chip: ATtiny424 
// Clock: 10MHz

#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

// 赤外線LED接続ピン
#define IR_SEND_PIN   PIN_PA1

// 設定モードピン
#define SETTING_PIN   PIN_PA0

// キースキャンピン
#define SCAN_COL_1_PIN   PIN_PA3
#define SCAN_COL_2_PIN   PIN_PA2
#define SCAN_COL_3_PIN   PIN_PB0
#define SCAN_COL_4_PIN   PIN_PA4
#define SCAN_COL_5_PIN   PIN_PA5
#define SCAN_ROW_1_PIN   PIN_PB1
#define SCAN_ROW_2_PIN   PIN_PB2
#define SCAN_ROW_3_PIN   PIN_PB3
#define SCAN_ROW_4_PIN   PIN_PA7
#define SCAN_ROW_5_PIN   PIN_PA6

// 赤外線送信ビットレート(Hz)
#define IR_BITRATE   800

// EEPROM の書き込みされているかどうか確認するバイト
#define EEPROM_CHECK_DATA   0x22

// EEPROM の各情報の書き込み位置
#define EEPROM_PT_CHECK       0x00
#define EEPROM_PT_SCAN_MODE   0x01
#define EEPROM_PT_SEND_START  0x02

// スキャンモードのタイプ
#define TYPE_SCAN_MATRIX          0x00
#define TYPE_SCAN_MATRIX_DOUBLE   0x01
#define TYPE_SCAN_DIRECT          0x02

// セッティングモードのタイプ
#define SETTING_TYPE_SCAN_MODE  0x00
#define SETTING_TYPE_START_INDEX  0x01

// 赤外線のコマンド
#define IRCMD_SEND_SETTING   0xB3
#define IRCMD_SEND_KEY_DOWN  0xB1
#define IRCMD_SEND_KEY_UP    0xB2

// キーが押されていたデータのバイト数
#define PRESS_STATE_LENGTH   12

// 赤外線通信オブジェクト
SoftwareSerial ir_serial(-1, IR_SEND_PIN); // RX, TX

// 設定モードかどうかのフラグ
bool setting_mode_flag;

// 設定モードで今何を設定しているか
uint8_t setting_type;

// スキャンの動作タイプ
uint8_t scan_mode;

// 送信するボタン番号の開始位置
uint8_t send_start_index;

// ボタンが押されてどれくらいの時間が経ったか
short press_time;

// 最後に設定情報を送ってからどれくらいの時間が経ったか
short setting_send_time;

// キーが押されているかどうかのステータス
uint8_t press_data[PRESS_STATE_LENGTH];

// キーが押されているかどうかのステータス(前回取得分)
uint8_t press_data_old[PRESS_STATE_LENGTH];

// 設定モード中の設定ボタンステータス
uint8_t setting_btn_stat;


// EEPROM に設定を保存する
void erom_write(uint8_t set_scan_mode, uint8_t set_send_start_index) {
    scan_mode = set_scan_mode;
    send_start_index = set_send_start_index;
    EEPROM.write(EEPROM_PT_SCAN_MODE, scan_mode); // スキャンモードのデフォルトデータ書込み
    EEPROM.write(EEPROM_PT_SEND_START, send_start_index); // 送信するボタン番号の開始位置のデフォルトデータ書込み
}

// EEPROM から設定を読み込み
void erom_read() {
    uint8_t c;

    // 初期値設定
    scan_mode = TYPE_SCAN_MATRIX;
    send_start_index = 1;

    // 初めての起動の場合EPPROMにデフォルト設定を書き込む
    c = EEPROM.read(EEPROM_PT_CHECK); // 最初の0バイト目を読み込む
    if (c != EEPROM_CHECK_DATA) {
        // 設定が保存されていなければデフォルト値を保存
        EEPROM.write(EEPROM_PT_CHECK, EEPROM_CHECK_DATA); // 初期化したよを書き込む
        erom_write(scan_mode, send_start_index);
    } else {
        // 設定が保存されていれば設定値を読み込む
        scan_mode = EEPROM.read(EEPROM_PT_SCAN_MODE);
        send_start_index = EEPROM.read(EEPROM_PT_SEND_START);
    }
}

// 赤外線で設定情報を送信
void ir_send_setting() {
    ir_serial.write(IRCMD_SEND_SETTING); // 設定情報を送るコマンド
    ir_serial.write(setting_type); // 今何を設定中か
    ir_serial.write(scan_mode); // スキャンモード
    ir_serial.write(send_start_index); // スキャンタイプ
    setting_send_time = 0; // 設定情報を送ってからどれくらい時間が経ったかをリセット
}

// 赤外線でキーダウンを送信
void ir_send_key_down(uint8_t key_num) {
    ir_serial.write(IRCMD_SEND_KEY_DOWN); // キーダウンコマンド
    ir_serial.write(send_start_index + key_num); // 対象のキー番号
}

// 赤外線でキーアップを送信
void ir_send_key_up(uint8_t key_num) {
    ir_serial.write(IRCMD_SEND_KEY_UP); // キーアップコマンド
    ir_serial.write(send_start_index + key_num); // 対象のキー番号
}

// COLピンのピンモードを設定する
void col_pin_mode(uint8_t set_mode) {
    pinMode(SCAN_COL_1_PIN, set_mode);
    pinMode(SCAN_COL_2_PIN, set_mode);
    pinMode(SCAN_COL_3_PIN, set_mode);
    pinMode(SCAN_COL_4_PIN, set_mode);
    pinMode(SCAN_COL_5_PIN, set_mode);
}

// ROWピンのピンモードを設定する
void row_pin_mode(uint8_t set_mode) {
    pinMode(SCAN_ROW_1_PIN, set_mode);
    pinMode(SCAN_ROW_2_PIN, set_mode);
    pinMode(SCAN_ROW_3_PIN, set_mode);
    pinMode(SCAN_ROW_4_PIN, set_mode);
    pinMode(SCAN_ROW_5_PIN, set_mode);
}

// COLピンのOUTPUTを設定する
void col_pin_write(uint8_t col_index) {
    digitalWrite(SCAN_COL_1_PIN, (col_index != 0));
    digitalWrite(SCAN_COL_2_PIN, (col_index != 1));
    digitalWrite(SCAN_COL_3_PIN, (col_index != 2));
    digitalWrite(SCAN_COL_4_PIN, (col_index != 3));
    digitalWrite(SCAN_COL_5_PIN, (col_index != 4));
}

// ROWピンのOUTPUTを設定する
void row_pin_write(uint8_t row_index) {
    digitalWrite(SCAN_ROW_1_PIN, (row_index != 0));
    digitalWrite(SCAN_ROW_2_PIN, (row_index != 1));
    digitalWrite(SCAN_ROW_3_PIN, (row_index != 2));
    digitalWrite(SCAN_ROW_4_PIN, (row_index != 3));
    digitalWrite(SCAN_ROW_5_PIN, (row_index != 4));
}

// COLピンの入力状態を取得する
uint8_t col_pin_read() {
    uint8_t read_data = 0;
    if (!digitalRead(SCAN_COL_1_PIN)) read_data |= 0x01;
    if (!digitalRead(SCAN_COL_2_PIN)) read_data |= 0x02;
    if (!digitalRead(SCAN_COL_3_PIN)) read_data |= 0x04;
    if (!digitalRead(SCAN_COL_4_PIN)) read_data |= 0x08;
    if (!digitalRead(SCAN_COL_5_PIN)) read_data |= 0x10;
    return read_data;
}

// ROWピンの入力状態を取得する
uint8_t row_pin_read() {
    uint8_t read_data = 0;
    if (!digitalRead(SCAN_ROW_1_PIN)) read_data |= 0x01;
    if (!digitalRead(SCAN_ROW_2_PIN)) read_data |= 0x02;
    if (!digitalRead(SCAN_ROW_3_PIN)) read_data |= 0x04;
    if (!digitalRead(SCAN_ROW_4_PIN)) read_data |= 0x08;
    if (!digitalRead(SCAN_ROW_5_PIN)) read_data |= 0x10;
    return read_data;
}

// スキャンピン初期化
void scan_pin_setup() {
    if (scan_mode == TYPE_SCAN_MATRIX) {
        // マトリックススキャン
        col_pin_mode(INPUT_PULLUP);
        row_pin_mode(OUTPUT);

    // ダブルスキャンはスキャン時にINPUT/OUTPUT切り替わるのでここでは何もしない
    // } else if (scan_mode == TYPE_SCAN_MATRIX_DOUBLE) {

    } else if (scan_mode == TYPE_SCAN_DIRECT) {
        // ダイレクトスキャン
        col_pin_mode(INPUT_PULLUP);
        row_pin_mode(INPUT_PULLUP);
    }
}

// 設定モード用ループ
void setting_loop() {
    if (digitalRead(SETTING_PIN)) {
        // 設定ボタンは離されている
        if (setting_btn_stat == 1) {
            // 離されて最初の処理(通常押下)
            if (setting_type == SETTING_TYPE_SCAN_MODE) {
                // スキャンモード設定中ならスキャンモードカウントアップ
                scan_mode++;
                if (scan_mode > 2) scan_mode = 0;
            } else if (setting_type == SETTING_TYPE_START_INDEX) {
                // 送信開始番号設定中なら送信開始番号をカウントアップ
                send_start_index += 10;
                if (send_start_index > 250) send_start_index = 1;
            }
            erom_write(scan_mode, send_start_index); // 変更した内容をEEPROMに書き込み
            ir_send_setting(); // 赤外線で変更した設定内容を送信(確認用)
            setting_btn_stat = 0;

        } else if (setting_btn_stat == 2) {
            // 離されて最初の処理(長押し)
            setting_btn_stat = 0;
        }
    } else {
        // 設定ボタンは押されている
        if (setting_btn_stat == 0) {
            // 設定ボタンが押されて最初の処理
            press_time = 0; // 押されている時間リセット
            setting_btn_stat = 1;
        } else if (setting_btn_stat == 1) {
            // 前から設定ボタンは押されていた
            press_time++; // 押されている時間カウントアップ
            if (press_time > 150) {
                // 長押しされている
                setting_type++; // セッティングモードのタイプをカウントアップ
                if (setting_type > 1) setting_type = SETTING_TYPE_SCAN_MODE;
                ir_send_setting(); // 赤外線で変更した設定内容を送信(確認用)
                setting_btn_stat = 2;
            }
        }
    }
    // 設定情報を3秒おきに送信
    setting_send_time++;
    if (setting_send_time > 200) {
        ir_send_setting();
    }
    // ループ間の待ち
    delay(30);
}

// キースキャン
void scan_loop() {
    uint8_t c, i, j, read_length;

    memcpy(press_data_old, press_data, PRESS_STATE_LENGTH); // 前回取得した入力をoldにコピー
    memset(press_data, 0x00, PRESS_STATE_LENGTH); // 入力ステータスクリア

    // 今回分のキースキャン
    if (scan_mode == TYPE_SCAN_MATRIX) {
        // マトリックススキャン
        for (i=0; i<5; i++) {
            row_pin_write(i);
            press_data[i] = col_pin_read();
        }
        read_length = 5;

    } else if (scan_mode == TYPE_SCAN_MATRIX_DOUBLE) {
        // ダブルマトリックススキャン
        col_pin_mode(INPUT_PULLUP);
        row_pin_mode(OUTPUT);
        for (i=0; i<5; i++) {
            row_pin_write(i);
            press_data[i] = col_pin_read();
        }
        col_pin_mode(OUTPUT);
        row_pin_mode(INPUT_PULLUP);
        for (i=0; i<5; i++) {
            col_pin_write(i);
            press_data[i+5] = row_pin_read();
        }
        read_length = 10;

    } else if (scan_mode == TYPE_SCAN_DIRECT) {
        // ダイレクトスキャン
        press_data[0] = col_pin_read();
        press_data[1] = row_pin_read();
        read_length = 2;

    }

    // 入力情報を送信
    for (i=0; i<5; i++) {
        c = 1 << i;
        for (j=0; j<read_length; j++) {
            if (press_data[j] & c) {
                // 今押されている
                if (!(press_data_old[j] & c)) {
                    // 前は押されてなかった
                    ir_send_key_down((j * 5) + i); // キーダウンを送信
                }
            } else {
                // 今押されていない
                if (press_data_old[j] & c) {
                    // 前は押されていた
                    ir_send_key_up((j * 5) + i); // キーアップを送信
                }
            }
        }
    }

    // ループ間の待ち
    delay(10);
}

// 起動時の処理
void setup() {
    int i;

    // 変数の初期化
    setting_type = SETTING_TYPE_SCAN_MODE; // セッティングモードのスキャンタイプを設定中
    press_time = 0; // ボタンは押されてどれくらい時間が経ったか
    setting_send_time = 200; // 最後に設定情報を送ってからどれくらい時間が経ったか（最初はすぐに設定情報送りたいから初期値を200にしておく）
    memset(press_data, 0x00, PRESS_STATE_LENGTH); // キーの入力ステータス
    memset(press_data_old, 0x00, PRESS_STATE_LENGTH); // キーの入力ステータス(前回取得分)
    setting_btn_stat = 0; // 設定ボタンステータス
    setting_mode_flag = false; // 設定モードではない

    // EEPROM から設定情報を読み込む
    erom_read();

    // 赤外線シリアル初期化
    ir_serial.begin(IR_BITRATE);

    // 設定モードとして起動するか判定
    pinMode(SETTING_PIN, INPUT_PULLUP); // 設定ピン読み込みで初期化
    delay(10);
    // 起動してから1 秒間の間に設定ボタン押されたら設定モードにする
    for (i=0; i<100; i++) {
        if (!digitalRead(SETTING_PIN)) {
            // 設定ボタン押されたら設定モードON
            setting_mode_flag = true; // 設定モードON
            break;
        }
        delay(10);
    }

    if (!setting_mode_flag) {
        // スキャンモードならピンの初期化
        scan_pin_setup();
        // 設定ピンのプルアップ分の電力がもったいないので通常INPUTにする
        pinMode(SETTING_PIN, INPUT);
    }
}

// メイン処理
void loop() {
    if (setting_mode_flag) {
        // 設定モードで動いている時は設定モードループを実行
        setting_loop();

    } else {
        // キースキャンのループ
        scan_loop();

    }
}
