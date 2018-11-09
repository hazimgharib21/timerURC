int robotDetectSensor;
int preRobotDet = 1;
bool robotDetected;
int lap = 0;
unsigned long startTime = 0;
bool gameStart = false;
unsigned long elapsedTime = 0;
int minit, second, lastSecond =  0;

void setup() {
    pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {

  if(Serial.available() > 0){
    lap = 0;
    gameStart = false;
    lastSecond = 0;
    Serial.println("00 : 00");
    Serial.read();
  }
  robotDetectSensor = digitalRead(2);
  
  if((preRobotDet == 0) && (robotDetectSensor == 1))
  {
    preRobotDet = robotDetectSensor;
  }
  else if((preRobotDet == 1) && (robotDetectSensor == 0))
  {
    preRobotDet = robotDetectSensor;
    if(lap == 0){
      if(!gameStart){
        
      Serial.println("Game Start");
      startTime = millis();
      gameStart = true;
      }
      else{
        Serial.print(minit);
        Serial.print(" Minutes");
        Serial.print(second);
        Serial.println(" Seconds");
      }
    }
  }

  if(gameStart){

    elapsedTime = millis() - startTime;
    int formatedTime = elapsedTime/1000L;
    second = formatedTime % 60;
    minit = formatedTime / 60;
    
    if(second - lastSecond >= 1 || second - lastSecond == -59){
        char buffer[4];
        snprintf(buffer,sizeof(buffer), "%02d", minit);
        Serial.print(buffer);
        Serial.print(" : ");
        snprintf(buffer,sizeof(buffer), "%02d", second);
        Serial.println(buffer);
        lastSecond = second;
    }

    if(minit ==  3){
      Serial.println("Game End");
      gameStart = false;
      Serial.println("00 : 00");
      lastSecond = 0;
    }
    
  }
  
}
