/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   创建一个BLE服务器，一旦我们收到连接，将会周期性发送通知

   T使用步骤：
   1. 创建一个 BLE Server
   2. 创建一个 BLE Service
   3. 创建一个 BLE Characteristic
   4. 创建一个 BLE Descriptor
   5. 开始服务
   6. 开始广播


*/
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>//0x2902（BLE2902） 就是标准的 Client Characteristic Configuration Descriptor，简称 CCCD
#include "common.h"
#include <WiFi.h> // 我想关掉wifi.

uint8_t txValue = 0;                        // 要发送的值, 我们打算发送数字, 这里是一个uint8_t类型的变量, 初始值为0, 之后这个值会++从而发送0,1,2,3...来演示
BLEServer *pServer = NULL;                   //BLEServer指针 pServer
BLECharacteristic *pTxCharacteristic = NULL; //声明一个用来定义一个特征的指针: BLECharacteristic指针 `pTxCharacteristic`
bool deviceConnected = false;                //本次连接状态
bool oldDeviceConnected = false;             //上次连接状态

// See the following for generating UUIDs: https://www.uuidgenerator.net/
// 在这个网站可以生成UUID.
#define SERVICE_UUID "12a59900-17cc-11ec-9621-0242ac130002" // UART service UUID
#define CHARACTERISTIC_UUID_RX "12a59e0a-17cc-11ec-9621-0242ac130002"
#define CHARACTERISTIC_UUID_TX "12a5a148-17cc-11ec-9621-0242ac130002"

// ESP32 (BLE Server)
// └── Service: 12a59900-...
//     ├── Characteristic: 12a5a148-... (TX)
//     │   ├── Property: Notify
//     │   └── Descriptor: 0x2902 (BLE2902)
//     └── Characteristic: 12a59e0a-... (RX)
//         └── Property: Write


//接下来给 BLEServer 设置回调函数.
//C++ 面向对象的核心用法之一：通过继承并重写回调函数（callbacks）来自定义行为。
// ESP32 BLE 框架使用回调函数来处理各种事件，比如：
    // 设备连接 / 断开
    // 主机写入特征值（Write）
    // 读取（Read）请求
    // 通知已确认（Indicate Confirm）
// 这些事件都不是你主动调用的，而是 事件触发时 ESP32 BLE 栈自动调用你注册的回调函数。这时候就需要你提供一份“回调逻辑”。

//继承自 BLEServerCallbacks 类，简单添加了两个我们自己的回调函数 onConnect 和 onDisconnect
class MyServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)  //onConnect()是BLE库提供的回调函数(虚函数, 还没被定义). 当有设备连接到 BLE Server 时会被调用。 onDisconnect()也是. 断开连接时会被调用。 这就是C++的多态.
    {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer *pServer)
    {
        deviceConnected = false;
    }
};

//继承自 BLECharacteristicCallbacks 类，重写回调函数 onWrite(). 这个虚函数会在 BLE 客户端写入数据到特征时被调用。
//
class MyCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string rxValue = pCharacteristic->getValue(); //接收信息

        if (rxValue.length() > 0)//长度大于0,说明收到字符串了
        { //向串口输出收到的值
            Serial.print("RX: ");
            for (int i = 0; i < rxValue.length(); i++)
                Serial.print(rxValue[i]);
            Serial.println();
        }
    }
};


//初始化BLE设备和服务
void BLE_Init(void){
     // 创建一个 BLE 设备
    BLEDevice::init("azazel's UART_BLE");
    //为什麽这样初始化而不是new一个 BLEDevice？因为 BLEDevice 是一个静态单例类, Singleton(工具类)，没有public成员! 不允许被实例化! 它的方法都是静态方法. 这种类的设计思想:
    //     不需要多个实例. 因为BLE 是设备级别的资源（类似于 UART、I2C 等外设）, 一个 ESP32 通常只提供一个 BLE 服务环境
    // ➤ 统一由静态函数操作 BLE 栈
    // 所以 BLEDevice 的所有成员函数都是 static 静态函数, 不需要也不允许创建对象


    // 创建一个 BLE 服务
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks()); //设置回调
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // 创建一个 BLE 特征
    pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
    pTxCharacteristic->addDescriptor(new BLE2902());
    BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
    pRxCharacteristic->setCallbacks(new MyCallbacks()); //设置回调

    pService->start();                  // 开始服务
    pServer->getAdvertising()->start(); // 开始广播
    Serial.println(" 等待一个客户端连接，且发送通知... ");
}


// BLE 循环处理函数
void BLE_LoopProc(void){
        // deviceConnected 已连接
    if (deviceConnected)
    {
        pTxCharacteristic->setValue(&txValue, 1); // 设置要发送的值为txValue,占1byte
        pTxCharacteristic->notify();              // 广播
        txValue++;                                // 改变要发送的数字
        delay(2000);                              // 如果有太多包要发送，蓝牙会堵塞, 所以延迟两秒
    }

    // disconnecting  断开连接
    if (!deviceConnected && oldDeviceConnected)
    {
        delay(500);                  // 留时间给蓝牙缓冲
        pServer->startAdvertising(); // 打开广播, 外界可以设备可以发现这个设备.
        Serial.println(" 开始广播 ");
        oldDeviceConnected = deviceConnected;
    }

    // connecting  正在连接
    if (deviceConnected && !oldDeviceConnected)
    {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}



void setup()
{
    //把默认打开的wifi关掉.
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);

    //把默认打开的蓝牙经典+BLE关掉.
    //btStop(); 



    Serial.begin(115200);
    BLE_Init(); //初始化BLE


}
    
   

void loop()
{
    BLE_LoopProc();
}