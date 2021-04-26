int outpin = 8;
float kiloh;
float freq = 10;

bool ones = false;
long lastTime = 0;
long now;

// Timer output
const byte CLOCKOUT = 9; // Only for Arduino Uno
#define NOP __asm__ __volatile__ ("nop\n\t")



void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    
    pinMode(outpin,OUTPUT);
    lastTime = millis();
    kiloh = 1000000/freq;
    kiloh = 1.0;

//    // Timer setup
//    // set up 8 MHz timer on CLOCKOUT (OC1A)
//    pinMode (CLOCKOUT, OUTPUT); 
//    // set up Timer 1
//    TCCR1A = bit (COM1A0);  // toggle OC1A on Compare Match
//    TCCR1B = bit (WGM12) | bit (CS10);   // CTC, no prescaling
//    OCR1A =  0;       // output every cycle
}

void loop() {
    if(micros()-lastTime > 100000){
        lastTime = micros();
        ones = !ones;
        
//        if (ones){
//            PORTB = B00000001;
//        } else{
//            PORTB = B00000000;
//        }
    }

    
    if (ones){
//        now = micros();
//        while (micros()-now < 1){
        for(int i = 0; i < 1000; i++){
            PORTB = B00000001;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
//            delayMicroseconds(kiloh);
            PORTB = B00000000;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
//            delayMicroseconds(kiloh);
        }
    }
}
