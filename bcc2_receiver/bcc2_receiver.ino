int readPin1 = A0;
int pinVal;
int last100 = 0;

float count = 0.0;
long lastTime = 0;

//
//// history
//const int len = 10;
//int yea[len];

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    // History
//    for (int i = 0; i< len; i++){
//        yea[i] = 0.0;
//    }
}

void loop() {
//    lastTime = micros();
    pinVal = analogRead(readPin1);

    addTo(pinVal);
    
//    count += pinVal > 50;
//    count *= .99;
    
    Serial.print("1000,");
    Serial.println(pinVal);
//    Serial.println(700*(howManySpikes() > 5));
}

//void addTo(int val){
//    for (int i = 0; i < len-1; i++){
//        yea[i] = yea[i+1];
//    }
//    yea[len-1] = val;
//}
//
//int howManySpikes(){
//   int no = 0;
//   for (int i = 0; i < len-1; i++){
//        no += yea[i] > 50;
//   }
//   return no;
//}
