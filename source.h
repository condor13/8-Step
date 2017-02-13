int dataPin = 4;
    //data pin for shift register
int latchPin = 6;
    //latch pin for shift register
int clockPin = 5;
    //clock pin for shift register or "shiftout" 
int togglePin = 7;
    //toggle pin for direction read
int randomEnable = 8;
    //source enable pin
volatile byte count;
    //4 digit variable
byte countArray[8];
    //4 digit array with 8 spaces
boolean reset = 0;
    //boolean reset toggle variable
boolean toggleDirection = 0; 
    //boolean direction toggle variable 
volatile int j = 0;
    //variable for counting through count array
int k = 0;
int l = 0;
    //for making random non repeating
volatile int x = 1;
    //variable for counting
volatile boolean bishop = 0;
    //create a variable that can be used for clock
boolean hudson = 0; 
    //create variable used in clock function 
boolean hicks = 0; 

void setup(){
  pinMode(dataPin, OUTPUT);
    //set shift register pin to output
  pinMode(latchPin, OUTPUT);
    //set latch pin to output
  pinMode(clockPin, OUTPUT);
    //set clock pin to output
  pinMode(togglePin, INPUT);
    //set reset pin to input
  pinMode(randomEnable, INPUT);
    //set sourceEnable pin to input
  attachInterrupt(0, sigourney, RISING);
    //when pin 2 changes (rising edge) move to "sigourney" reset loop
  attachInterrupt(1, alienClock, RISING); 
    //when pin 3 changes (rishing edge) move to "alienClock" clock loop
  randomSeed(analogRead(0));
     //read analog pin 0 for start of pseudo random sequence
        
  countArray[0] = 1;   //0000 0001, step 0
  countArray[1] = 2;   //0000 0010, step 1
  countArray[2] = 4;   //0000 0100, step 2
  countArray[3] = 8;   //0000 1000, step 3
  countArray[4] = 16;  //0001 0000, step 4
  countArray[5] = 32;  //0010 0000, step 5
  countArray[6] = 64;  //0100 0000, step 6
  countArray[7] = 128; //1000 0000, step 7
}
void loop(){    
  
  if(bishop != hudson){
    //limites access to this loop, once per external clock cycle until random is enabled
    hicks = digitalRead(randomEnable);
    //check to see if random mode is enabled
    if(hicks == 1){
      //if random mode is enabled then do the following
      l = k; 
      k = j; 
      //creates a history.  k is j last cycle and l is j from the cycle before
      do {
        j = random(8);
      }
      while (j == k || j == l);
      //generate random value for j and make sure it does not match previous 2 value
    }
  else {
    j = j + x;
    // add 1 to j
    }
   hudson = !hudson;
  //prevents function from returning to this loop before another cycle of the external clock
  }
  //toggle hudson
  if(j > 7) j = 0;
    //when j reachers 8, go to startpoint
  if(j < 0) j = 7;
    //when j is less than 0 go to startpoint
  
}

void sigourney(){
  j = 0;
  count = countArray[j];
    // set count eaqual to present state of starting point   
  digitalWrite(latchPin, 0);
    //ground latchPin and hold low for as long as you are transmitting
  shiftOut(dataPin, clockPin, MSBFIRST, count);
    //serial output count
  digitalWrite(latchPin, 1);
    //bring latch pin high to end transmission
}
void alienClock(){
  count = countArray[j];
    // set count eaqual to present state of j    
  digitalWrite(latchPin, 0);
    //ground latchPin and hold low for as long as you are transmitting
  shiftOut(dataPin, clockPin, MSBFIRST, count);
    //serial output count
  digitalWrite(latchPin, 1);
    //bring latch pin high to end transmission
  bishop = !bishop; 
  toggleDirection = digitalRead(togglePin); 
   if(toggleDirection == 1){
  x = -1;
   }
   else{
  x = 1;
   }
}