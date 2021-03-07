
static unsigned long tenSecondTimerStart = 0;
static unsigned long oneSecondTimerStart = 0;
static unsigned long hundredMilliSecondTimerStart = 0;
static unsigned long rastTimerStart = 0;
static unsigned long brennerTimerStart = 0;
static unsigned long thermostatTimerStart = 0;
int suspendTempMessure = 0;
bool suspendTempMessureActive = false;


void initTimer(void){
  tenSecondTimerStart = millis();
  oneSecondTimerStart = millis();
  hundredMilliSecondTimerStart = millis();
}

bool  hundredMilliSecondsExpired(void){
  long diff = millis() - hundredMilliSecondTimerStart;
  if (diff > 100){
    hundredMilliSecondTimerStart = millis();
    return true;
  }
  return false;
}

bool tenSeconsExpired(void){
  long diff = millis() - tenSecondTimerStart;
  if (diff > 10000){
    tenSecondTimerStart = millis();
    return true;
  }
  return false;
}

bool oneSeconsExpired(void){
  long diff = millis() - tenSecondTimerStart;
  if (diff > 1000){
    tenSecondTimerStart = millis();
    return true;
  }
  return false;
}

void initRastTimer(void){
  rastTimerStart = millis();
}

bool rastTimerExpired(long zeit){
  long diff = millis() - rastTimerStart;
  if(diff > zeit){
    rastTimerStart = 0;
    return true;
  }
  return false;
}

int getRemainingRast(long zeit){
  long diff = millis() - rastTimerStart;
  int remain = zeit - (diff/1000/60);
  return remain;
}

void initBrennerTimer(void){
  if (brennerTimerStart == 0){
    brennerTimerStart = millis();
  } 
}

bool brennerTimerExpired(void){
  long diff = millis() - brennerTimerStart;
  if(diff > BRENNERDELAY){
    return true;
    brennerTimerStart = 0;
  }
  return false;
}

void brennerTimerReset(void){
  brennerTimerStart = 0;
}


void initThermostatTimer(void){
  if (thermostatTimerStart == 0){
    thermostatTimerStart = millis();
  } 
}

bool thermostatTimerExpired(void){
  long diff = millis() - thermostatTimerStart;
  if(diff > THERMOSTATDELAY){
    return true;
    thermostatTimerStart = 0;
  }
  return false;
}

void thermostatTimerReset(void){
  thermostatTimerStart = 0;
}

void suspendTempMessureTick(void){
  if (suspensionActive()){
    suspendTempMessure++;
  }
  
}

bool suspendTempMessureExpired(void){
  return suspendTempMessure > TEMPMESSSUSPEND;
}

bool suspensionActive(void){
  return suspendTempMessureActive;
}

void suspendTempMessureActivate(void){
  if(!suspensionActive()){
  suspendTempMessure = 0;
  suspendTempMessureActive = true;
  }
}

void suspendTempMessureDeactivate(void){
  suspendTempMessureActive = false;
  //suspendTempMessure = 30;
}
