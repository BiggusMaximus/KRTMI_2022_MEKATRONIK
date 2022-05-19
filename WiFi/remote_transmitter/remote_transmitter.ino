#include <espnow.h>
#include <ESP8266WiFi.h>

 
#define pin_maju D1
#define pin_mundur D2
#define pin_kiri D3
#define pin_kanan D4
#define pin_capit_gigit D5
#define pin_capit_lepas D6

bool maju, mundur, kiri, kanan, capit_gigit, capit_lepas;

uint8_t broadcastAddress[] = {0x50, 0x02, 0x91, 0xC3, 0x34, 0xFA};

typedef struct struct_message{
  bool nilai_maju, nilai_mundur, nilai_kiri, nilai_kanan, nilai_capit_gigit, nilai_capit_lepas;
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
  

  pinMode(pin_maju        , INPUT_PULLUP);
  pinMode(pin_mundur      , INPUT_PULLUP);
  pinMode(pin_kiri        , INPUT_PULLUP);
  pinMode(pin_kanan       , INPUT_PULLUP);
  pinMode(pin_capit_gigit , INPUT_PULLUP);
  pinMode(pin_capit_lepas , INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  maju        = digitalRead(pin_maju);
  mundur      = digitalRead(pin_mundur);
  kiri        = digitalRead(pin_kiri);
  kanan       = digitalRead(pin_kanan);
  capit_gigit = digitalRead(pin_capit_gigit);
  capit_lepas = digitalRead(pin_capit_lepas);
  Serial.println("Nilai maju : " + String(maju) + "   | Nilai mundur : " + String(mundur) + "  | Nilai kiri : " + String(kiri)+ "  | Nilai kanan : " + String(kanan)+ "  | Nilai gigit : " + String(capit_gigit) +  "  | Nilai lepas : " + String(capit_lepas));
 
  myData.nilai_maju         = maju;
  myData.nilai_mundur       = mundur;
  myData.nilai_kiri         = kiri;
  myData.nilai_kanan        = kanan;
  myData.nilai_capit_gigit  = capit_gigit;
  myData.nilai_capit_lepas  = capit_lepas;
  
  // Send message via ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  
  delay(100);
} 
