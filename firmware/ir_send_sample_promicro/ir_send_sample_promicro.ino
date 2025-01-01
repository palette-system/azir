// ProMicroでAZIRの赤外線キーボード用コマンドを送信するサンプル
// TX0 と VCC に赤外線LEDを接続すると動作します

#include <SoftwareSerial.h>

// シリアル通信クラス
SoftwareSerial ir_serial(-1, 1); // RXピン, TXピン

void setup() {
  // シリアル通信クラス 初期化
  ir_serial.begin(800);
}

// 5秒おきに仮想キー1を押す
void loop() {
  // 仮想ボタン1を押した コマンド送信
  ir_serial.write(0xB1);
  ir_serial.write(0x01);

  delay(200); // 0.2秒待つ

  // 仮想ボタン1を離した コマンド送信
  ir_serial.write(0xB2);
  ir_serial.write(0x01);

  delay(5000); // 5秒待つ
}