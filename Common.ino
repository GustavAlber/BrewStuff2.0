states oldstate = undefined;
states newstate = undefined;

void stateInit(states state){
  if(state == heiz_60 && brennerstat == OFF){
    brennerAN();
  }
  oldstate = state;
  newstate = state;
}

void newState(states state){
  if(oldstate != thermostat){
    setZieltemperatur(0.0);
  }
  newstate = state;
}

bool stateChanged(states state){
  if (oldstate == state){
    return false;
  }
  oldstate = state;
  return true;
}

void brennerAN(void){
  initBrennerTimer();
  suspendTempMessureActivate();
  brennerstat = ON;
}

void brennerZünden(void){
  if(brennerTimerExpired()){
    digitalWrite(RELAY, ON);
    #ifdef logging
    Serial.println("Brenner AN");
    #endif
   } 
}

void brennerAUS(void){
  suspendTempMessureDeactivate();
  brennerTimerReset();
  digitalWrite(RELAY, OFF);
  Serial.println("Brenner AUS");
  brennerstat = OFF;
}

bool wasInManual(void){
  return newstate > ende;
}
