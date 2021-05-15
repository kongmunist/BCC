int inPin = A0;

int lastReading = 0;
int curReading = 0;

// Reading pattern
const int patternLen = 10;
bool pattern[patternLen] = {0,0,
                    0,0,0,0,0,0,0,0}; 
int patternIndex = 0;
long assumedPeriod = 4950;

bool refPattern [patternLen] = {1,0,
                    0,1,0,0,0,0,0,1}; 

void setup() {
    Serial.begin(115200);
    pinMode(inPin,INPUT);

}

void loop() {
    curReading = analogRead(inPin);
    if ((curReading - lastReading) > 50){
        // Read for 10 bytes
        pattern[0] = 1;
        for (int i = 1; i < patternLen; i++){
            delayMicroseconds(assumedPeriod);
            curReading = analogRead(inPin);
            pattern[i] = (curReading - lastReading) > 50;
        }

//        // Print out pattern
//        for (int i = 0; i < patternLen; i++){
//            Serial.print(pattern[i]);
//            Serial.print(", ");
//        }
//        Serial.println();

        // Check if it matches
        bool allMatch = true;
        for (int i = 0; i < patternLen; i++){
            allMatch = allMatch & (pattern[i] == refPattern[i]);
        }
        if (allMatch){
            Serial.println("Andy Detected!");
        }
        
        

        // Reset array
        for (int i = 0; i < patternLen; i++){
            pattern[i] = 0;
        }
    }
    
//    Serial.print("1000,");
//    Serial.println(curReading); 
    lastReading = curReading;
}
