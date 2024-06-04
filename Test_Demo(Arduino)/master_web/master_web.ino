#include "BluetoothSerial.h"
#include <Arduino.h>
#include <WiFi.h>       //用于基础WiFi连接
#include <AsyncTCP.h>   //ESPAsyncWebServer.h的前置组件 这个库需要下载组件安装 https://github.com/me-no-dev/ESPAsyncWebServer
#include <ESPAsyncWebServer.h>  //用于websever和webstocket的建立 
#include "string.h"         //用于对字符串进行处理
#include <stdlib.h>        //用于整型转字符型
#include <cJson.h>         //用于解析json和构造json数据
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

#define LED_PIN   2
const int bootPin = 0; // BOOT按钮连接的引脚
BluetoothSerial SerialBT;
const char *pin = "1234"; // 蓝牙匹配代码
String slaveName = "ESP32-BT-Slave"; // 蓝牙从机名称
String myName = "ESP32-BT-Master"; // 蓝牙主机名称

const int x = 32;
const int y = 33;
int flag = 0;

#define T_S_pin   26 
#define led_pin   4            
#define ligth_pin 34


#define led_on  SerialBT.println('5')
#define led_off  SerialBT.println('6')

typedef struct {             //定义一个用户变量
  const char* u_nume ;
  const char* u_pawd ; 
}user;
user hujingxuan={     //用户实例化
.u_nume="221300",
.u_pawd="888888"
};

AsyncWebServer server(80);    //web端口号 80
const char* PARAM_MESSAGE = "usernum";  
char connet_flag=0;//是否建立stocketl连接标志

int Humidity,Temperature; //温湿度
static char *json_data; //json数据对象

const char* ssid = "OnePlus";        //wifi密码和名称
const char* password = "2206020409";



const char* web_main=
  "<!DOCTYPE html><html>"
  "<head>"
  "<meta charset=\"utf-8\">"
  "<title>测试网页</title>"
  "<style>"
  "body { font-family: Verdana, sans-serif; margin: 0; padding: 0; background: url('/img1.jpg') no-repeat center center fixed; background-size: cover; }"
  "form { width: 500px; margin: 50px auto; padding: 40px; background: #fff; border-radius: 10px; box-shadow: 2px 2px 20px rgba(0, 0, 0, 0.1); position:relative; }"
  "p { color: #333; }"
  "p.title { color: #19CAAD; font-size: 24px; font-weight: bold; }"
  "input[type=number], input[type=password] { width: calc(100% - 20px); padding: 15px; margin-top: 10px; margin-bottom: 20px; border: 1px solid #ddd; border-radius: 5px; }"
  "input[type=submit], input[type=reset] { padding: 15px 20px; border: none; border-radius: 5px; margin-top: 10px; cursor: pointer; }"
  "input[type=submit] { background-color: #19CAAD; color: white; }"
  "input[type=reset] { background-color: #f44336; color: white; }"
  "</style>"
  "</head>"
  "<body>"
  "<form action=\"/post\" method=\"post\">"
  "<p class=\"title\">微机原理登录</p>"
  "<p>账号:<input type=\"number\" name=\"usernum\" placeholder=\"请输入账号\" required=\"required\"></p>"
  "<p>密码:<input type=\"password\" name=\"pswd\" placeholder=\"请输入密码\" required=\"required\"></p>"
  "<p><input type=\"submit\"> <input type=\"reset\"></p>"
  "</form>"
  "</body>"
  "</html>";
String web_app = String("") +
"<DOCTYPE html>\n" +
"<html>\n" +
"<head>\n" +
" <meta charset=\"UTF-8\">\n" +
" <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n" +
" <title>智能温室控制系统</title>\n" +
" <style>\n" +
" body { margin: 0; padding: 0; font-family: Verdana, sans-serif; background-color: #f0f0f0; }\n" +
" #container { width: 80%; max-width: 800px; margin: 20px auto; background-color: #fff; border-radius: 10px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }\n" +
" #header { background-color: #19CAAD; color: white; text-align: center; padding: 10px; border-top-left-radius: 10px; border-top-right-radius: 10px; }\n" +

