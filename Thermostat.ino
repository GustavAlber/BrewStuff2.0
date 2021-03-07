float zielTemperatur = 0.0;

bool exceedsUpperBound(float temp){
  return temp > UPPERBOUND;
}

void setZieltemperatur(float temp){
  zielTemperatur = temp;
}

bool exceedsLowerBound(float temp){
  return temp < LOWERBOUND;
}

void increseTemp(void){
  if(exceedsUpperBound(zielTemperatur + 1)){
    zielTemperatur = 0.0;
  }
  else if(exceedsLowerBound(zielTemperatur + 1)){
    zielTemperatur = 34.0;
  }
  else {
    zielTemperatur +=1;
  }
}

float getZieltemperatur(void){
  return zielTemperatur;
}
