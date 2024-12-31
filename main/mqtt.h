#include <ArduinoMqttClient.h>
#include <WiFi.h>

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);








const char broker[] = "broker.emqx.io";
int        port     = 1883;
const char topic[]  = "/Arduino/data";
bool mqttConnected  = false;


void onMqttMessage(int messageSize) {
  String msg;
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  while (mqttClient.available()) {
    msg += (char)mqttClient.read();
  }

  int separatorIndex = msg.indexOf(':');
  if (separatorIndex > 0) {
    String pinStr = msg.substring(0, separatorIndex);
    String stateStr = msg.substring(separatorIndex + 1);
    int pin = pinStr.toInt();
    int state = stateStr.toInt();
    if(state == 1)
      digitalWrite(pin, ACTIVATE);
    else
      digitalWrite(pin, DEACTIVATE);
  }
  Serial.println(msg);
}


void mqttConnect() {
  Serial.println("[MQTT] Connecting");
  if (!mqttClient.connect(broker, port)) {
    Serial.print("[MQTT] Connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    mqttConnected = false;
  }
  else {
    Serial.println("[MQTT] connected");
    mqttClient.onMessage(onMqttMessage);
    mqttClient.subscribe(topic);
    mqttConnected = true;
  }
}


void mqttLoop() {
  if(mqttConnected) {
    mqttClient.poll();
  }
  else {
    if(internetConnected)
      mqttConnect();
    else if(mqttConnected)
      mqttConnected = false;
  }
}