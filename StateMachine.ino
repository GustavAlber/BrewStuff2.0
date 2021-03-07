void state_machine(){
  ausgabe(newstate);
  switch(newstate){
    case heiz_60:     
      brennerZünden();
      if (getAverageTemp() < ERSTETEMP){
        newstate = heiz_60; 
          if (!digitalRead(TASTER)){
            newstate = einmeisch;
            brennerAUS();
            while(!digitalRead(TASTER)){}
          }
      }
      else{
        newstate = einmeisch;
        brennerAUS();
      }
      break;
      
    case (einmeisch):
 
      if(!digitalRead(TASTER)==HIGH){
        newstate = heiz_63;
        
        brennerAN();
        while(!digitalRead(TASTER)){}
      }
      else{
        newstate = einmeisch;
      }
      break;

    case heiz_63:
    
      brennerZünden();
      if (getAverageTemp() < ZWEITETEMP){
        newstate = heiz_63;
        if (!digitalRead(TASTER)){
            newstate = rast_45;
            initRastTimer();
            brennerAUS();
            while(!digitalRead(TASTER)){};
          }
      }
      else{
        newstate = rast_45;
        initRastTimer();
        brennerAUS();
      }
      break;

    case(rast_45):

      if (rastTimerExpired(ERSTERAST)){
        newstate = heiz_66;
        brennerAN();
      }
      else{
        newstate = rast_45;
        if (!digitalRead(TASTER)){
            newstate = heiz_66;
            brennerAN();
            while(!digitalRead(TASTER)){}
        }
      }
      break;

   case heiz_66:
      brennerZünden();
    
      if (getAverageTemp() < DRITTETEMP){
        newstate = heiz_66;
        if (!digitalRead(TASTER)){
            newstate = rast_10;
            initRastTimer();
            brennerAUS();
            while(!digitalRead(TASTER)){}
          }
      }
      else{
        newstate = rast_10;
        initRastTimer();
        brennerAUS(); 
      }
      break;

   case(rast_10):
      
       if (rastTimerExpired(ZWEITERAST)){
        newstate = heiz_72;
        brennerAN();
      }
      else{
        newstate = rast_10;
        if (!digitalRead(TASTER)){
            newstate = heiz_72;
            brennerAN();
            while(!digitalRead(TASTER)){}
        }
      }
      break;

   case heiz_72:
      brennerZünden();
    
      if (getAverageTemp() < VIERTETEMP){
        newstate = heiz_72;
        if (!digitalRead(TASTER)){
            newstate = rast_15;
            initRastTimer();
            brennerAUS();
            while(!digitalRead(TASTER)){}
          }
      }
      else{
        newstate = rast_15;
        brennerAUS();
        initRastTimer();  
      }
      break;
   
   case(rast_15):
      
       if (rastTimerExpired(DRITTERAST)){
        newstate = heiz_76;
        brennerAN();
      }
      else{
        newstate = rast_15;
        if (!digitalRead(TASTER)){
            newstate = heiz_76;
            brennerAN();
            while(!digitalRead(TASTER)){}
        }
      }
      break;

   case heiz_76:
      brennerZünden();
    
      if (getAverageTemp() < FUNFTETEMP){
        newstate = heiz_76;
        if (!digitalRead(TASTER)){
            newstate = ende;
            brennerAUS();
            while(!digitalRead(TASTER)){}
          }
      }
      else{
        brennerAUS();
        newstate = ende;
      }
      break;
      
   case ende:

     if (!digitalRead(TASTER)){
            newstate = heiz_60;
            brennerAN();
            while(!digitalRead(TASTER)){}
          }
      break;
      
    case moff:
    if (!digitalRead(TASTER)){
            newstate = man;
            brennerAN();
            while(!digitalRead(TASTER)){}
          }
    break;

    case man:
    brennerZünden();
    if (!digitalRead(TASTER)){
            newstate = moff;
            brennerAUS();
            while(!digitalRead(TASTER)){}
          }
    break;
    
    case thermostat:

    //just for incresing the temperatur
    if (!digitalRead(TASTER)){
        initThermostatTimer();
        increseTemp();
        while(!digitalRead(TASTER)){
          if(thermostatTimerExpired()){
            if(hundredMilliSecondsExpired()){
              increseTemp();
              ausgabe(newstate);
            }  
          }
         }
       thermostatTimerReset();  
     }
    //end of incresing part

    if (getZieltemperatur() > getAverageTemp()){
      if(brennerstat == OFF){
        brennerAN();
      }
      brennerZünden();
    }
    else{
      if(brennerstat == ON){
        brennerAUS();
      }
    }
     

    break;

    case aus:
    brennerAUS();
  }  
}