" button { background-color: #F4606C; color: white; padding: 10px 15px; border: none; border-radius: 5px; margin-top: 10px; cursor: pointer; }\n" +
" .info { color: #333; margin: 10px 0; }\n" +
" .data-display { color: #F4606C; }\n" +
" #menu { padding: 10px; }\n" +
" #content { background-color: #EEEEEE; padding: 10px; }\n" +
" #footer { background-color: #19CAAD; color: white; text-align: center; padding: 10px; border-bottom-left-radius: 10px; border-bottom-right-radius: 10px; }\n" +
" </style>\n" +
"</head>\n" +
"<body>\n" +
" <div id=\"container\">\n" +
" <div id=\"header\">\n" +
" <h1>智能探测系统</h1>\n" +
" </div>\n" +
" <div id=\"menu\">\n" +
" <b>菜单：</b><br>\n" +
" <button onclick=\"ledon()\">开灯</button><br>\n" +
" <button onclick=\"ledoff()\">关灯</button><br>\n" +
" <button onclick=\"change()\">点击改变数值</button>\n" +
" <div class=\"info\">当前温室温度：<span class=\"data-display\" id=\"TemperatureIntensity\">00</span>℃</div>\n" +
" <div class=\"info\">当前温室湿度：<span class=\"data-display\" id=\"HumidityIntensity\">00</span>%</div>\n" +


" 版权 © UPC12138.com\n" +
" </div>\n" +
" </div>\n" +
" <script>\n" +
" var ws;\n" +
" var debugMessages = [];\n" +
" window.onload = function () {\n" +
" if (\"WebSocket\" in window) {\n" +
" ws = new WebSocket(\"ws://\" + window.location.host + \"/\");\n" +
" ws.onopen = function () {\n" +
" document.getElementById(\"info\").innerHTML += \"WebSocket连接成功!<br>\";\n" +
" ws.send(\"connect ok!\");\n" +
" };\n" +
" ws.onmessage = function (evt) {\n" +
" var obj = JSON.parse(evt.data);\n" +
" document.getElementById(\"TemperatureIntensity\").innerHTML = obj.Temperature;\n" +
" document.getElementById(\"HumidityIntensity\").innerHTML = obj.Humidity;\n" +
" document.getElementById(\"LightIntensity\").innerHTML = obj.light;\n" +
" debugMessages.unshift('温度: ' + obj.Temperature + ' 湿度: ' + obj.Humidity + ' 光照: ' + obj.light + \"<br>\");\n" +
" if (debugMessages.length > 10) debugMessages.pop();\n" +
" document.getElementById(\"info\").innerHTML = debugMessages.join(\"\");\n" +
" };\n" +
" ws.onerror = function () {\n" +
" document.getElementById(\"info\").innerHTML += \"WebSocket通讯错误!<br>\";\n" +
" };\n" +
" ws.onclose = function () {\n" +
" document.getElementById(\"info\").innerHTML += \"WebSocket连接已关闭!<br>\";\n" +
" };\n" +
" } else {\n" +
" document.getElementById(\"info\").innerHTML = \"您的浏览器不支持 WebSocket!\";\n" +
" }\n" +
" };\n" +
" function ledon() {\n" +
" ws.send(\"led_on\");\n" +
" }\n" +
" function ledoff() {\n" +
" ws.send(\"led_off\");\n" +
" }\n" +
" function change() {\n" +
" document.getElementById(\"LightIntensity\").innerHTML = \"50\";\n" +
" }\n" +
" </script>\n" +
"</body>\n" +
"</html>";
void data_pick()//采集外设数据，并打包成json发送到客户端
{
	cJSON *TCP = cJSON_CreateObject();				//创建一个对象
	
	cJSON_AddNumberToObject(TCP,"light",analogRead(ligth_pin));	//构造json数据
	cJSON_AddNumberToObject(TCP,"Humidity",Humidity);	    	//添加整型数字 
	cJSON_AddNumberToObject(TCP,"Temperature",Temperature);	//添加浮点型数字
	json_data = cJSON_Print(TCP);				//JSON数据结构转换为JSON字符串

}
void notFound(AsyncWebServerRequest *request) {       //客户端错误请求时调用
    request->send(404, "text/plain", "Not found");
}

