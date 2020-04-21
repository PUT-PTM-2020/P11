#include <string.h>

void setNote(char* note, TIM_HandleTypeDef* htim){
   HAL_TIM_Base_Stop_IT(htim);
   __HAL_TIM_SET_COUNTER(htim, 0);
   HAL_TIM_Base_Start_IT(htim);
   if(strcmp(note, "pp ") == 0){
          htim->Instance->PSC = 13;
          htim->Instance->ARR = 59999;
      }
      if(strcmp(note, "C2 ") == 0){
          htim->Instance->PSC = 6460;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "CS2") == 0){
          htim->Instance->PSC = 1738;
          htim->Instance->ARR = 6;
      }
      if(strcmp(note, "D2 ") == 0){
          htim->Instance->PSC = 10;
          htim->Instance->ARR = 1045;
      }
      if(strcmp(note, "DS2") == 0){
          htim->Instance->PSC = 10;
          htim->Instance->ARR = 978;
      }
      if(strcmp(note, "E2 ") == 0){
          htim->Instance->PSC = 568;
          htim->Instance->ARR = 17;
      }
      if(strcmp(note, "F2 ") == 0){
          htim->Instance->PSC = 1930;
          htim->Instance->ARR = 4;
      }
      if(strcmp(note, "FS2") == 0){
          htim->Instance->PSC = 54;
          htim->Instance->ARR = 165;
      }
      if(strcmp(note, "G2 ") == 0){
          htim->Instance->PSC = 2856;
          htim->Instance->ARR = 2;
      }
      if(strcmp(note, "GS2") == 0){
          htim->Instance->PSC = 672;
          htim->Instance->ARR = 11;
      }
      if(strcmp(note, "A2 ") == 0){
          htim->Instance->PSC = 22;
          htim->Instance->ARR = 331;
      }
      if(strcmp(note, "AS2") == 0){
          htim->Instance->PSC = 2392;
          htim->Instance->ARR = 2;
      }
      if(strcmp(note, "B2 ") == 0){
          htim->Instance->PSC = 568;
          htim->Instance->ARR = 11;
      }
      if(strcmp(note, "C3 ") == 0){
          htim->Instance->PSC = 1602;
          htim->Instance->ARR = 3;
      }
      if(strcmp(note, "CS3") == 0){
          htim->Instance->PSC = 3020;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "D3 ") == 0){
          htim->Instance->PSC = 2856;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "DS3") == 0){
          htim->Instance->PSC = 672;
          htim->Instance->ARR = 7;
      }
      if(strcmp(note, "E3 ") == 0){
          htim->Instance->PSC = 2544;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "F3 ") == 0){
          htim->Instance->PSC = 0;
          htim->Instance->ARR = 4799;
      }
      if(strcmp(note, "FS3") == 0){
          htim->Instance->PSC = 1134;
          htim->Instance->ARR = 3;
      }
      if(strcmp(note, "G3 ") == 0){
          htim->Instance->PSC = 856;
          htim->Instance->ARR = 4;
      }
      if(strcmp(note, "GS3") == 0){
          htim->Instance->PSC = 672;
          htim->Instance->ARR = 5;
      }
      if(strcmp(note, "A3 ") == 0){
          htim->Instance->PSC = 22;
          htim->Instance->ARR = 165;
      }
      if(strcmp(note, "AS3") == 0){
          htim->Instance->PSC = 720;
          htim->Instance->ARR = 4;
      }
      if(strcmp(note, "B3 ") == 0){
          htim->Instance->PSC = 424;
          htim->Instance->ARR = 7;
      }
      if(strcmp(note, "C4 ") == 0){
          htim->Instance->PSC = 1602;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "CS4") == 0){
          htim->Instance->PSC = 378;
          htim->Instance->ARR = 7;
      }
      if(strcmp(note, "D4 ") == 0){
          htim->Instance->PSC = 118;
          htim->Instance->ARR = 23;
      }
      if(strcmp(note, "DS4") == 0){
          htim->Instance->PSC = 44;
          htim->Instance->ARR = 59;
      }
      if(strcmp(note, "E4 ") == 0){
          htim->Instance->PSC = 508;
          htim->Instance->ARR = 4;
      }
      if(strcmp(note, "F4 ") == 0){
          htim->Instance->PSC = 1202;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "FS4") == 0){
          htim->Instance->PSC = 1134;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "G4 ") == 0){
          htim->Instance->PSC = 62;
          htim->Instance->ARR = 33;
      }
      if(strcmp(note, "GS4") == 0){
          htim->Instance->PSC = 22;
          htim->Instance->ARR = 87;
      }
      if(strcmp(note, "A4 ") == 0){
          htim->Instance->PSC = 22;
          htim->Instance->ARR = 82;
      }
      if(strcmp(note, "AS4") == 0){
          htim->Instance->PSC = 52;
          htim->Instance->ARR = 33;
      }
      if(strcmp(note, "B4 ") == 0){
          htim->Instance->PSC = 424;
          htim->Instance->ARR = 3;
      }
      if(strcmp(note, "C5 ") == 0){
          htim->Instance->PSC = 802;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "CS5") == 0){
          htim->Instance->PSC = 378;
          htim->Instance->ARR = 3;
      }
      if(strcmp(note, "D5 ") == 0){
          htim->Instance->PSC = 476;
          htim->Instance->ARR = 2;
      }
      if(strcmp(note, "DS5") == 0){
          htim->Instance->PSC = 44;
          htim->Instance->ARR = 29;
      }
      if(strcmp(note, "E5 ") == 0){
          htim->Instance->PSC = 12;
          htim->Instance->ARR = 97;
      }
      if(strcmp(note, "F5 ") == 0){
          htim->Instance->PSC = 400;
          htim->Instance->ARR = 2;
      }
      if(strcmp(note, "FS5") == 0){
          htim->Instance->PSC = 226;
          htim->Instance->ARR = 4;
      }
      if(strcmp(note, "G5 ") == 0){
          htim->Instance->PSC = 62;
          htim->Instance->ARR = 16;
      }
      if(strcmp(note, "GS5") == 0){
          htim->Instance->PSC = 100;
          htim->Instance->ARR = 9;
      }
      if(strcmp(note, "A5 ") == 0){
          htim->Instance->PSC = 476;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "AS5") == 0){
          htim->Instance->PSC = 52;
          htim->Instance->ARR = 16;
      }
      if(strcmp(note, "B5 ") == 0){
          htim->Instance->PSC = 424;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "C6 ") == 0){
          htim->Instance->PSC = 400;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "CS6") == 0){
          htim->Instance->PSC = 26;
          htim->Instance->ARR = 27;
      }
      if(strcmp(note, "D6 ") == 0){
          htim->Instance->PSC = 16;
          htim->Instance->ARR = 41;
      }
      if(strcmp(note, "DS6") == 0){
          htim->Instance->PSC = 336;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "E6 ") == 0){
          htim->Instance->PSC = 12;
          htim->Instance->ARR = 48;
      }
      if(strcmp(note, "F6 ") == 0){
          htim->Instance->PSC = 12;
          htim->Instance->ARR = 45;
      }
      if(strcmp(note, "FS6") == 0){
          htim->Instance->PSC = 188;
          htim->Instance->ARR = 2;
      }
      if(strcmp(note, "G6 ") == 0){
          htim->Instance->PSC = 106;
          htim->Instance->ARR = 4;
      }
      if(strcmp(note, "GS6") == 0){
          htim->Instance->PSC = 100;
          htim->Instance->ARR = 4;
      }
      if(strcmp(note, "A6 ") == 0){
          htim->Instance->PSC = 52;
          htim->Instance->ARR = 8;
      }
      if(strcmp(note, "AS6") == 0){
          htim->Instance->PSC = 224;
          htim->Instance->ARR = 1;
      }
      if(strcmp(note, "B6 ") == 0){
          htim->Instance->PSC = 16;
          htim->Instance->ARR = 24;
      }
      if(strcmp(note, "C7 ") == 0){
          htim->Instance->PSC = 18;
          htim->Instance->ARR = 20;
      }
}
