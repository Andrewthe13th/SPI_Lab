#include <Arduino.h>

enum digits {zero,one,two,three,four,five,six,seven,eight,nine};
bool b_decimal = false;

//Forward declare func
int digit_sequence(digits num,bool decimal=false);
void update_7segmentDisplay(digits digit, bool decimal=false);

void setup() {
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);
  //SPCR=0b01010010;
  SPCR=0b01110010; // LSB MODE, easier base
  SPSR|=0b00000001;
  digitalWrite(10,HIGH);
}

void loop() {

  for(int i = 0; i < 10; i++){ // 
    update_7segmentDisplay((digits)i,false);
    delay (1000);
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