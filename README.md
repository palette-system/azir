# 概要
<img src="/images/gaiyo.png"><br>
<br>
azir（エーゼット、アイアール）は自作の赤外線キーボードを誰もが作れるようにするためのプロジェクトです。
<br><br>

<b>簡単に作れる</b><br>
AZIR50を使用すればスイッチと電池を繋ぐだけで赤外線キーボードになります。<br>
送信している信号がとてもシンプルなので自前の赤外線キーボードを作る事も用意です。<br>

リンク： <a href="/docs/command.md">AZIR 通信コマンド</a><br>

<br><br>

<b>長時間動作</b><br>
BLEや電波を使用せず赤外線LEDを光らせるだけなのでボタン電池で長時間動作します。<br>
<br><br>

## AZSENSOR
AZSENSOR（エーゼット、センサー）は赤外線キーボードの信号を受け取るためのセンサーです。<br>
中身はただの赤外線センサーで、より広範囲の赤外線信号を受け取るためのセンサーです。<br>
これを使用しなくても赤外線用のフォトトランジスタをESP32S3に接続するだけでも赤外線キーボードとして使用する事ができます。(ただし受光角度が30°しかなかったりします)<br>

<br><br>

## AZSENSOR ファームウェア
QMKやPRKのような位置づけになりますが、キーボード別にコードを書いたりコンパイルする必要はありません。<br>
ファームウェア書き込みサイトからESP32S3に書き込みを行うだけで様々なキーボードで使用できます。<br>
キー配列やキーマップの設定はAZTOOLから行います。<br>
<br>
リンク： <a href="https://palette-system.github.io/az-core/azsensor.html">AZSENSORファームウェア</a><br>

<br><br>

## AZTOOL
REMAPやVIALのような位置づけで、自前で作成したキーボードのキー配列の登録やキーマップの設定を行えます。<br>
新しいキーボードを作った場合に申請は必要なく、キー配列の設定も含めてAZTOOL上でGUIで設定できます。<br>
<br>
リンク： <a href="https://palette-system.github.io/aztool/">AZTOOL</a><br>

<br><br>

## AZIR50
AZIR50（エーゼット、アイアール、フィフティ）は接続されたスイッチをキースキャンしてボタンが押されたら押下コマンドを赤外線で送信するマイコンボードです。<br>
ProMicroやRP2040ボードのような位置づけです、あらかじめファームウェアが書き込まれているので開封して電池を接続するだけで動作します。<br>
COL1～5、ROW1～5のピンがあるのでそのピンを使用して下さい。<br>
電池は1.8V～5.5V内の電池を接続して下さい。ボタン電池（CR2032）1つで連続稼働10日以上動作しました。<br>

<br><br>

# ライセンス
MIDライセンスとします。<br>
ドキュメント、ファームウェア、Github上にあるソースは好きに使って頂いて大丈夫です。<br>
ただし発生した問題、不具合は自己責任とし、パレットシステムはいかなる責任も持ちません。<br>

