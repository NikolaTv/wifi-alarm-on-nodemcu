//НИКОЛА ТВ https://www.youtube.com/channel/UCiZWRDeZZMV_8MTkpk1hkXg

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//ВНИМАНИЕ! ПЕРЕД ПРОШИВКОЙ ОТКЛЮЧИТЕ ПИН D8 ОТ ПЛАТЫ, ИНАЧЕ ПЛАТА МОЖЕТ НЕ ПРОШИВАТЬСЯ
//для пршивки я выбирал NodeMCU 1.0 
//никаких настроек дополнительно не менял. только указал ком-порт к которому подключена плата

//первоначальная настройка
//1.Установка драйверов CP2102 или CH340
//2.Перейти в Файл -> настройки и вставить дополнительную ссылку менеджера плат http://arduino.esp8266.com/stable/package_esp8266com_index.json
//3.Перейти Инструменты -> Плата -> Менеджер плат найти в поиске ESP8266 и установить версию 2.5.2(на других версиях может не работать)
//4.Настроить настройки ниже и загрузить прошивку
//не забудь прочитать README

//НАСТРОЙКИ
#define ssid "test" //имя wifi
#define pass "test1234" //пароль wifi
#define token "4cd4182400c104ceaca7930d35b34f57" //токен, который получили у бота
#define level HIGH //HIGH(если датчик высокого уровня)/LOW(если датчик низкого уровня)
//НАСТРОЙКИ

void setup() {
Serial.begin(115200);
}

bool st = false;

void loop() {
if(digitalRead(D6) == level){
  st = true;
}

if(st == true){
send();
delay(5000);
st = false;
}

}

void send(){
WiFi.begin(ssid, pass);   //WiFi connection
delay(5000);
//HTTPClient.begin();

while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
delay(500);
Serial.println("Waiting for connection");
}
if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
HTTPClient http;    //Declare object of class HTTPClient
http.begin("http://api.zhmail.ru/bots/security/arduino.php");      //Specify request destination
http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
int httpCode = http.POST("token="token);   //Send the request
String payload = http.getString();                  //Get the response payload
Serial.println(httpCode);   //Print HTTP return code
Serial.println(payload);    //Print request response payload
http.end();  //Close connection
WiFi.mode(WIFI_OFF);
}else{
Serial.println("Error in WiFi connection");
}

}
