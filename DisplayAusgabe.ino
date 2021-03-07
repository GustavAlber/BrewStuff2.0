#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(DISPLAYADRESSE, DISPLAYSPALTEN, DISPLAYZEILEN);

void displayInit(void){
  lcd.init();
  lcd.backlight();
}

void temperaturMessungAktiv(void){
  lcd.setCursor(15, 0);
  if(suspensionActive()){
    lcd.print("!");
  }
  else{
    lcd.print("*");
  }
}

void heizen(int goalTemp){
  lcd.setCursor(0, 0);
  lcd.print("Heizen auf ");
  lcd.print(goalTemp);
  lcd.write(0xdf);
  lcd.setCursor(15, 0);
  temperaturMessungAktiv();
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(getAverageTemp()); 
}

void rasten(int rast){
  lcd.setCursor(0, 0);
  lcd.print("Rasten ");
  lcd.print(rast);
  lcd.print("min");
  temperaturMessungAktiv();
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(getAverageTemp());
  if(getRemainingRast(rast) > 9){
    lcd.print("    -");
  }
  else{
    lcd.print("    - ");
  }
  lcd.print(getRemainingRast(rast));
  lcd.print("m");
}

void nurText(const char message[]){
  lcd.setCursor(0, 0);
  lcd.print(message);
  temperaturMessungAktiv();
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(getAverageTemp()); 
}

void ausgabeStateChanged(void){
  lcd.clear();
}


void ausgabe(int state){
  if(stateChanged(newstate)){
    ausgabeStateChanged();
  }
    switch(state){
      case heiz_60:
      heizen(ERSTETEMP);
      break;
    case (einmeisch):
      nurText("Einmeischen");
      break;
    case heiz_63:
      heizen(ZWEITETEMP);
      break;
    case(rast_45):
      rasten(ERSTERAST/1000/60);
      break;
   case heiz_66:
      heizen(DRITTETEMP);
      break;
   case(rast_10):
      rasten(ZWEITERAST/1000/60);
      break;
   case heiz_72:
      heizen(VIERTETEMP);
      break;
   case(rast_15):
      rasten(DRITTERAST/1000/60);
      break;
   case heiz_76:
      heizen(FUNFTETEMP);
      break;
   case ende:
      nurText("ENDE");
      break;
   case man:
      nurText("Manuell AN");
      break;
   case moff:
      nurText("Manuell AUS");
      break;
   case thermostat:
      lcd.setCursor(0, 0);
      lcd.print("Thermostat");
      lcd.setCursor(15, 0);
      temperaturMessungAktiv();
      lcd.setCursor(0, 1);
      lcd.print("T: ");
      lcd.print(getAverageTemp());
      lcd.print(" > ");
      lcd.print(getZieltemperatur());
      break;
   case aus:
      nurText("AUS");
      break;
    }
}
