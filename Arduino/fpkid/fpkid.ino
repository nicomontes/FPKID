//Variables Seats Heaters
const int btnHeaterFL  = 0;
const int btnHeaterFR  = 1;
const int btnHeaterRL  = 2;
const int btnHeaterRR  = 3;
int heaterFLStatus = 0;
int heaterFRStatus = 0;
int heaterRLStatus = 0;
int heaterRRStatus = 0;
const int heaterFLLow = 4;
const int heaterFRLow = 5;
const int heaterRLLow = 6;
const int heaterRRLow = 7;
const int heaterFLHigh = 8;
const int heaterFRHigh = 9;
const int heaterRLHigh = 10;
const int heaterRRHigh = 11;

//Variables Trim
bool trimDown = false;
bool trimUp = false;
bool trustTrimDown = true;
bool trustTrimUp = true;
const int btnTrimDown = 16;
const int btnTrimUp = 17;
const int engTrimDown = 18;
const int engTrimUp = 19;
int tDownTimer = 0; //Trim Down Timer position
int tUpTimer = 0; //Trim Up Timer position
int trimDisableTimer = 300; //Trime Disable Timer
int trimUntrustTimer = 10000; //Trime Untrust Timer

//Variables Lights
bool lightFixed = false;
bool lightFlash = false;
int lTimer = 0; //Light Timer position
const int lightTimer = 100; //Timer 0.1 sec (set what we want)
bool lightRActive = false;
bool lightLActive = false;
const int btnLightFixed = 12;
const int btnLightFlash = 13;
const int lightR = 14;
const int lightL = 15;

void setup()
{ 
  Serial.begin(9600);

  //Set pins for seat heater
  //pinMode(btnHeaterFL,INPUT_PULLUP);
  //pinMode(btnHeaterFR,INPUT_PULLUP);
  pinMode(btnHeaterRL,INPUT_PULLUP);
  pinMode(btnHeaterRR,INPUT_PULLUP);
  pinMode(heaterFLLow,OUTPUT);
  pinMode(heaterFRLow,OUTPUT);
  pinMode(heaterRLLow,OUTPUT);
  pinMode(heaterRRLow,OUTPUT);
  pinMode(heaterFLHigh,OUTPUT);
  pinMode(heaterFRHigh,OUTPUT);
  pinMode(heaterRLHigh,OUTPUT);
  pinMode(heaterRRHigh,OUTPUT);

  //Set pins for trim
  pinMode(btnTrimDown,INPUT_PULLUP);
  pinMode(btnTrimUp,INPUT_PULLUP);
  pinMode(engTrimDown,OUTPUT);
  pinMode(engTrimUp,OUTPUT);

  //Set pins for lights
  pinMode(btnLightFixed,INPUT_PULLUP);
  pinMode(btnLightFlash,INPUT_PULLUP);
  pinMode(lightR,OUTPUT);
  pinMode(lightL,OUTPUT);
}

void loop()
{

  Serial.println(analogRead(A6));
  Serial.println(analogRead(A7));

  //Read Trim button
  if (digitalRead(btnTrimDown) == LOW)
  {
    trim(0,true);
  }
  else
  {
    trim(0,false);
  }
  if (digitalRead(btnTrimUp) == LOW)
  {
    trim(1,true);
  }
  else
  {
    trim(1,false);
  }
  if (digitalRead(btnTrimDown) == HIGH and digitalRead(btnTrimUp) == HIGH)
  {
    trimDown = false;
    trimUp = false;
  }

  //Read lights button
  if (digitalRead(btnLightFixed) == LOW)
  {
    light(0);
  }
  else if (digitalRead(btnLightFlash) == HIGH)
  {
    digitalWrite(lightL, LOW);
    digitalWrite(lightR, LOW);
    lightFixed = false;
  }
  if (digitalRead(btnLightFixed) == HIGH and digitalRead(btnLightFlash) == HIGH)
  {
    digitalWrite(lightL, LOW);
    digitalWrite(lightR, LOW);
    lightFixed = false;
    lightFlash = false;
    lightRActive = false;
    lightLActive = false;
  }
  if (digitalRead(btnLightFixed) == LOW and digitalRead(btnLightFlash) == LOW)
  {
    light(0);
  }
  else if (digitalRead(btnLightFlash) == LOW)
  {
    light(1);
  }

  //Read heater button 
  if (digitalRead(btnHeaterFL) == LOW)
  {
    int i = 0;
    while (digitalRead(btnHeaterFL) == LOW and i < 50){delay(10);i++;} //Wait button UP or wait 0.5 sec to do action
    seatsHeaters(1);
  }
  if (digitalRead(btnHeaterFR) == LOW)
  {
    int i = 0;
    while (digitalRead(btnHeaterFR) == LOW and i < 50){delay(10);i++;}
    seatsHeaters(2);
  }
  if (digitalRead(btnHeaterRL) == LOW)
  {
    int i = 0;
    while (digitalRead(btnHeaterRL) == LOW and i < 50){delay(10);i++;}
    seatsHeaters(3);
  }
  if (digitalRead(btnHeaterRR) == LOW)
  {
    int i = 0;
    while (digitalRead(btnHeaterRR) == LOW and i < 50){delay(10);i++;}
    seatsHeaters(4);
  }

  delay(10);
}

