# 簡単に赤外線キーボードを試す

## ESP32S3の配線
XIAO ESP32S3に赤外線用のフォトトランジスタを接続するだけでAZSENSORの変わりが作成できます。<br>
秋月電子で購入できる「L-51ROPT1D1」などがお手頃です。<br>
<br>
秋月電子 リンク： <a href="https://akizukidenshi.com/catalog/g/g118078/" target="_blank">XIAO ESP32S3</a><br>
秋月電子 リンク： <a href="https://akizukidenshi.com/catalog/g/g104211/" target="_blank">L-51ROPT1D1</a><br>
<br>
<b>配線</b><br>
<img src="/images/azsensor.png">
<br>
<br>

<b>XIAO ESP32S3のファームウェア</b><br>
AZSENSORのファームウェアをそのまま使用します。<br>
ファームウェアの書き込み手順は下記を参照して下さい。<br>
<br>
リンク： <a href="https://palette-system.github.io/az-core/azsensor.html" target="_blank">AZSENSORのファームウェア</a><br>

<br>
<br>

## ProMicroの配線
ProMicroを赤外線キーボードにするための配線例を紹介します。<br>
秋月電子で購入できる「OSI5LA5113A」などがお手頃です。<br>
<br>
秋月電子 リンク：　<a href="https://akizukidenshi.com/catalog/g/g112612/" target="_blank">OSI5LA5113A</a><br>
<br>
<b>配線</b><br>
<img src="/images/promicro_send.png">
<br>
<br>

<b>ProMicroのファームウェア</b><br>
ArduinoIDEでキー入力するサンプルを紹介します。<br>
5秒おきに仮想キー1を押して離すだけをするサンプルです。<br>
<br>
サンプルソースコード リンク：　<a href="/firmware/ir_send_sample_promicro/ir_send_sample_promicro.ino" target="_blank">ir_send_sample_promicro.ino</a><br>
<br>
<b>ソースコード</b><br>
<img src="/images/ir_send_sample.png">
<br>
<br>

## キーボードの登録
AZTOOLを使用してESP32S3にキーボードとして登録します。<br>
<br>
リンク： <a href="/docs/add_option.md">AZSENSORにキーボードを追加する手順</a><br>
