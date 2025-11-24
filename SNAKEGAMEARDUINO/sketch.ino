#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

int TFT_CS = 10;
int TFT_DC = 9;
int TFT_RST = 8;
int JOY_X = A0; 
int JOY_Y = A1;
int RESTART_BUTTON = 2;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

int BLACK = 0x0000;
int GREEN = 0x07E0;
int RED = 0xF800;
int WHITE = 0xFFFF;
const int B = 10;
const int W = 240 / B; 
const int H = 320 / B; 

int sx[200]; 
int sy[200]; 
int len; 
int ax, ay; 
int appleValue = 0; 
int dx = 1; 
int dy = 0; 
int score = 0;
bool isGameOver = false;
long lastMoveTime = 0; 
const int moveDelay = 150; 

void restartGame();
void placeApple();
void handleInput();
void updateGame();
void drawBlock(int x, int y, uint16_t color);
void displayScore();

//////
void setup() {
  tft.begin();
  tft.setRotation(0);
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(RESTART_BUTTON, INPUT_PULLUP);
  randomSeed(micros()); 
  restartGame();
}

void loop() {
  if (digitalRead(RESTART_BUTTON) == LOW) { 
    restartGame();
    delay(500); 
    return;
  }
  if (isGameOver) {
    displayScore(); 
    return;
  }

  handleInput();
  if (millis() - lastMoveTime > moveDelay) {
    updateGame();
    lastMoveTime = millis();
  }
}

//////////

void drawBlock(int x, int y, uint16_t color) {
  tft.fillRect(x * B, y * B, B, B, color);
}

void restartGame() {
  len = 9;
  dx = 1; 
  dy = 0;
  score = 0;
  isGameOver = false;
  appleValue = 0;

  tft.fillScreen(BLACK);
  for (int i = 0; i < len; i++) {
    sx[i] = W / 2 - i;
    sy[i] = H / 2;
  }
  placeApple();
}

void placeApple() {
  bool onSnake;
  do {
    onSnake = false;
    ax = random(W);
    ay = random(H);
    for (int i = 0; i < len; i++) {
      if (sx[i] == ax && sy[i] == ay) {
        onSnake = true;
        break;
      }
    }
  } while (onSnake);
  appleValue = random(-5, 10); 
  drawBlock(ax, ay, RED);
}

void handleInput() {
  int x_val = analogRead(JOY_X);
  int y_val = analogRead(JOY_Y);
  
  const int T_LOW = 400;
  const int T_HIGH = 600;

  int new_dx = dx;
  int new_dy = dy;

  if (x_val < T_LOW) { new_dx = 1; new_dy = 0; } 
  else if (x_val > T_HIGH) { new_dx = -1; new_dy = 0; } 
  
  if (y_val < T_LOW) { new_dx = 0; new_dy = 1; } 
  else if (y_val > T_HIGH) { new_dx = 0; new_dy = -1; }

  if ((new_dx != -dx or new_dx == 0) && (new_dy != -dy or new_dy == 0)) {
     dx = new_dx;
     dy = new_dy;
  }
}

void updateGame() {
  int tail_x = sx[len - 1];
  int tail_y = sy[len - 1];

  for (int i = len - 1; i > 0; i--) {
    sx[i] = sx[i - 1];
    sy[i] = sy[i - 1];
  }
  sx[0] += dx;
  sy[0] += dy;

  if (sx[0] < 0 or sx[0] >= W or sy[0] < 0 or sy[0] >= H) {
    isGameOver = true;
    return;
  }
  for (int i = 1; i < len; i++) {
    if (sx[0] == sx[i] && sy[0] == sy[i]) {
      isGameOver = true;
      return;
    }
  }


  if (sx[0] == ax && sy[0] == ay) {
    score += appleValue;
    if (len < 200) {
      len++;
      sx[len - 1] = tail_x;
      sy[len - 1] = tail_y; 
    }
    placeApple();
  } else {
    drawBlock(tail_x, tail_y, BLACK);
  }
  
  drawBlock(sx[0], sy[0], GREEN);
  displayScore();
}

void displayScore() {
  tft.fillRect(0, 0, 150, 20, BLACK); 
  tft.setCursor(5, 5);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(2);
  tft.print("Score: ");
  tft.print(score);
  
  if (isGameOver) {
    tft.setCursor(15, 150); 
    tft.setTextColor(RED, BLACK);
    tft.setTextSize(4);
    tft.println("GAME OVER");
  }
}
