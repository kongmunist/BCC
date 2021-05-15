int outpin = 8;
float kiloh;
long period;

bool ones = false;
long lastTime = 0;
long now;

// Timer output
const byte CLOCKOUT = 9; // Only for Arduino Uno
#define NOP __asm__ __volatile__ ("nop\n\t")

// Output strings
//String bitstring = "0110100001100101011011000110110001101111"; // Hello
//String bitstring = "01001000";// 0110100100100001"; // Hi!
String bitstring = "11010011";// 0110100100100001"; // I dunno

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    
    pinMode(outpin,OUTPUT);
    lastTime = micros();

    period = 20000; // 20ms

        // Timer setup
    // set up 8 MHz timer on CLOCKOUT (OC1A)
//    pinMode (CLOCKOUT, OUTPUT); 
//    // set up Timer 1
//    TCCR1A = bit (COM1A0);  // toggle OC1A on Compare Match
//    TCCR1B = bit (WGM12) | bit (CS10);   // CTC, no prescaling
//    OCR1A =  7;       // output every cycle
}

void loop() {
    Serial.println();
    lastTime = millis();
    // Starting header of 1010
    for (int i = 0; i < 2; i++) {
        sendBit((1+i) % 2);
    }


    
    // Other bits
    for (int i = 0; i < bitstring.length(); i++) {
      if (bitstring[i] == '1'){
        sendBit(true);
//        PORTB = B00000001;
//        delayMicroseconds(period);
//        Serial.print("1 ");
      } else {
        sendBit(false);
//        PORTB = B00000000;
//        delayMicroseconds(period);
//        Serial.print("0 ");
      }
      
//      Serial.println(millis()-lastTime);
    }
    
    PORTB = B00000000;
    delay(1000);
}


void sendBit(bool singleBit){
    long startTime = micros();
    if (singleBit){
        while (micros() - startTime < period){
            PORTB = B00000001;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
            PORTB = B00000000;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
            PORTB = B00000001;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
            PORTB = B00000000;
            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
//            PORTB = B00000001;
//            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
//            PORTB = B00000000;
//            NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
        }
    } else {
        while (micros() - startTime < period){
            PORTB = B00000000;
        }
    }
}
