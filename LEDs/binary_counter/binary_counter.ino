//Binary Counter (8 bit)
//Level 1: Easy || Try to represent 0 -> 15 with 4 lights
//Level 2: Medium || Try to represent 0 -> 15 with 4 lights and 1 Counter UP
//Level 3: Hard || Try to represent 0 -> 15 with 4 lights and 2 Counter UP, DOWN

// Components:
/*
- Arduino UNO
- 2 Button
- 4 LEDs
- 4 Resistors 220V -> up
- Breadboard
- Wires
*/

//Fields

const int ledPins[4] = {13,12,11,10};
const int buttonPinUp = 3; // Plugged in ~3
const int buttonPinDown = 5; // Plugged in ~5 (Which supports PMW)
int counter = 0;
bool upCall = false;
bool downCall = false;

//Processing

void decimalToBinary(int n, char binaryBuffer[4]){ 
  for (int i = 0; i<4; i++){
    binaryBuffer[3-i] = (n>>i) & 1 ? '1':'0';
  }
}
/* Level 1
void setup(){
  for (int i = 0; i<4; i++){
    pinMode(ledPins[i],OUTPUT); 
  }
}

void loop(){
  for (int count = 0; count <= 15; count++){
    char binary[4];
    decimalToBinary(count, binary);
    for (int i = 0; i< 4; i++){
      digitalWrite(ledPins[i],binary[i] == '1'?HIGH:LOW);
    }
    delay(1000);
  }
}
*/
// Level 2 + Level 3
void setup(){
  // Configure button as digital input pin
  pinMode(buttonPinUp, INPUT_PULLUP);
  pinMode(buttonPinDown, INPUT_PULLUP);
  for (int i = 0; i<4; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600); // Set up Serial for DEBUGGING
}
void loop(){
  // Operate on button press
  if (!digitalRead(buttonPinUp)){ // when button is pressed -> LOW(0 or False) else -> HIGH (255 or True)
    upCall = true;
    delay(300); 
    // Key debouncing -> As during the process of button pressed, without delay, it will run this loop multiple times until you leave it out of pressed state 
  }
  if (!digitalRead(buttonPinDown)){
    downCall = true;
    delay(300); // Key debouncing
  }
  if (upCall){
    if (counter > 15){
      counter = 0;
    }
    else counter++;
    upCall = false;
  }
  if (downCall){
    if(counter < 0){
      counter = 0;
    }
    else counter--;
    downCall = false;
  }
  Serial.println(counter); // Debug for counter
  // Represent counter in LEDs
  char binary[4];
  decimalToBinary(counter, binary);
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], binary[i] == '1' ? HIGH : LOW);
  }
}