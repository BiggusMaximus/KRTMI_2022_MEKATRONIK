#define x A0
#define sw 2
int16_t value_x;
bool value_sw;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(x, INPUT);
  pinMode(sw, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  value_x = analogRead(x);
  value_sw = digitalRead(sw);
  Serial.println("NIlai x : " + String(value_x) + "NIlai sw : " + String(value_sw)); 
  delay(200);
}
