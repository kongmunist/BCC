#include "cppQueue.h"

#define SLIDING_WINDOW_SIZE 15
#define thresh 10

float runningMean = 0;
int spikeCounter = 0;
int touchPin = A0;
long lastTime = 0;

cppQueue queue(sizeof(int), SLIDING_WINDOW_SIZE, FIFO);

// Tracking history from the sliding window
bool recording = false;
int howManyZeros = 0;
const int histLen = 400;
int histIndex = 0;
int pastSec[histLen];

void setup() {
  Serial.begin(115200);
  pinMode(touchPin, INPUT);

  clearArray(pastSec);
}

void loop() {
  int touchVal = analogRead(touchPin);

////////////////// Only start recording if we get a spike 
  if (touchVal > thresh*5 && !recording){
    recording = true;
    histIndex = 0;
    clearArray(pastSec);
  } else if (histIndex == histLen){
    recording = false;
    // Run array reducing and classification here.
//    printArray(pastSec);
  }

/////////////// Recording values after spike
  if (recording){ 
    // Collect values and filters/features
    if (queue.isFull()) {
      int oldVal;
      queue.pop(&oldVal);
      runningMean -= oldVal / SLIDING_WINDOW_SIZE;
      spikeCounter -= (oldVal > thresh);
    }
    
    queue.push(&touchVal);
    runningMean += touchVal / SLIDING_WINDOW_SIZE;
    spikeCounter += (touchVal > thresh);
    
    // accumulate into history
    pastSec[histIndex] = spikeCounter > 2;
    histIndex += 1;
    
    plotData(touchVal, runningMean, spikeCounter);  
  }
  
}

void plotData(float val1, float val2, float val3) {
  Serial.print("1000,");
  Serial.print(val1);
  Serial.print(",");
  Serial.print(val2);
//  Serial.print(",");
//  Serial.print((val3 > 2)*700);
  Serial.print(",");
  Serial.print((val3 > 3)*700);
//  Serial.print(",");
//  Serial.print((val3 > 4)*700);
  Serial.println();
}

void clearArray(int arr[]){
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        arr[i] = -1;
    }
}

void printArray(int arr[]){
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        Serial.print(arr[i]);
        Serial.print(",");

        if ( i%200 == 0){
            Serial.println();
        }
    }
}
