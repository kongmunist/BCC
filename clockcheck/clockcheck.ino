bool state = 0;
int outPin = 8; 

long lastTrig = 0;
bool otherstate = 0;
long period = 5000;

const int patternLen = 10;
bool pattern[patternLen] = {1,0,
                    0,1,0,0,0,0,0,1}; 
int patternIndex = 0;

const byte CLOCKOUT = 9; // Only for Arduino Uno

void setup() {
    // put your setup code here, to run once:
    
        // Timer setup
//     set up 8 MHz timer on CLOCKOUT (OC1A)
    pinMode (CLOCKOUT, OUTPUT); 
    // set up Timer 1
    TCCR1A = bit (COM1A0);  // toggle OC1A on Compare Match
    TCCR1B = bit (WGM12) | bit (CS10);   // CTC, no prescaling
    OCR1A =  0;       // output every cycle

    pinMode(outPin, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    
    if (micros() - lastTrig > period){
        patternIndex++;
        if (patternIndex == patternLen){
            patternIndex = 0;
            digitalWrite(outPin,false);
            delay(100);
        }
        otherstate = pattern[patternIndex];
        digitalWrite(outPin,otherstate);
        lastTrig = micros();
    }
}
