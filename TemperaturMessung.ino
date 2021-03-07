int SensorPin = A0;
float SensorValue = 0.0;
float B = 3892.48;
float R1 = 10000;
float Tr = 298.15;
float Rr = 10000;

float Rinf=0.0;

float offset = 0.8;
float offsetON = 0.0;

float TempK=0.0;
float TempC=0.0;

void messungInit(void){
    Rinf=Rr*exp(-B/Tr);
}

double offsetCalc(void){
  float ofs = offset;
  if (brennerstat) ofs += offsetON;
  return ofs;
}

//returns temperatur in °C
float messungTermperatur(void){
  
  
  float analogBuffer[10];
  float averageAnalog = 0;
 
  for (int i = 0; i<10; i++){
    analogBuffer[i] = analogRead(NTCPIN);
  }
  for (int i = 0; i<10; i++){
    averageAnalog+=analogBuffer[i];
  }
  
  float SensorValue = averageAnalog/10;

  SensorValue = (1023 / SensorValue)  - 1;
  SensorValue = R1 / SensorValue;

  TempK=(B/log(SensorValue/Rinf)); // calc for temperature
  TempC=TempK-273.15+offsetCalc();

  return TempC;
}
