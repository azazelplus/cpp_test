
#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup()
{
    Serial.begin(115200);
    SerialBT.begin("azazel's esp32"); // 如果没有参数传入则默认是蓝牙名称是: "ESP32"
    //SerialBT.setPin("1234");   // 蓝牙连接的配对码
    Serial.printf("BT initial ok and ready to pair. \r\n");
}

void loop()
{
    if (Serial.available())//如果串口有信息
    {
        SerialBT.write(Serial.read());//用蓝牙发送出去
    }
    if (SerialBT.available())//如果蓝牙收到信息
    {
        Serial.write(SerialBT.read());//用串口打印出来
    }
    delay(1);
}