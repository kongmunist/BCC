void setup() {
    // put your setup code here, to run once:

}

void loop() {
    // put your main code here, to run repeatedly:

}




int* countDuplicates(int* arr){
    int condensed[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int condensedIndex = 0;
    int lenBit = 4;
    
//    int arr[] = {1,1,1,1,1,1,1,1,1,1,0,0,0,0,
//                1,1,1,1,1,0,0,0,0,1,1,1,1,
//                0,0,0,0,0,0,0,0,0,0,0,0,0,};
    
    
    
    int curCounter = 0;
    int lastBit = 1;
    for (int i = 0; i < (sizeof(arr)/sizeof(arr[0])); i++){
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
        
        // If counter is over lenBit, subtract lenBit and add one to no
        if (curCounter >= lenBit){
            curCounter = 0;
            condensed[condensedIndex] = lastBit;
            condensedIndex += 1;
        }
        
        // printf("%d Y", i);
    }
    
    
    // Print no array
    for (int i = 0; i < (sizeof(condensed)/sizeof(condensed[0])); i++){
        printf("%d %d\n", i, condensed[i]);
    }
    
    
}
