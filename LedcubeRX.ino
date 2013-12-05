#include <SPI.h>
#include <avr/io.h>
int latchPin = 8; // Latch
int resetPin = 9; // Master ReClear (not necessary - just tie High on each Shift Register)
int dataPin = 11; // must be 11 to use SPI on Arduino UNO
int clockPin = 13; // must be 13 to use SPI on Arduino UNO

word matrix[4];
byte level[4];

String inputString = "";
String levelString = "";
String matrixString = "";
boolean stringComplete = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Ready to receive data...");
  level[0]=1;
  level[1]=2;
  level[2]=4;
  level[3]=8;

  inputString.reserve(40);
  levelString.reserve(40);
  matrixString.reserve(40);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH);

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  // set up timer interrupt
  noInterrupts();
  TCCR1B = 10;
  TIMSK1 = 2;
  OCR1A= 30; 
  SPI.begin();
  interrupts();
  matrix[0]=0b0000000000000000;
  matrix[1]=0b0000000000000000;
  matrix[2]=0b0000000000000000;
  matrix[3]=0b0000000000000000;
}

void loop() {

  //parseData();  Uncomment to control directly from LEDCUBETEST GUI and
  //comment out the animations and delay below
  paintUp();
  eraseUp();
  paintDown();
  eraseDown();
  fillUp();
  eraseUp();

  delay(200);


} 

ISR(TIMER1_COMPA_vect){ //timer based multiplexer

  for(int i=0; i<4; i++){
    digitalWrite(latchPin, LOW);
    SPI.transfer(level[i]);
    SPI.transfer(~highByte(matrix[i])); //the ~ is to invert the bits because my cathodes are ACTIVE LOW
    SPI.transfer(~lowByte(matrix[i]));
    digitalWrite(latchPin, HIGH);
  }

}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}
void parseData(){
  //noInterrupts();
  // print the string when a newline arrives:
  if (stringComplete) {
    //inputString.trim();
    Serial.println(inputString);
    int separatorIndex = inputString.indexOf(',');
    levelString=inputString.substring(0,1);
    //Serial.println(levelString);
    matrixString=inputString.substring(separatorIndex+1);
    Serial.println(matrixString);
    int tmp_level  = levelString.toInt();
    //matrix[tmp_level] = matrixString.toHex();
    char charbuf[17];
    matrixString.toCharArray(charbuf,17);
    matrix[tmp_level] = strtol(charbuf,NULL,2);



    Serial.println(matrix[tmp_level],BIN);

    // clear the string:
    inputString = "";
    levelString = "";
    matrixString = "";
    stringComplete = false;
  }

}













