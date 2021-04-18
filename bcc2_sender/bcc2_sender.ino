int outpin = 8;
bool state = false;
long lastTime = 0;
long trigTime = 10;

float kiloh;
float freq = 10;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    
    pinMode(outpin,OUTPUT);
    lastTime = millis();
    kiloh = 1000/freq;
}

void loop() {
    // put your main code here, to run repeatedly:
//    if (millis()-lastTime > trigTime) {
//        digitalWrite(outpin, state);
//        state = !state;
//        lastTime = millis();
//        Serial.println(state);
//    }

    while (true) {
        PORTB = B00000001;
        delay(kiloh);
        PORTB = B00000000;
        delay(kiloh);
    }
    
}
