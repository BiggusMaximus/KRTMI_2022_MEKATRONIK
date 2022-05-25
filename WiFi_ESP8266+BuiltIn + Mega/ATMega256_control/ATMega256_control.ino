#define xpin A0
#define ypin A1
#define swpin 2

int16_t x_value,y_value;
bool sw_value;
String kirim = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(115200);
  pinMode(swpin, INPUT_PULLUP);
  pinMode(ypin, INPUT);
  pinMode(xpin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  x_value   = analogRead(xpin);
  y_value   = analogRead(ypin);
  sw_value  = digitalRead(swpin);
  //Serial.println("Nilai x : " + String(x_value) + " | Nilai y : " + String(y_value) + " | Nilai switch : " + String(sw_value));

  kirim = "";
  kirim += x_value;
  kirim += ";";
  kirim += y_value;
  kirim += ";";
  kirim += sw_value;
 
  Serial3.println(kirim);
  
  delay(100);
}
