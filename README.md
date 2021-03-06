# IoT Dojo

## 概要

IoTの開発ができる人を増やそう!

## 日程案

勉強会を2日間行い、その後2週間チームで開発を行う

1日目
- 勉強会 10:00-17:00
  - ArduinoDojoのESP32版 10:00-14:00
  - Faboで遊ぶ 14:00-15:30
  - ESP32勉強会 15:00-17:00

2日目
- 13:20-15:00 ESP32勉強会
- 15:10-16:20 アイデアソン

## 教える順番

### ArduinoDojoのESP32版

1. イントロ:マイコンの概要
2. Arduino IDEのsetup
3. ESP32のsetup
4. Lチカ
5. アナログ出力
6. ボタン入力&シリアル通信(出力)
8. シリアル通信の入力
9. 時間処理

### Faboで遊ぶ

好きなFaboのパーツを使わせ、自分で調べて自分で実装させます。

### ESP32勉強会

1. WebHookの使い方(HTTPリクエスト)
2. WebサーバへのHTTPリクエスト
3. ESP32をWebサーバにする

### アイデアソン

チームで何を作るかを考える。

## 具体的な内容

### ArduinoDojoのESP32版

## 1. イントロ

* マイコンとは
* Arduinoの説明

## 2. ArduinoIDEのsetup

## 3. Lチカ

1. プログラムの作成

* setup,loopの説明
* pinMode
* digitalWrite
* delay

2. コンパイル&書き込み
3. 回路の説明

* LEDについての説明
* 簡単な抵抗の計算

4. ブレッドボードの説明
5. 回路の製作

## 4. アナログ出力

LEDをじょじょに明るくしたり、暗くしたりする

1. プログラムの作成

* ledcWriteについて
* 雑にPWMの説明(知らなくても使えるから)

2. 書き込み

## 5. ボタン入力&Serial出力

ボタンを押している間LEDが光る

1. プログラムの作成

* pinMode
* digitalRead
* Serialについて

2. 回路の説明

* ボタンについて
* 負論理
* プルアップについて

3. プログラムの書き込み
4. 回路の製作
5. シリアルモニタを見る

## 6. Serialの入力

1. プログラムの作成

* Serial入力について

3. 書き込み
4. 回路製作
5. シリアルモニタから入力してテスト

## 8. 時間処理

1. プログラムの作成

* 時間処理で別々のプロセスの処理の仕方

2. 書き込み
3. 回路製作

## スライドは以下を参照

[IoTDojo Things編](https://docs.google.com/presentation/d/1JS-oxG0eDSsEBJlCSfgKwuFwBgofehyfCaODZOZSojU/edit?usp=sharing)  
[IoTDojo Internet編](https://docs.google.com/presentation/d/1p7NkKNRmOBm9MeIX_MDrqPcki5ktiqoi7-hBQ6IcLKo/edit?usp=sharing)
## 他にも案があれば、Issueにどうぞ
