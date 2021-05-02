int readPin1 = A0;
int touchVal;
int pinVal;


int EWMAval = 0;
float alpha = .2;


long lastTime = 0;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
}

void loop() {
    pinVal = analogRead(readPin1);
//    EWMAval = (1-alpha)*EWMAval + alpha*pinVal;
    Serial.print("1000,");
//    Serial.println(pinVal-EWMAval);
//    Serial.println(EWMAval);
    Serial.println(pinVal);
        
}