AsyncWebSocket ws("/"); // WebSocket对象，url为/
void data_deal(char* resivedata)//数据处理函数，对客户端发来的数据进行解析，如果执行比较大的程序，比如刷新led建议标记，在主循环处理。
{
   Serial.printf("这里是数据处理函数%s\n", resivedata);
   if(strcmp(resivedata,"led_off")==0){
     led_on;
   }
   else if(strcmp(resivedata,"led_on")==0){
     led_off;
   }
   else{
     Serial.printf("对不起没有找到指令:%s\n", resivedata);
   }

}
// WebSocket事件回调函数
uint32_t clientID=0;   //用于存储连接对象的id
void onEventHandle(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  if (type == WS_EVT_CONNECT) // 有客户端建立连接
  {
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    clientID= client->id();
    client->printf("Hello Client %u !", client->id()); // 向客户端发送数据
    client->ping();                                    // 向客户端发送ping
  }
  else if (type == WS_EVT_DISCONNECT) // 有客户端断开连接
  {
    //Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
    connet_flag=0;
    Serial.printf("服务端断开连接\n");
  }
  else if (type == WS_EVT_ERROR) // 发生错误
  {
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
  }
  else if (type == WS_EVT_PONG) // 收到客户端对服务器发出的ping进行应答（pong消息）
  {
    Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "");
  }
  else if (type == WS_EVT_DATA) // 收到来自客户端的数据
  {
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    Serial.printf("ws[%s][%u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(), info->num, (info->message_opcode == WS_TEXT) ? "text" : "binary", info->index, info->index + len);
    data[len] = 0;
    data_deal((char *)data);
    Serial.printf("%s\n", (char *)data);
  }
}
void tim1Interrupt()
{
   if(connet_flag)//如果连接打开
    {
      data_pick();
     // Serial.printf("%s\n", json_data);
      ws.printf(clientID, json_data);//向建立连接的客户端发送信息
      ws.cleanupClients();     // 关闭过多的WebSocket连接以节省资源
     
    } 
    else{
      // Serial.printf("等待连接建立...\n"); 
    }
}

static TimerHandle_t timer1_Handle=NULL;
static TimerHandle_t timer2_Handle=NULL;

