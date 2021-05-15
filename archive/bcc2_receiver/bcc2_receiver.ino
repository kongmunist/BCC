int readPin1 = A0;
int pinVal;
int last100 = 0;

float count = 0.0;
long lastTime = 0;

// Tracking history from the sliding window
#define SLIDING_WINDOW_SIZE 10
float WIND_DIVISOR = 1.0/SLIDING_WINDOW_SIZE;
#define thresh 20
int yea[SLIDING_WINDOW_SIZE];

bool recording = false;
int howManyZeros = 0;
const int histLen = 300;
int histIndex = 0;
int pastSec[histLen];

// Metric tracking
float runningMean = 0;
int spikeCounter = 0;


void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

//    pinMode(7,INPUT);

    // History
//    for (int i = 0; i< len; i++){
//        yea[i] = 0.0;
//    }
    lastTime = micros();
}

void loop() {
    pinVal = analogRead(readPin1);

    ////////////////// Only start recording if we get a spike 
  if (pinVal > thresh*5 && !recording){
    recording = true;
  } else if (histIndex == histLen){
    recording = false;
    // Run array reducing and classification here.
//    Serial.println("Raw ADC input:");
//    printArray(pastSec);
//    dilateArray(pastSec);
//    oppositeArray(pastSec);
//    Serial.println("Filtered ADC input:");
//    printArray(pastSec);
//    int* condensed = countDuplicates(pastSec);
    /////    printArray(condensed);

    

    histIndex = 0;
    clearArray(pastSec);
  }

      /////////////// Recording values after spike
  if (recording){ 
    // Collect values and filters/features
    addTo(pinVal);
    // accumulate into history
//    pastSec[histIndex] = spikeCounter > 3;
//    pastSec[histIndex] = (spikeCounter > 1 && runningMean>30);
    
    pastSec[histIndex] = runningMean>30;
    histIndex += 1;
    
    
    Serial.print("1000,");
    Serial.print(pinVal);
//    Serial.print(",");
//    Serial.print((runningMean>30)*700);
//    Serial.print(",");
//    Serial.print(runningMean);
//    Serial.print(",");
//    Serial.print((spikeCounter > 2)*800);
//    Serial.print(",");
//    Serial.print((pastSec[histIndex-1])*900);
    Serial.println();

    
  }
}

void addTo(int val){
    // Remove old val
    runningMean -= yea[0] * WIND_DIVISOR;
    spikeCounter -= (yea[0] > thresh);

    // Shift all values towards front
    for (int i = 0; i < SLIDING_WINDOW_SIZE-1; i++){
        yea[i] = yea[i+1];
    }
    yea[SLIDING_WINDOW_SIZE-1] = val;

    runningMean += val * WIND_DIVISOR;
    spikeCounter += (val > thresh);    
}

void clearArray(int arr[]){
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        arr[i] = -1;
    }
}


void printArray(int arr[]){
    for (int i = 0; i < histLen; i++){
//        Serial.print(i);
//        Serial.print(",");
        Serial.print(arr[i]);
        Serial.print(",");

        if ( i%100 == 99){
            Serial.println();
        }
    }
}

void dilateArray(int arr[]){
    for (int i = 1; i < histLen-2; i++){
        if (arr[i-1]==1 && arr[i]==0 && arr[i+1]==1){
            arr[i] = 1;
        } else if (arr[i-1]==1 && arr[i]==0 && arr[i+1]==0  && arr[i+2]==1){
            arr[i] = 1;
        }
    }
}

void oppositeArray(int arr[]){
    for (int i = 1; i < histLen-2; i++){
        if (arr[i-1]==0 && arr[i]==1 && arr[i+1]==0){
            arr[i] = 0;
        } else if (arr[i-1]==0 && arr[i]==1 && arr[i+1]==1  && arr[i+2]==0){
            arr[i] = 0;
        }
    }
}

int* countDuplicates(int arr[]){
    // Initialize variables for condensing
    int condensedIndex = 0;
    int lenBit = 13;
    int lenCondensed = 40;
    int condensed[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                        };

    
    int curCounter = 0;
    int lastBit = 1;
//    Serial.println(sizeof(arr));
//    Serial.println(sizeof(arr[0]));
    for (int i = 0; i < histLen; i++){
        // If this bit matches the last one, add one to counter
        if (lastBit == arr[i]){ 
            curCounter += 1;
        } else{
            // Else, check if curCounter / lenBit > 0.7. If so, we add one 
            if ((float) curCounter/lenBit > 0.7){
                condensed[condensedIndex] = lastBit;
                condensedIndex += 1;
            }
            // then reset counter and lastBit
            lastBit = arr[i];
            curCounter = 1;
        }
        
        // If counter is over lenBit, subtract lenBit and add one to the accumulator
        if (curCounter >= lenBit){
            curCounter = 0;
            condensed[condensedIndex] = lastBit;
            condensedIndex += 1;
        }
    }
    
    Serial.println("\nCondensed raw:");
    for (int i = 0; i < lenCondensed; i++){
//        printf("%d %d\n", i, condensed[i]);
        Serial.print(condensed[i]);
        Serial.print(",");
    }

    
    // Print no array
    Serial.println("\nCondensed output:");
    for (int i = 2; i < 10; i++){
//        printf("%d %d\n", i, condensed[i]);
        Serial.print(condensed[i]);
//        Serial.print(",");
    }
    

    
    Serial.println();
    return condensed;
}
