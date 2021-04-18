int readPin1 = A0;
int readPin2 = A1;
int touchVal;
int pinVal;

long lastTime = 0;
long trigTime = 10;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
}

void loop() {
    if (millis()-lastTime > trigTime) {
        touchVal = analogRead(readPin1);
        pinVal = analogRead(readPin2);
        Serial.print("1000,");
        Serial.print(pinVal);
        Serial.print(",");
        Serial.println(touchVal);
        
        lastTime = millis();
    }
    
}
