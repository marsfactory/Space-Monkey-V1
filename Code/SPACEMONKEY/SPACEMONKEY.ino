//  _____ ____   ____    __    ___      ___ ___   ___   ____   __  _    ___  __ __ 
// / ___/|    \ /    |  /  ]  /  _]    |   |   | /   \ |    \ |  |/ ]  /  _]|  |  |
//(   \_ |  o  )  o  | /  /  /  [_     | _   _ ||     ||  _  ||  ' /  /  [_ |  |  |
// \__  ||   _/|     |/  /  |    _]    |  \_/  ||  O  ||  |  ||    \ |    _]|  ~  |
// /  \ ||  |  |  _  /   \_ |   [_     |   |   ||     ||  |  ||     \|   [_ |___, |
// \    ||  |  |  |  \     ||     |    |   |   ||     ||  |  ||  .  ||     ||     |
//  \___||__|  |__|__|\____||_____|    |___|___| \___/ |__|__||__|\_||_____||____/ 

// Juguete sonoro programable basado en el chip attiny85

int buttonPin1 = 1;
int buttonPin2 = 3;
int freqLFO = 0;
int potenciometro = 0;

int buttonState1 = 0;
int lastButtonState1 = 0;
int count = -1;

int buttonState2 = 0;
int lastButtonState2 = 0;
int umbral = 900;

float escalablues[36] = {65.41, 73.42, 77.78, 82.41, 98.00, 110.0, 130.81, 146.83, 155.56, 164.81, 196.00, 220.00, 261.63, 293.67, 311.13, 329.63 , 392.00, 440.00, 523.25, 587.33, 622.25, 659.26, 783.99, 880.00, 1046.50, 1567.98, 1244.51, 1318.51, 1567.98, 1760.00, 2093.01, 2349.32, 2637.02, 2637.02, 3135.96, 3520.00};
int escalaspace[] = {66, 75, 80, 90, 100, 110, 120, 130, 140, 200, 300, 350, 400, 480, 700, 750, 800, 900, 954, 999, 1000, 1200, 1400, 1700, 2000, 2300, 2500, 2600, 3000, 3300, 3333, 3600, 2345, 2500, 2800, 400, 700};
int gamelin[36] = {65, 69, 78, 98, 104, 116, 131, 139, 156, 196, 208, 233, 262, 277, 311, 392, 415, 466, 523, 554, 622, 784, 831, 932, 1046, 1109, 1244, 1568, 1661, 1865, 2093, 2217, 2489, 3136, 3322, 3729};
int bancos = 2;

int LFO[] = {5, 10, 25, 50, 100, 200, 400, 800, 1600};

void setup() {

  pinMode(0, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  digitalWrite(buttonPin1, HIGH);
  pinMode(buttonPin2, INPUT_PULLUP);
  digitalWrite(buttonPin2, HIGH);

}

// the loop function runs over and over again forever
void loop() {



  lecturaBotones () ;

  freqLFO = analogRead (A2);
  potenciometro = analogRead (A1);
  potenciometro = analogRead (A1);
  int playescala = map ( potenciometro, 0, 899, 35, 0 );
  int playlfo = map (freqLFO, 0, 1023, 8, 0);


  switch (count) {

    case 0: // marcianblues scale
      if (potenciometro < umbral) {
        tone ( 0, escalablues[playescala]);
        delay (LFO[playlfo]);
      }
      else {
        noTone (0);
      }
      break;

    case 1: // spacerockers, sacandole el "brake" genera una especie de LFO
      if (potenciometro < umbral) {
        tone ( 0, escalaspace[playescala]);
        delay (LFO[playlfo] );
      }
      else {
        noTone (0);
      }

    case 2: // GAMELIN
      if (potenciometro < umbral) {
        tone ( 0, gamelin[playescala]);
        delay (LFO[playlfo] );
      }
      else {
        noTone (0);
      }
      break;


  }
}

void lecturaBotones () {

  // read the state of the switch into a local variable:
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 != lastButtonState1 && buttonState1 == HIGH) {
    // if the state has changed, increment the counter
    count++;
    delay(10);
    if (count > bancos) {
      count = 0;
    }
  }

  lastButtonState1 = buttonState1;

  buttonState2 = digitalRead(buttonPin2);
  if (buttonState2 != lastButtonState2 && buttonState2 == HIGH) {
    // if the state has changed, increment the counter
    count--;
    delay(10);
    if (count < 0) {
      count = bancos;
    }
  }
  lastButtonState2 = buttonState2;

}
/*
  Octavas, notas y frecuencias correspondientes expresadas en números enteros:
  C      C#     D      D#     E      F      F#     G      G#     A      A#     B
  16   , 17   , 18   , 19   , 21   , 22   , 23   , 25   , 26   , 27   , 28   , 31
  33   , 36   , 37   , 39   , 41   , 44   , 46   , 49   , 52   , 55   , 58   , 62
  65   , 69   , 73   , 78   , 82   , 87   , 92   , 98   , 104  , 110  , 116  , 123
  139  , 139  , 147  , 156  , 165  , 175  , 185  , 196  , 208  , 220  , 233  , 247
  262  , 277  , 294  , 311  , 330  , 349  , 370  , 392  , 415  , 440  , 466  , 494
  523  , 554  , 587  , 622  , 659  , 698  , 740  , 784  , 831  , 880  , 932  , 987
  1047 , 1109 , 1175 , 1245 , 1319 , 1397 , 1480 , 1568 , 1661 , 1760 , 1865 , 1976
  2093 , 2217 , 2349 , 2489 , 2637 , 2794 , 2960 , 3136 , 3322 , 3520 , 3729 , 3951
  4186 , 4435 , 4699 , 4978 , 5274 , 5588 , 5920 , 6272 , 6645 , 7040 , 7459 , 7902
*/

