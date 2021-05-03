int outpin = 8;
float kiloh;
float freq = 10;
long period;

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
    lastTime = micros();
    kiloh = 1000000/freq;
    kiloh = 1.0;

    period = 20000;

    // Timer setup
    // set up 8 MHz timer on CLOCKOUT (OC1A)
//    pinMode (CLOCKOUT, OUTPUT); 
//    // set up Timer 1
//    TCCR1A = bit (COM1A0);  // toggle OC1A on Compare Match
//    TCCR1B = bit (WGM12) | bit (CS10);   // CTC, no prescaling
//    OCR1A =  7;
}


void loop() {
   
    if (ones){
        while (micros()-lastTime < period){
            PORTB = B00000001;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
            PORTB = B00000000;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
            PORTB = B00000001;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
            PORTB = B00000000;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
            PORTB = B00000001;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
            PORTB = B00000000;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
        }
        
    } else {
        while (micros()-lastTime < period){
            PORTB = B00000000;
        }
    }
    lastTime = micros();
    ones = !ones;
}






//void loop() {
//    if (ones){
//        while (micros()-lastTime < period){
//            PORTB = B00000001;
//            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
//            PORTB = B00000000;
//            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
//            PORTB = B00000001;
//            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
//            PORTB = B00000000;
//            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
//            PORTB = B00000001;
//            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
//            PORTB = B00000000;
//            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
//        }
//    } else {
//        while (micros()-lastTime < period){NOP;}
//    }
//    lastTime = micros();
//    ones = !ones;
//}