void timer_callback();
void timer2_callback();
void setup() {
  Serial.begin(115200);

  pinMode(led_pin, OUTPUT); // 将LED引脚设置为输出模式
  digitalWrite(led_pin, LOW); // 关闭LED

  SerialBT.begin(myName, true); // 启动蓝牙串口
  Serial.printf("The device \"%s\" started in master mode, make sure slave BT device is on!\n", myName.c_str());
  SerialBT.setPin(pin); // 设置配对代码

  Serial.printf("Connecting to slave BT device named \"%s\"\n", slaveName.c_str());
  if (SerialBT.connect(slaveName)) {
    Serial.println("Connected Successfully!");
  } else {
    Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
  }

  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(bootPin, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);     //wifi 的打开和连接
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());   //获取到的ip地址，这个地址之后要显示在屏幕上

      ws.onEvent(onEventHandle); // WebSocket事件回调函数
      server.addHandler(&ws);    // 将WebSocket添加到服务器中

      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){   //url 主页面请求
          request->send(200, "text/html",web_main);
      });

      server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){ //账户密码提交页面请求
          String message;
          char resive_name[10]={0},   //存放客户端发来的账号
                resive_pswd[10]={0};   //存放客户端发来的密码
          if (request->hasParam("usernum", true)) {  //找usernum这个键
              strcpy(resive_name,request->getParam("usernum", true)->value().c_str());
              Serial.printf("usernum: %s\n",resive_name);
          }
          if (request->hasParam("pswd", true)){//找pswd这个键
            // message = request->getParam("pswd", true)->value();
              strcpy(resive_pswd,request->getParam("pswd", true)->value().c_str());
              Serial.printf("pswd: %s\n",resive_pswd);
          }
          if(strcmp(resive_name,hujingxuan.u_nume)==0){ //得到提交数据之后开始密码校验
            Serial.printf("已找到用户:%s,开始密码校验...\n",resive_name);
            if(strcmp(resive_pswd,hujingxuan.u_pawd)==0){
            Serial.printf("用户密码正确!\n");
            connet_flag=1;
            request->send(200, "text/html",web_app);
            }
            else{
            Serial.printf("对不起，您输入的密码有误!\n");
            }
          }
          else{
            request->send(200, "text/html",web_main);
            Serial.printf("找不到指定用户，请重新输入!\n");
          }
      });
      server.onNotFound(notFound);
      server.begin();
    
  //开启一个freertos定时器，注意，定时器1不能时间间隔太短否则会导致消息堆积，发不出去
  timer1_Handle=xTimerCreate("timer1_Handle",250,pdTRUE,(void*)1,(TimerCallbackFunction_t )timer_callback);
  if(timer1_Handle!=NULL){xTimerStart(timer1_Handle,0);}

  timer2_Handle=xTimerCreate("timer2_Handle",1000,pdTRUE,(void*)2,(TimerCallbackFunction_t )timer2_callback);
  if(timer2_Handle!=NULL){xTimerStart(timer2_Handle,0);}
  Serial.printf("初始化结束\n");

}
unsigned char time1_flag=0,time2_flag=0;
void loop() {
  int x_value = analogRead(x);
  int y_value = analogRead(y);

  Serial.print(x_value);
  Serial.print(",");
  Serial.println(y_value);

 if (digitalRead(bootPin) == LOW) {
    digitalWrite(2, HIGH);
    SerialBT.println('A');
    delay(100);
  } 
  else {
    digitalWrite(2, LOW);
    SerialBT.println('B');
    delay(100);
  }

  if (y_value >= 4000 || (x_value >= 4000 && y_value >= 4000)) {
    flag = 4;
    Serial.println(4);
    SerialBT.println('4');
    delay(100);
  } else if (x_value <= 100) {
    flag = 2;
    Serial.println(2);
    SerialBT.println('2');
    delay(100);
  } else if (x_value >= 4000) {
    flag = 3;
    Serial.println(3);
    SerialBT.println('3');
    delay(100);
  } else if (y_value <= 100) {
    flag = 1;
    Serial.println(1);
    SerialBT.println('1');
    delay(100);
  } else if(2500<=x_value<=3000&&2500<=y_value<=3000){
    flag = 0;
    Serial.println(0);
    SerialBT.println('0');
    delay(100);
  }

  if(time1_flag)
   {
     time1_flag=0;
     tim1Interrupt(); //定时回调
   }
   if(time2_flag)
   {
     time2_flag=0;
     /* if(((int)DHT11.getHumidity()<500)&&((int)DHT11.getTemperature()<500))//滤除错误数据
      {
      float   Humidity=dhtSensor.readHumidity();//(int)DHT11.getHumidity();
      float  Temperature=dhtSensor.readTemperature();//(int)DHT11.getTemperature();
        Serial.printf("Humidity=%d,Temperature=%d\n",(int)DHT11.getHumidity(),(int)DHT11.getTemperature());
      }*/
   }

  //delay(100);
}

void timer_callback()//注意，这个函数还是在内部任务调用的，所以不能放太多内容，否则会堆栈溢出
{
  time1_flag=1;
}
void timer2_callback()
{
  time2_flag=1;
}

