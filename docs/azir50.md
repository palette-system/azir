# AZIR50
<br>
<table><tr><td>
<img src="/images/azir50_pcb_t.png">
</td><td>
<img src="/images/azir50_pcb_b.png">
</td></tr></table>
<br>
AZIR50は最大50キーのキースキャンを行い赤外線で信号を送るボードです。<br>
消費電力が少なくボタン電池1つで動作します。(対応電圧は1.8～5.5V)<br>

<br><br>

## SETボタン
AZIR50を起動してから1.5秒以内にSETボタンを押すと設定モードで起動します。<br>
設定モードではスキャンのタイプ、送信する仮想ボタンの番号を変更できます。<br>

<br><br>

## 必要な配線
VCCとGNDに電池、IRとVCCに赤外線LED、SETとGNDの間にSETボタンを接続して下さい。<br>
SETボタンはスキャンタイプなどの設定のために必要で、設定済みのAZIR50を接続する場合はSETボタンの接続は不要です。<br>
<br>
<img src="/images/azir50_def.png"><br>

<br><br>

## ダイレクトスキャン
R1～5、C1～5のピンそれぞれがGNDに接続されると押下になります。<br>
最大10キーとなります。<br>
<br>
<img src="/images/azir50_direct.png"><br>

<br><br>

## 通常マトリックススキャン
R1～5からC1～5のピンに接続されると押下になります。<br>
最大25キーとなります。<br>
<br>
<img src="/images/azir50_matrix.png"><br>

<br><br>

## 倍マトリックススキャン
通常マトリックス同様にR1～5からC1～5のピンに接続と、逆方向のC1～5からR1～5のピンに接続されると押下になります。<br>
最大50キーとなります。<br>
<br>
<img src="/images/azir50_double_matrix.png"><br>

<br><br>

