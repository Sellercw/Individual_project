// Colin Sellers
// Individual Project
// ECE387
// 5/8/2022


//include statements
#include <UTFT.h>
#include <URTouch.h>

// Object initlization 
UTFT    myGLCD(ITDB32S_V2,38,39,40,41);
URTouch  myTouch( 6, 5, 4, 3, 2);

// Pins
const int VCC = 11;
const int button = 12;
const int joystick = 10;
const int buzzer = 13;

// Declare variables 
extern uint8_t BigFont[];
extern uint8_t SmallFont[];
char currentPage;
int score;
int highScore;
int x, y;
int robotY, objX, objY;
float objSpeed = 2.6;
int fallRateInt;
float fallRate;
bool gameStart = false;
bool screenPressed = false;
int buttonState = 0;



// Functions

// Highlights the button when pressed
void drawFrame(int x1, int y1, int x2, int y2) {
  myGLCD.setColor(VGA_AQUA);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (x1, y1, x2, y2);
}

void drawHomeScreen(){
  myGLCD.setFont(BigFont);
  myGLCD.fillScr(VGA_GRAY);
  myGLCD.setColor(VGA_AQUA);
  myGLCD.setBackColor(VGA_GRAY);
  myGLCD.print("Video Game", CENTER, 10);
  myGLCD.setFont(SmallFont);
  myGLCD.print("by Colin Sellers", CENTER, 30);
  drawFrame(80,10,238,43);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.fillRoundRect(70,100,250,140);
  myGLCD.fillRoundRect(70,160,250,200);
  myGLCD.setColor(VGA_AQUA);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.setFont(BigFont);
  myGLCD.print("START!", CENTER, 115);
  myGLCD.print("How to Play", CENTER, 175);  
}

void setupGame(){
  myGLCD.clrScr(); 
  myGLCD.fillScr(VGA_GRAY);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.fillRoundRect(278,0,319,15);
  myGLCD.setFont(SmallFont);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.setColor(VGA_AQUA);
  myGLCD.print("reset", RIGHT, 0);
  myGLCD.setBackColor(VGA_GRAY);
  score = 0;
  robotY = 198;
  fallRateInt = 0;
  fallRate = 0;
  objX = 319;
  objY = 170;
  myGLCD.print("Score: ", LEFT, 225);  
  myGLCD.print("High Score: ", LEFT, 5);
  updateScore();
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawLine(0,200,319,200);
  myGLCD.drawLine(0,20,319,20);
  drawRobot(robotY);
  myGLCD.setFont(BigFont);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setBackColor(VGA_GRAY);
  myGLCD.print("READY?", CENTER, 120);
  delay(1000);
  myGLCD.setColor(VGA_GRAY);
  myGLCD.fillRect(100, 100, 300, 140);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print("GO!", CENTER, 120);
  delay(500);
  myGLCD.setColor(VGA_GRAY);
  myGLCD.fillRect(100, 100, 300, 140);
  gameStart = true;  
}

void gameOver(){
currentPage = '3';
myGLCD.clrScr();
myGLCD.fillScr(VGA_GRAY);
myGLCD.setFont(BigFont);
myGLCD.setColor(VGA_WHITE);
myGLCD.setBackColor(VGA_GRAY);
myGLCD.print("GAME OVER!", CENTER, 100);
myGLCD.print("Final Score: ", CENTER, 130);
myGLCD.printNumI(score, 250, 130);  
myGLCD.setBackColor(VGA_WHITE);
myGLCD.fillRoundRect(270,0,319,15);
myGLCD.setFont(SmallFont);
myGLCD.setColor(VGA_AQUA);
myGLCD.print("return", RIGHT, 0);
if(score > highScore) {
  highScore = score; 
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(VGA_GRAY);
  myGLCD.print("New High Score!", CENTER, 160); 
  delay(1000);
  myGLCD.setColor(VGA_GRAY);
  myGLCD.fillRect(10, 150, 310, 190);
  delay(500);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print("New High Score!", CENTER, 160); 
  delay(1000);
  myGLCD.setColor(VGA_GRAY);
  myGLCD.fillRect(10, 150, 310, 190);
  delay(500);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print("New High Score!", CENTER, 160);
  delay(1000);
  myGLCD.setColor(VGA_GRAY);
  myGLCD.fillRect(10, 150, 310, 190);
  delay(500);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print("New High Score!", CENTER, 160);
}
score = 0;
}

void updateScore(){
  myGLCD.setFont(SmallFont);
  myGLCD.setColor(VGA_GRAY);
  myGLCD.fillRect(49,225,319,250);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.printNumI(score, 50, 225);  
  myGLCD.setColor(VGA_GRAY);
  myGLCD.fillRect(90,4,200,10);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.printNumI(highScore, 90, 5); 
  
}

void drawRobot(int y){
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRect(10,y,40,y-30);
  myGLCD.drawRect(15,y-5,35,y-10);
  myGLCD.drawRect(15,y-20,20,y-25);
  myGLCD.drawRect(30,y-20,35,y-25);
  myGLCD.setColor(VGA_GRAY);
  myGLCD.fillRect(10,y-31,40,y-40);
  myGLCD.fillRect(11,y-1,14,y-29);
  myGLCD.fillRect(36,y-1,39,y-29);
  myGLCD.fillRect(11,y-1,39,y-4);
  myGLCD.fillRect(11,y-26,39,y-29);
  myGLCD.fillRect(11,y-11,39,y-19);
  myGLCD.fillRect(21,y-19,29,y-25);
  myGLCD.fillRect(16,y-6,34,y-9);
  myGLCD.fillRect(16,y-21,19,y-24);
  myGLCD.fillRect(31,y-21,34,y-24);
  if((objX-30 <= 40 || objX <=40)&& y<=194){
    myGLCD.fillRect(10,y+1,40, y+5);  
  } else {
    myGLCD.fillRect(10,y+1,40,199);
  }
}