// SeatHeater Function 
void seatsHeaters(int seat)
{
  switch (seat) {
  case 1: // Seat 1 Front Left
    heaterFLStatus = (heaterFLStatus+1)%3;
    if (heaterFLStatus == 0)
    {
      digitalWrite(heaterFLLow, LOW); // Heater 1
      digitalWrite(heaterFLHigh, LOW); // Heater 2
    } else if (heaterFLStatus == 1)
    {
      digitalWrite(heaterFLLow, HIGH);
      digitalWrite(heaterFLHigh, LOW);
    } else if (heaterFLStatus == 2)
    {
      digitalWrite(heaterFLLow, HIGH);
      digitalWrite(heaterFLHigh, HIGH);
    }
    break;
  case 2:
    heaterFRStatus = (heaterFRStatus+1)%3;
    if (heaterFRStatus == 0)
    {
      digitalWrite(heaterFRLow, LOW);
      digitalWrite(heaterFRHigh, LOW);
    } else if (heaterFRStatus == 1)
    {
      digitalWrite(heaterFRLow, HIGH);
      digitalWrite(heaterFRHigh, LOW);
    } else if (heaterFRStatus == 2)
    {
      digitalWrite(heaterFRLow, HIGH);
      digitalWrite(heaterFRHigh, HIGH);
    }
    break;
  case 3:
    heaterRLStatus = (heaterRLStatus+1)%3;
    if (heaterRLStatus == 0)
    {
      digitalWrite(heaterRLLow, LOW);
      digitalWrite(heaterRLHigh, LOW);
    } else if (heaterRLStatus == 1)
    {
      digitalWrite(heaterRLLow, HIGH);
      digitalWrite(heaterRLHigh, LOW);
    } else if (heaterRLStatus == 2)
    {
      digitalWrite(heaterRLLow, HIGH);
      digitalWrite(heaterRLHigh, HIGH);
    }
    break;
  case 4:
    heaterRRStatus = (heaterRRStatus+1)%3;
    if (heaterRRStatus == 0)
    {
      digitalWrite(heaterRRLow, LOW);
      digitalWrite(heaterRRHigh, LOW);
    } else if (heaterRRStatus == 1)
    {
      digitalWrite(heaterRRLow, HIGH);
      digitalWrite(heaterRRHigh, LOW);
    } else if (heaterRRStatus == 2)
    {
      digitalWrite(heaterRRLow, HIGH);
      digitalWrite(heaterRRHigh, HIGH);
    }
    break;
  default:
    break;
  }
}

void trim(int position, bool active)
{
  if (position == 0 and active == false and trimUp == false)
  {
    //Serial.println("Reset TRIM");
    digitalWrite(engTrimDown, LOW);
    tDownTimer = 0;
    trimDown = false;
  }
  if (position == 1 and active == false and trimDown == false)
  {
    //Serial.println("Reset TRIM");
    digitalWrite(engTrimUp, LOW);
    tUpTimer = 0;
    trimUp = false;
  }
  if (position == 0 and active == true and trustTrimDown == true) //Trim Down
  {
    tDownTimer = tDownTimer+1;
    if (tDownTimer < 300)
    {
      Serial.println("DOWN");
      digitalWrite(engTrimDown, HIGH);
      trimDown = true;
      trimUp = false;
    }
    else if (tDownTimer > 1000)
    {
      Serial.println("Trim Down untrust");
      digitalWrite(engTrimUp, LOW);
      digitalWrite(engTrimDown, LOW);
      trustTrimDown = false;
    }
    else
    {
      digitalWrite(engTrimUp, LOW);
      digitalWrite(engTrimDown, LOW);
    }
  }
  if (position == 1 and active == true and trustTrimUp == true) //Trim UP
  {
    tUpTimer = tUpTimer+1;
    if (tUpTimer < 300)
    {
      Serial.println("UP");
      digitalWrite(engTrimUp, HIGH);
      trimDown = false;
      trimUp = true;
    }
    else if (tUpTimer > 1000)
    {
      Serial.println("Trim UP untrust");
      digitalWrite(engTrimUp, LOW);
      digitalWrite(engTrimDown, LOW);
      trustTrimUp = false;
    }
    else
    {
      digitalWrite(engTrimUp, LOW);
      digitalWrite(engTrimDown, LOW);
    }
  }
}

void light(int mode)
{
  if (mode == 0 and lightFixed == false)
  {
    digitalWrite(lightL, HIGH);
    digitalWrite(lightR, HIGH);
    lightFixed = true;
  }
  if (mode == 1 and lightFlash == false)
  {
    if (lTimer == 0 and lightRActive == false)
    {
      digitalWrite(lightR, HIGH);
      digitalWrite(lightL, LOW);
      lightRActive = true;
      lightLActive = false;
    }
    else if (lTimer == 0 and lightLActive == false)
    {
      digitalWrite(lightR, LOW);
      digitalWrite(lightL, HIGH);
      lightRActive = false;
      lightLActive = true;
    }
    lTimer = (lTimer+1)%lightTimer;
  }
  

}