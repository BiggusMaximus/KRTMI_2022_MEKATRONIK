#include <ESP8266WiFi.h>
#include <espnow.h>
#define in1 D0
#define in2 D1
#define in3 D2
#define in4 D3
#define enA D5
#define enB D6
unsigned char pwmA = 100;
unsigned char pwmB = 100;
unsigned char pwmRendah = 60;

typedef struct struct_message{
  bool y_value, sw_value;
  short x_value;
}struct_messange;

struct_message myData;
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println("Nilai x : " + String(myData.x_value) + "   | Nilai y : " + String(myData.y_value) + "  | Nilai sw : " + String(myData.sw_value));
  if(myData.x_value > 900){
    kanan();
  }
  else if(myData.x_value < 800){
    kiri();
  }
  if(myData.y_value == HIGH){
    maju();
  }
  if(myData.sw_value == LOW){
    berhenti();
  }
}

// Callback


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  digitalWrite(enA, 0);
  digitalWrite(enB, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void maju(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, pwmA);
  analogWrite(enB, pwmB);
  Serial.println("Maju");
}
void kiri(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, pwmA);
  analogWrite(enB, pwmB);
  Serial.println("Kiri");
}
void kanan(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, pwmA);
  analogWrite(enB, pwmB);
  Serial.println("Kanan");
}
void mundur(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, pwmA);
  analogWrite(enB, pwmB);
  Serial.println("Mundur");
}

void berhenti(){
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  Serial.println("Berhenti");
}
