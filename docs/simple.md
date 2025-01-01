# 簡単に赤外線キーボードを試す

## ESP32S3の配線
ESP32S3に赤外線用のフォトトランジスタを接続するだけでAZSENSORの変わりが作成できます。<br>
秋月電子で購入できる「L-51ROPT1D1」などがお手頃です。<br>
<br>
秋月電子 リンク： <a href="https://akizukidenshi.com/catalog/g/g104211/" target="_blank">L-51ROPT1D1</a><br>
<br>
<b>配線</b><br>
<img src="/images/azsensor.png">
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

## ProMicroのファームウェア
ArduinoIDEでキー入力するサンプルを紹介します。<br>
5秒おきに仮想キー1を押して離すだけをするサンプルです。<br>
<br>
サンプルソースコード リンク：　<a href="/firmware/ir_send_sample_promicro/ir_send_sample_promicro.ino" target="_blank">ir_send_sample_promicro.ino</a><br>
<br>
<b>ソースコード</b><br>
<img src="/images/ir_send_sample.png">
<br>
