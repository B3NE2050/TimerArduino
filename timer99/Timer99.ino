//Declaracao de pinos usados
int display2[7] = {14, 15, 16, 17, 18, 19, 2 };
int display1[7] = {9, 13, 7, 6, 5, 4, 3 };

int addButton = 10;
int lessButton = 11;
const int beeper = 12;

//funcoes abaixo do loop
void showDecimal(int decimal, int display);

void onLed(int position);

void offLed(int position);
void offDisplay(int display);
int offAll();

int timeSelection();
int countSeconds();
int makeBeep();

//Variaveis globais
int valD = 0, valD2 = 0;

//Inicializacao
void setup() {
  // put your setup code here, to run once:
  for(int pino = 0; pino < 8; pino++){
    pinMode(display1[pino], OUTPUT);
    pinMode(display2[pino], OUTPUT);
  }

  pinMode(addButton, INPUT_PULLUP);
  pinMode(lessButton, INPUT_PULLUP);

  pinMode(beeper, OUTPUT);
  
  offAll();
}

//Loop
void loop() {
  valD = 0;
  valD2 = 0;
  makeBeep();
  timeSelection(); 
  countSeconds();
}

int makeBeep(){
  for(int i = 0; i < 2; i++){
    tone(beeper, 500); // Send 1KHz sound signal...
    delay(200);        // ...for 1 sec
    noTone(beeper);   // Stop sound...
  }
  return 1;
}

int timeSelection(){
  int selected = 0;
  byte addButtonStats;
  byte lessButtonStats;

  showDecimal(valD, 0);
  showDecimal(valD2, 1);

  while(!selected){
    addButtonStats = digitalRead(addButton);
    lessButtonStats = digitalRead(lessButton);

    if(addButtonStats == LOW){
      if(valD == 9 && valD2 < 9) {
        valD = 0;
        valD2 += 1;
      }else{
          if(!(valD == 9 && valD2 == 9))
            valD += 1;
      }
    }

    if(lessButtonStats == LOW){
      selected = 1;
      return selected;
    }

    offAll();

    showDecimal(valD, 0);
    showDecimal(valD2, 1);

    delay(150);
  }
}

int countSeconds(){
  int finished = 0;
  byte lessButtonStats;
  lessButtonStats = digitalRead(lessButton);

  while(!finished){
    if(lessButtonStats == LOW){
      finished = 1;
      delay(500);
    }

    while(valD2 >= 0){
      while(valD >= 0){
        offAll();

        showDecimal(valD, 0);
        showDecimal(valD2, 1);

        valD--;

        delay(1000);
      }
      if(valD2 > 0)
        valD = 9;
      valD2--;
    }
  }
}

void onLed(int position){
  digitalWrite(position, LOW);    
}

void offLed(int position){
  digitalWrite(position, HIGH);
}

int offAll(){
  for(int i = 0; i < 8; i++){
    offLed(display1[i]);
    offLed(display2[i]);
  }
  return 1;
}
void offDisplay(int display){
  for(int i = 0; i < 8; i++){
    if(display){
      offLed(display1[i]);
    }else{
      offLed(display2[i]);
    }
  }
}

void onPositions(int positions[7]){
  for(int i = 0; i < 8; i++){
    if(positions[i] != 0){
      onLed(positions[i]);
    }
  }
}
void showDecimal(int decimal, int display){
   int a, b, c, d, e, f, g;
   if(display){
      a = display2[0];
      b = display2[1];
      c = display2[2];
      d = display2[3];
      e = display2[4];
      f = display2[5];
      g = display2[6];
   }else{
      a = display1[0];
      b = display1[1];
      c = display1[2];
      d = display1[3];
      e = display1[4];
      f = display1[5];
      g = display1[6];
   }

  if(decimal == 0){
    int positions[7] = {a, b, c, d, e, f, 0};
    onPositions(positions);
  }
   if(decimal == 1){
    int positions[7] = {b, c, 0, 0, 0, 0, 0};
    onPositions(positions);
  }
   if(decimal == 2){
    int positions[7] = {a, b, g, e, d, 0, 0};
    onPositions(positions);
  }
   if(decimal == 3){
    int positions[7] = {a, b, g, c, d, 0, 0};
    onPositions(positions);
  }
   if(decimal == 4){
    int positions[7] = {f, b, g, c, 0, 0, 0};
    onPositions(positions);
  }
   if(decimal == 5){
    int positions[7] = {a, f, g, c, d, 0, 0};
    onPositions(positions);
  }
   if(decimal == 6){
    int positions[7] = {a, f, g, c, d, e, 0};
    onPositions(positions);
  }
   if(decimal == 7){
    int positions[7] = {a, b, c, 0, 0, 0, 0};
    onPositions(positions);
  }
   if(decimal == 8){
    int positions[7] = {a, b, c, d, e, f, g};
    onPositions(positions);
  }
   if(decimal == 9){
    int positions[7] = {a, b, c, d, 0, f, g};
    onPositions(positions);
  }
  // if(decimal == 10){
  //   int positions[7] = {a, 0, g, 0, 0, 0, 0};
  //   onPositions(positions);
  // }
}