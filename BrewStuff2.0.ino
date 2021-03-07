//logic
#define ON 1
#define OFF 0
#define FEHLER -100.00

//display
#define DISPLAYADRESSE 0x27
#define DISPLAYSPALTEN 16
#define DISPLAYZEILEN 2

//peripherial pins
#define RELAY 8
#define TASTER 9
#define SCHALTERMAN 10
#define SCHALTERTHER 11
#define SCHALTERAUTO 12
#define NTCPIN A0

//temperaturraster
#define ERSTETEMP 60.0
#define ZWEITETEMP 62.5
#define DRITTETEMP 66.0
#define VIERTETEMP 72.0
#define FUNFTETEMP 77.0

//rastzeiten
#define ERSTERAST 2100000
#define ZWEITERAST 600000
#define DRITTERAST 900000

//ringbuffer
#define RINGBUFFERSIZE 30

//timer
#define BRENNERDELAY 2000
#define THERMOSTATDELAY 1000
//hier in sekunden!!!
#define TEMPMESSSUSPEND 10

//thermostat
#define UPPERBOUND 103
#define LOWERBOUND 34

//schalter
//#define logging

static uint8_t brennerstat = OFF;

enum states{
  heiz_60,
  einmeisch,
  heiz_63,
  rast_45,
  heiz_66,
  rast_10,
  heiz_72,
  rast_15,
  heiz_76,
  ende,
  man,
  moff,
  thermostat,
  aus,
  undefined
};

void setup() {
  pinMode(RELAY, OUTPUT);
  pinMode(TASTER, INPUT_PULLUP);
  pinMode(SCHALTERMAN, INPUT_PULLUP);
  pinMode(SCHALTERTHER, INPUT_PULLUP);
  pinMode(SCHALTERAUTO, INPUT_PULLUP);
  pinMode(A0, INPUT);
  
  displayInit();
  initTimer();
  messungInit();
  initRingBuffer();
  stateInit(heiz_60);
  #ifdef logging
  Serial.begin(9600);
  #endif
  
}

void loop() {

  if(oneSeconsExpired()){
    //runs every second
    if(suspensionActive()){
      suspendTempMessureTick();
      if(suspendTempMessureExpired()){
        suspendTempMessureDeactivate();
      }
    }
    else{
      takeMeasurement();
      #ifdef logging
      printRingbuffer();
      #endif
    }
  }
  
  if(tenSeconsExpired()){
    //runs every ten seconds
  }

  if(!digitalRead(SCHALTERTHER)){
    newState(thermostat);
    state_machine();
  }
  else if(!digitalRead(SCHALTERMAN)){
    //manual
    if(brennerstat == ON){
      newState(man);
    }
    else{
      newState(moff);
    }
    state_machine();
  }
  else if(!digitalRead(SCHALTERAUTO)){
    //brewstuff
    if(wasInManual()){
      stateInit(heiz_60);
    }
    state_machine();  
  }
  else{
    newState(aus);
    state_machine();
  }
  
  
}
