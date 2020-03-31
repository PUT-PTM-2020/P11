void setNote(char* note, TIM_HandleTypeDef* htim){
   if(note == "pp"){
       htim->Instance->PSC = 1343;
       htim->Instance->ARR = 62499;
   }
   if(note == "C2"){
       htim->Instance->PSC = 12922;
       htim->Instance->ARR = 1;
   }
   if(note == "CS2"){
       htim->Instance->PSC = 1738;
       htim->Instance->ARR = 6;
   }
   if(note == "D2"){
       htim->Instance->PSC = 10;
       htim->Instance->ARR = 1045;
   }
   if(note == "DS2"){
       htim->Instance->PSC = 10;
       htim->Instance->ARR = 978;
   }
   if(note == "E2"){
       htim->Instance->PSC = 10242;
       htim->Instance->ARR = 1;
   }
   if(note == "F2"){
       htim->Instance->PSC = 1930;
       htim->Instance->ARR = 4;
   }
   if(note == "FS2"){
       htim->Instance->PSC = 54;
       htim->Instance->ARR = 165;
   }
   if(note == "G2"){
       htim->Instance->PSC = 2856;
       htim->Instance->ARR = 2;
   }
   if(note == "GS2"){
       htim->Instance->PSC = 672;
       htim->Instance->ARR = 11;
   }
   if(note == "A2"){
       htim->Instance->PSC = 22;
       htim->Instance->ARR = 331;
   }
   if(note == "AS2"){
       htim->Instance->PSC = 7178;
       htim->Instance->ARR = 1;
   }
   if(note == "B2"){
       htim->Instance->PSC = 6828;
       htim->Instance->ARR = 1;
   }
   if(note == "C3"){
       htim->Instance->PSC = 1602;
       htim->Instance->ARR = 3;
   }
   if(note == "CS3"){
       htim->Instance->PSC = 6042;
       htim->Instance->ARR = 1;
   }
   if(note == "D3"){
       htim->Instance->PSC = 2856;
       htim->Instance->ARR = 1;
   }
   if(note == "DS3"){
       htim->Instance->PSC = 672;
       htim->Instance->ARR = 7;
   }
   if(note == "E3"){
       htim->Instance->PSC = 2544;
       htim->Instance->ARR = 1;
   }
   if(note == "F3"){
       htim->Instance->PSC = 0;
       htim->Instance->ARR = 4799;
   }
   if(note == "FS3"){
       htim->Instance->PSC = 1134;
       htim->Instance->ARR = 3;
   }
   if(note == "G3"){
       htim->Instance->PSC = 4284;
       htim->Instance->ARR = 1;
   }
   if(note == "GS3"){
       htim->Instance->PSC = 672;
       htim->Instance->ARR = 5;
   }
   if(note == "A3"){
       htim->Instance->PSC = 22;
       htim->Instance->ARR = 165;
   }
   if(note == "AS3"){
       htim->Instance->PSC = 720;
       htim->Instance->ARR = 4;
   }
   if(note == "B3"){
       htim->Instance->PSC = 424;
       htim->Instance->ARR = 7;
   }
   if(note == "C4"){
       htim->Instance->PSC = 1602;
       htim->Instance->ARR = 1;
   }
   if(note == "CS4"){
       htim->Instance->PSC = 378;
       htim->Instance->ARR = 7;
   }
   if(note == "D4"){
       htim->Instance->PSC = 2856;
       htim->Instance->ARR = 1;
   }
   if(note == "DS4"){
       htim->Instance->PSC = 44;
       htim->Instance->ARR = 59;
   }
   if(note == "E4"){
       htim->Instance->PSC = 2544;
       htim->Instance->ARR = 1;
   }
   if(note == "F4"){
       htim->Instance->PSC = 1202;
       htim->Instance->ARR = 1;
   }
   if(note == "FS4"){
       htim->Instance->PSC = 1134;
       htim->Instance->ARR = 1;
   }
   if(note == "G4"){
       htim->Instance->PSC = 62;
       htim->Instance->ARR = 33;
   }
   if(note == "GS4"){
       htim->Instance->PSC = 22;
       htim->Instance->ARR = 87;
   }
   if(note == "A4"){
       htim->Instance->PSC = 22;
       htim->Instance->ARR = 82;
   }
   if(note == "AS4"){
       htim->Instance->PSC = 52;
       htim->Instance->ARR = 33;
   }
   if(note == "B4"){
       htim->Instance->PSC = 424;
       htim->Instance->ARR = 3;
   }
   if(note == "C5"){
       htim->Instance->PSC = 802;
       htim->Instance->ARR = 1;
   }
   if(note == "CS5"){
       htim->Instance->PSC = 378;
       htim->Instance->ARR = 3;
   }
   if(note == "D5"){
       htim->Instance->PSC = 476;
       htim->Instance->ARR = 2;
   }
   if(note == "DS5"){
       htim->Instance->PSC = 44;
       htim->Instance->ARR = 29;
   }
   if(note == "E5"){
       htim->Instance->PSC = 12;
       htim->Instance->ARR = 97;
   }
   if(note == "F5"){
       htim->Instance->PSC = 1202;
       htim->Instance->ARR = 1;
   }
   if(note == "FS5"){
       htim->Instance->PSC = 1134;
       htim->Instance->ARR = 1;
   }
   if(note == "G5"){
       htim->Instance->PSC = 62;
       htim->Instance->ARR = 16;
   }
   if(note == "GS5"){
       htim->Instance->PSC = 100;
       htim->Instance->ARR = 9;
   }
   if(note == "A5"){
       htim->Instance->PSC = 476;
       htim->Instance->ARR = 1;
   }
   if(note == "AS5"){
       htim->Instance->PSC = 52;
       htim->Instance->ARR = 16;
   }
   if(note == "B5"){
       htim->Instance->PSC = 424;
       htim->Instance->ARR = 1;
   }
   if(note == "C6"){
       htim->Instance->PSC = 400;
       htim->Instance->ARR = 1;
   }
   if(note == "CS6"){
       htim->Instance->PSC = 756;
       htim->Instance->ARR = 1;
   }
   if(note == "D6"){
       htim->Instance->PSC = 16;
       htim->Instance->ARR = 41;
   }
   if(note == "DS6"){
       htim->Instance->PSC = 336;
       htim->Instance->ARR = 1;
   }
   if(note == "E6"){
       htim->Instance->PSC = 12;
       htim->Instance->ARR = 48;
   }
   if(note == "F6"){
       htim->Instance->PSC = 600;
       htim->Instance->ARR = 1;
   }
   if(note == "FS6"){
       htim->Instance->PSC = 188;
       htim->Instance->ARR = 2;
   }
   if(note == "G6"){
       htim->Instance->PSC = 106;
       htim->Instance->ARR = 4;
   }
   if(note == "GS6"){
       htim->Instance->PSC = 504;
       htim->Instance->ARR = 1;
   }
   if(note == "A6"){
       htim->Instance->PSC = 476;
       htim->Instance->ARR = 1;
   }
   if(note == "AS6"){
       htim->Instance->PSC = 224;
       htim->Instance->ARR = 1;
   }
   if(note == "B6"){
       htim->Instance->PSC = 424;
       htim->Instance->ARR = 1;
   }
   if(note == "C7"){
       htim->Instance->PSC = 400;
       htim->Instance->ARR = 1;
   }
}
