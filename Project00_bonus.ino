//             _____            .___    .__                           
//            /  _  \_______  __| _/_ __|__| ____   ____              
//           /  /_\  \_  __ \/ __ |  |  \  |/    \ /  _ \             
//          /    |    \  | \/ /_/ |  |  /  |   |  (  <_> )            
//          \____|__  /__|  \____ |____/|__|___|  /\____/             
//                  \/           \/             \/                    
// __________               __         _________            .___      
// \______   \ ____   _____/  |______  \_   ___ \  ____   __| _/____  
//  |     ___// __ \ /    \   __\__  \ /    \  \/ /  _ \ / __ |/ __ \ 
//  |    |   \  ___/|   |  \  |  / __ \\     \___(  <_> ) /_/ \  ___/ 
//  |____|    \___  >___|  /__| (____  /\______  /\____/\____ |\___  >
//                \/     \/          \/        \/            \/    \/ 

#define BUTTON_PIN 2
#define GREEN_PIN 3
#define YELLOW_PIN 4
#define RED_PIN 5

void setup()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
}

void loop()
{
  static bool flag = true;
  static bool clickOne = true;
  int currentButtonState = digitalRead(BUTTON_PIN);

  if (currentButtonState == LOW)
  {
    clickOne = true;
  }
  
  if (currentButtonState == HIGH && clickOne)
  {
    clickOne = false;
    flag = !flag;
  }

  if (flag)
  {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
  }
  else
    setupBlinkingMode(clickOne);

}

void setupBlinkingMode(bool clickOne)
{
  digitalWrite(GREEN_PIN, LOW);


  digitalWrite(YELLOW_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
  smartDelay(2000, clickOne);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
  smartDelay(2000, clickOne);

}

void smartDelay(int time, bool clickOne)
{
  const int refreshTime = 10;

  while ((digitalRead(BUTTON_PIN) != HIGH || !clickOne) && time > 0)
  {
    delay(refreshTime);
    time -= refreshTime;
  }
}
