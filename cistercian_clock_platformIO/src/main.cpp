#include <Arduino.h>

// Pin number where the LED is connected
const int F_4 = 0; //D0 pin
const int A_3 = 2; // D2
const int B_3 = 3; //D3
const int C_3 = 4; //D4
const int D_3 = 5; //D5
const int E_3 = 6; //D6

const int A_2 = 7; //D7
const int B_2 = 8; //D8
const int C_2 = 9; //D9
const int D_2 = 10; //D10
const int E_2 = 11; //D11

const int A_1 = 12; //D12
const int B_1 = 13; //D13
const int C_1 = 14; //A0
const int D_1 = 15; //A1
const int E_1 = 16; //A2

const int A_0 = 17; //A3
const int B_0 = 18; //A4
const int C_0 = 19; //A5
const int D_0 = 20; //A6
const int E_0 = 21; //A7
unsigned long previousMillis = 0;
const long interval = 100;

const int segments[4][5] = {
  {A_0, B_0, C_0, D_0, E_0}, // Quadrant 0
  {A_1, B_1, C_1, D_1, E_1}, // Quadrant 1
  {A_2, B_2, C_2, D_2, E_2}, // Quadrant 2
  {A_3, B_3, C_3, D_3, E_3}  // Quadrant 3
};



// Setup function runs once when you press reset or power the board
void setup() {
  // Set all pins as OUTPUT
  for (int i=0; i < sizeof(segments) / sizeof(segments[0]); i++){
    for (int j=0; j < sizeof segments[0] / sizeof segments[0][0]; j++){
      pinMode(segments[i][j], OUTPUT);
    }
  }
  pinMode(F_4, OUTPUT);

  digitalWrite(F_4, HIGH);
}

void clearNum(int quadrant){
  
  // Ensure the quadrant is within valid range
  if (quadrant == 9){
    // rows = sizeof array / sizeof array[0];
    for (int i=0; i < sizeof(segments) / sizeof(segments[0]); i++){
      for (int j=0; j < sizeof segments[0] / sizeof segments[0][0]; j++){
        digitalWrite(segments[i][j], LOW);
      }
    }
    return;
  }else if (quadrant < 0 || quadrant > 3){
    return;
  }

  // Get the pins for the specified quadrant
  int A = segments[quadrant][0];
  int B = segments[quadrant][1];
  int C = segments[quadrant][2];
  int D = segments[quadrant][3];
  int E = segments[quadrant][4];


  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
}


void writeNum(int number, int quadrant){
  // Ensure the quadrant is within valid range
  if (quadrant < 0 || quadrant > 3) return;

  // Get the pins for the specified quadrant
  int A = segments[quadrant][0];
  int B = segments[quadrant][1];
  int C = segments[quadrant][2];
  int D = segments[quadrant][3];
  int E = segments[quadrant][4];

  // Turn on the appropriate pins based on the number
  switch (number){
    case 0:
      break;
    case 1:
      digitalWrite(A, HIGH);
      break;
    case 2:
      digitalWrite(C, HIGH);
      break;
    case 3:
      digitalWrite(D, HIGH);
      break;
    case 4:
      digitalWrite(E, HIGH);
      break;
    case 5:
      digitalWrite(A, HIGH);
      digitalWrite(E, HIGH);
      break;
    case 6:
      digitalWrite(B, HIGH);
      break;
    case 7:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      break;
    case 8:
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    case 9:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    default:
      break;
  }
}

void mainClock(){
  for (int q0 = 0; q0 <=2; q0++){
    clearNum(0);
    writeNum(q0, 0);
    for (int q1=0; q1 <= 9; q1++){
      clearNum(1);
      writeNum(q1, 1);
      if (q0 == 2 && q1 == 4) {
        break; //break out of q1 loop
      }
      for (int q2=0; q2 <= 5; q2++){
        clearNum(2);
        writeNum(q2, 2);
        for (int q3=0; q3 <= 9; q3++){
          unsigned long currentMillis = millis();
          previousMillis = currentMillis;
          clearNum(3);
          writeNum(q3, 3);
          while (currentMillis - previousMillis < interval) {
            currentMillis = millis();
          }
        }
      }
      
    }
    // if (q0 == 2) {
    //   break; //break out of q0 loop
    // }
  }
}





// Loop function runs over and over again forever
void loop() {
  // clearNum(9);
  // for (int i=0; i <= 9; i++){
  //   clearNum(3);
  //   writeNum(i,3);
  //   delay(1000);
  // }
  mainClock();
}