void drawObj(int x, int y){
    myGLCD.setColor(VGA_BLUE);
    myGLCD.fillRect(x,y, x-30, 199);
    if(x <= 319) {
      myGLCD.setColor(VGA_GRAY);
      myGLCD.fillRect(x+1,y,x+5,199);  
    }
    
}


void showRules(){
  myGLCD.fillScr(VGA_GRAY);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.fillRoundRect(270,0,319,15);
  myGLCD.setFont(SmallFont);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.setColor(VGA_AQUA);
  myGLCD.print("return", RIGHT, 0);
   myGLCD.setBackColor(VGA_GRAY);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print("score: ", LEFT, 225);  
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawLine(0,200,319,200);
  myGLCD.drawLine(0,20,319,20);
  drawRobot(198);
  drawObj(319,170);
  myGLCD.setFont(BigFont);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setBackColor(VGA_GRAY);
  myGLCD.print("Tap Screen to jump!", CENTER, 120);
  delay(1000);
  myGLCD.setColor(VGA_GRAY);
  myGLCD.fillRect(10, 100, 310, 140);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print("Avoid the blue!", CENTER, 120);
  delay(1000);
  myGLCD.setColor(VGA_GRAY);
  myGLCD.fillRect(10, 100, 310, 140);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print("Good luck!", CENTER, 120);
  delay(1000);
  currentPage = '0'; // home screen
  myGLCD.clrScr(); 
  drawHomeScreen();
}
  
void setup() {
  // Pin init
  pinMode(VCC, OUTPUT);
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(VCC, HIGH); // +5V - Pin 13 as VCC
  // Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  drawHomeScreen(); 
  currentPage = '0';
}

void loop() {
  if (currentPage == '0') { // Home page 
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x=myTouch.getX(); 
      y=myTouch.getY();
      if((x>=70) && (x<=250) && (y>=100) && (y<=140)){
        drawFrame(70,100,250,140);
        currentPage = '1'; // game screen
        setupGame();
        }
      if((x>=70) && (x<=250) && (y>=160) && (y<=200)){
        drawFrame(70,160,250,200);
        currentPage = '2'; // rules screen
        myGLCD.clrScr(); 
        showRules();
        }  
      }
  }
  // Game page 
  if (currentPage == '1') {      
      // Start game
      if(gameStart){
        objX = objX - objSpeed;
        if(objX <= -25) {
          objX = 320; 
          objY= random(130, 180); 
          score++;
          updateScore();
        }
        
        drawObj(objX, objY);
        robotY+=fallRateInt;
        fallRate=fallRate+0.2;
        fallRateInt = int(fallRate);
        if (robotY>=199) { // stops falling at ground
          robotY=198;
        } 
        if (robotY-30 <= 21) { // stops from going through ceiling 
          robotY = 51; 
        }  
        drawRobot(robotY); 
        if(score%5 == 0) {
          objSpeed += random(0.3,0.6);  
        }

        // Detect collison: robot(10,y,40,y-30), obj(objX,objY, objX-30, 199)
        if(((objX-30 >= 10 && objX-30 <= 40)||(objX >= 10 && objX <= 40)) && (robotY >= objY)){
          tone(buzzer,400);
          delay(200);
          noTone(buzzer); 
          tone(buzzer,300);
          delay(200);
          noTone(buzzer); 
          tone(buzzer,100);
          delay(400);
          noTone(buzzer);  
          gameOver();
        }

        buttonState = digitalRead(button);
        if(buttonState == HIGH && (robotY == 198)){
          fallRate=-7;   
          tone(buzzer,2400);
          delay(10);
          noTone(buzzer);
        }
        if (myTouch.dataAvailable() && !screenPressed) {
          screenPressed = true;
          myTouch.read();
          x=myTouch.getX(); 
          y=myTouch.getY();
          // if((x>=10) && (x<=40) && (y>=robotY-30) && (y<=robotY) && (robotY == 198)){
          if(y>=20 && y<=200 && (robotY == 198)){
            fallRate=-7;
            tone(buzzer,2400);
            delay(10);
            noTone(buzzer);
          }  
        } else if ( !myTouch.dataAvailable() && screenPressed){
            screenPressed = false;
        }
        if((x>=278) && (x<=319) && (y>=0) && (y<=15)){
            drawFrame(278,0,319,15);
            currentPage = '0'; // home screen
            gameStart = false;
            myGLCD.clrScr(); 
            drawHomeScreen(); 
            }  
      }
       
  }
  // Rule page
  if (currentPage == '2') {  
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x=myTouch.getX(); 
      y=myTouch.getY();
      if((x>=270) && (x<=319) && (y>=0) && (y<=15)){
        drawFrame(270,0,319,15);
        currentPage = '0'; // home screen
        myGLCD.clrScr(); 
        drawHomeScreen(); 
        }
      } 
  }

  if (currentPage == '3') {
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x=myTouch.getX(); 
      y=myTouch.getY();
      if((x>=270) && (x<=319) && (y>=0) && (y<=15)){
        drawFrame(270,0,319,15);
        currentPage = '0'; // home screen
        myGLCD.clrScr(); 
        drawHomeScreen(); 
        }
      }
  }
    
}
