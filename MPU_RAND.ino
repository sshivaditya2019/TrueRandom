
#include "Wire.h"
#include <MPU6050_light.h>


MPU6050 mpu(Wire);
unsigned long timer = 0;
int passFlag = 0;
int game_state = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
}
unsigned char rand_num()
{
  unsigned char sum = 0;
  const uint8_t minEntropyScale = 8; //min-entropy for measuring devices
  for(int i=1;i<=3;i++){
      mpu.update();
      unsigned char X = mpu.getAccAngleX()/10;
      unsigned char Y = mpu.getAccAngleY()/10; 
      unsigned char Z = mpu.getGyroX()*10;
      uint8_t real4xBits = (X / minEntropyScale) & 0xF; //Converting the X value obtained to 4 bitnumbers
      uint8_t real4yBits = (Y / minEntropyScale) & 0xF; //Similaryly converting Y
      uint8_t real4zBits = (Z / minEntropyScale) & 0xF; // And Z
      uint8_t randn = ((real4xBits & 0x3) << 6) ^ (real4zBits << 4) ^ (real4yBits << 2) ^ real4xBits ^ (real4zBits >> 2); //Using the Expression for generating a random number
      if (X != 0 || Y!=0 || Z!=0 ){  //Omitting Zero numbers from calculation
        Serial.print("\n");
        Serial.print(randn%6+1); //Taking Mod 6 to get number less than 6 and adding 1 to prevent getting zero
        Serial.print("\n");
        return (randn%6+1); //Function reutrns the number generated
      }
    }
    return; //Edge case
       
}
int print_pat(int num)
{
  Serial.print("\n_____\n");
  if (num == 1)
  {
    Serial.print("| . |\n");
    Serial.print("-----\n");
  }
  else if(num == 2){
    Serial.print("|. .|\n");
    Serial.print("-----\n");
  }
  else if(num == 3){
    Serial.print("|.  |\n");
    Serial.print("|. .|\n");
    Serial.print("-----\n");
  }
  else if(num == 4){
    Serial.print("|. .|\n");
    Serial.print("|. .|\n");
    Serial.print("-----\n");
  }
  else if(num == 5){
    Serial.print("| . |\n");
    Serial.print("|. .|\n");
    Serial.print("|. .|\n");
    Serial.print("-----\n");
  }
  else {
    Serial.print("|. .|\n");
    Serial.print("|. .|\n");
    Serial.print("|. .|\n");
    Serial.print("-----\n");
  }
  return num;
  
}
int score_gen(){
  int a = print_pat(rand_num());
  int b = print_pat(rand_num());
  int c = print_pat(rand_num());
  int score = a*100 + b*10 + c;
  return score;
}

void loop() {
 if (game_state == 0)
 {
  int p1 = 0;
  int p2 = 0;
  int p3 = 0;
  int p1_t = 0 ;
  int p2_t = 0;
  int p3_t = 0;
  int k = 1;
  while(game_state == 0)
  {
    Serial.print(" -------------A-------------");
    Serial.print("\n");
    p1 = score_gen();
    Serial.print(" -------------B-------------");
    Serial.print("\n");
    p2 = score_gen();
    Serial.print(" -------------C-------------");
    Serial.print("\n");
    p3 = score_gen();
    p1_t = p1_t + p1;
    p2_t = p2_t + p2;
    p3_t = p3_t + p3;
    Serial.print("Score at the end of Round #");
    Serial.print(k);
    Serial.print("\n");
    Serial.print(" A : ");
    Serial.print(p1_t);
    Serial.print("\n");
    Serial.print(" B : ");
    Serial.print(p2_t);
    Serial.print("\n");
    Serial.print(" C : ");
    Serial.print(p3_t);
    Serial.print("\n");
    if (p1_t >= 3156 || p2_t >= 3156 || p3_t >= 3156){
      game_state++;
      if (p1_t >= p2_t && p1_t >= p3_t)
      {
      Serial.print("\nPlayer A Wins !!!!\n");
      }
      else if(p2_t > p3_t && p2_t > p1_t)
      {
      Serial.print("\nPlayer B Wins !!!!\n");
      }
      else {
      Serial.print("\nPlayer C Wins !!!!\n");
      }
      Serial.end();
    }
    k++;
  }
 }
}
