# serial_servo

## boostを用いたserial通信servoのプログラム
* Futaba
* KondoB3M
* test
 ### 使用方法
 `$ git clone https://github.com/RikiHayashi/serial_servo.git`  
 boostのインストール
 ### Futaba
 * ttyUSB0が認識しない時
 ```bash
  $ sudo modprobe ftdi-sio  
  $ sudo chmod 777 /sys/bus/usb-serial/drivers/ftdi_sio/new_id
  $ sudo echo "1115 0008" > /sys/bus/usb-serial/drivers/ftdi_sio/new_id
  $ sudo chmod +x /dev/ttyUSB0
 ```
 * ``futaba``内のsample実行法
 ```
  $ cd futaba
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make 
  $ cp ../offset.txt .
  $ ./futaba
 ```
 複数のサーボを同一のコマンドで動かす
 ### KondoB3M
 * ttyUSB0が認識しない時
 ```
  $ sudo su
  $ modprobe ftdi-sio
  $ echo 165C 0009 > /sys/bus/usb-serial/drivers/ftdi_sio/new_id
  $ exit
 ```
 * ``kondo_b3m``内のsample実行法
 ```
  $ cd kondo_b3m
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make 
  $ ./kondo_b3m
 ```
 1つのサーボを動かす。
 ### test
 ```
  $ cd serial_servo/test  
  $ g++ -std=c++11 test.cpp -o test -lboost_system  
  $ ./test
 ```
 コマンドのパケット毎の値やチェックサムの計算などのtestプログラム  
 
 
