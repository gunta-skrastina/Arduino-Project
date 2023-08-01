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
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
  }
  else
    setupBlinkingMode();
}

void setupBlinkingMode()
{
  digitalWrite(GREEN_PIN, LOW);

  static unsigned long blinkTime = 0;

  if (millis() - blinkTime >= 1000)
  {
    blinkTime = millis();
    digitalWrite(YELLOW_PIN, !digitalRead(YELLOW_PIN));
    digitalWrite(RED_PIN, !digitalRead(RED_PIN));
  }
}
