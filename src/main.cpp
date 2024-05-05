#include <Arduino.h>

enum digits {zero,one,two,three,four,five,six,seven,eight,nine};
bool b_decimal = false;
int delay_time = 3;
#define DIGIT_1_PIN 9
#define DIGIT_2_PIN 8
#define DIGIT_3_PIN 7
#define DIGIT_4_PIN 6
#define ROW_1 0
#define COLUMN 1

//Forward declare func
int digit_sequence(digits num,bool decimal=false);
void update_7segmentDisplay(digits digit, bool decimal=false);

void setup() {
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(DIGIT_1_PIN,INPUT);
  pinMode(DIGIT_2_PIN,INPUT);
  pinMode(DIGIT_3_PIN,INPUT);
  pinMode(DIGIT_4_PIN,INPUT);
  pinMode(ROW_1,INPUT_PULLUP);
  pinMode(COLUMN,OUTPUT);
  //SPCR=0b01010010;
  SPCR=0b01110010; // LSB MODE, easier base
  SPSR|=0b00000001;
  digitalWrite(10,HIGH);
  // set input pins too low by default
  pinMode(DIGIT_1_PIN, LOW);
  pinMode(DIGIT_2_PIN, LOW);
  pinMode(DIGIT_3_PIN,LOW);
  pinMode(DIGIT_4_PIN, LOW);
}

void loop() {
  // count 
  for(int i = 0; i < 10000; i++)
  {
    int digit1 = i / 1000 % 10;
    int digit2 = i / 100 % 10;
    int digit3 = i / 10 % 10;
    int digit4 = i % 10;

    // hold value for 600 ms
    for(int i = 0; i < 600/(4*delay_time); i++){
      pinMode(DIGIT_1_PIN,HIGH);
      update_7segmentDisplay((digits)digit4,false);
      delay(delay_time);
      pinMode(DIGIT_1_PIN, LOW);

      pinMode(DIGIT_2_PIN,HIGH);
      update_7segmentDisplay((digits)digit3,false);
      delay(delay_time);
      pinMode(DIGIT_2_PIN, LOW);

      pinMode(DIGIT_3_PIN,HIGH);
      update_7segmentDisplay((digits)digit2,false);
      delay(delay_time);
      pinMode(DIGIT_3_PIN, LOW);

      pinMode(DIGIT_4_PIN,HIGH);
      update_7segmentDisplay((digits)digit1,false);
      delay(delay_time);
      pinMode(DIGIT_4_PIN, LOW);
    }
  }
}

// Functions
void update_7segmentDisplay(digits digit, bool decimal=false){
  digitalWrite(10,LOW); // default pin
  SPDR = digit_sequence(digit,decimal); // convert digit to binary code
  while (!(SPSR & (1<<SPIF))){ // wait until SPI interrupt is triggered, when 8 bit register is filled, then update 8 pin light
  }
  digitalWrite(10,HIGH);// turn on
}

int digit_sequence(digits digit,bool decimal=false){
  int binary = 0b00000000;

  switch (digit)
  {
    case digits::zero:
      binary = 0b11101110;
      break;

    case digits::one:
      binary = 0b00100100;
      break;
    
    case digits::two:
      binary = 0b10111010;
      break;

    case digits::three:
      binary = 0b10110110;
      break;
  
    case digits::four:
      binary = 0b01110100;
      break;

    case digits::five:
      binary = 0b11010110;
      break;
  
    case digits::six:
      binary = 0b11011110;
      break;

    case digits::seven:
      binary = 0b10100100;
      break;

    case digits::eight:
      binary = 0b11111110;
      break;

    case digits::nine:
      binary = 0b11110100;
      break;

    default:
      break;
  }
  if (decimal)
  {
    binary |= 0b00000001; // last bit is decimal
  }
  

  return binary;
}