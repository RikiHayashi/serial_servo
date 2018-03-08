# serial_servo

## boostを用いたserial通信servoのプログラム
* Futaba
* KondoB3M
* test
 ### 使用方法
 `$ git clone https://github.com/RikiHayashi/serial_servo.git`  
 boostのインストール
 ### Futaba
 ```bash
  $ sudo modprobe ftdi-sio  
  $ sudo chmod 777 /sys/bus/usb-serial/drivers/ftdi_sio/new_id
  $ sudo echo "1115 0008" > /sys/bus/usb-serial/drivers/ftdi_sio/new_id
  $ sudo chmod +x /dev/ttyUSB0
 ```
 ### KondoB3M
 ```
  $ sudo su
  $ modprobe ftdi-sio
  $ echo 165C 0009 > /sys/bus/usb-serial/drivers/ftdi_sio/new_id
  $ exit
 ```
 ### test
 ```
  $ cd serial_servo/test  
  $ g++ -std=c++11 test.cpp -o test -lboost_system  
  $ ./test
 ```
