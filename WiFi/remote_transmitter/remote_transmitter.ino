#include <espnow.h>
#include <ESP8266WiFi.h>

#define xpin A0
#define ypin D1
#define swpin D2
bool y, sw;
short x;

uint8_t broadcastAddress[] = {0x50, 0x02, 0x91, 0xC3, 0x34, 0xFA};

typedef struct struct_message{
  bool y_value, sw_value;
  short x_value;
}struct_messange;

// Buat Objek
struct_message myData;


// Callback kalo data udah terkirim
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // WiFi station mode
  WiFi.mode(WIFI_STA);
  
  // Initilize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  // Register the send callback
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(swpin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  x = analogRead(xpin);
  y = digitalRead(ypin);
  sw = digitalRead(swpin);
  Serial.println("Nilai x : " + String(x) + "   | Nilai y : " + String(y) + "  | Nilai sw : " + String(sw));
 
  myData.y_value = y;
  myData.x_value = x;
  myData.sw_value = sw;
  
  // Send message via ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  
  delay(100);
} 
