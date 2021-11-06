# 1 "e:\\Code\\Arduino\\SoftFinger-esp32\\SoftFinger-esp32.ino"
# 2 "e:\\Code\\Arduino\\SoftFinger-esp32\\SoftFinger-esp32.ino" 2
# 3 "e:\\Code\\Arduino\\SoftFinger-esp32\\SoftFinger-esp32.ino" 2
# 4 "e:\\Code\\Arduino\\SoftFinger-esp32\\SoftFinger-esp32.ino" 2
# 5 "e:\\Code\\Arduino\\SoftFinger-esp32\\SoftFinger-esp32.ino" 2
# 6 "e:\\Code\\Arduino\\SoftFinger-esp32\\SoftFinger-esp32.ino" 2

#define CONTRACT_PIN 32
#define RESET_PIN 33
#define MIDDLE_PIN 35

#define STANDALONE_ 5

// 定义外部中断的Mode
// 0: 无中断，读取Touch值
// 1：Touch中断，执行 TouchEvent()
// 2: 外部IO的中断
#define EXT_ISR_MODE 2

Hand *hand;
BreathingLED *led;
Buzzer *buzzer;

BLE *ble;

void contractIT();
void resetIT();
void standaloneIT();

void setup()
{
  // start serials
  // debug serial
  Serial.begin(115200);
  // servo control serial
  Serial2.begin(1000000);

  // init peripherals
  led = new BreathingLED(LED(18, 19, 21, 22), 2000);
  buzzer = new Buzzer(26, 25, 27);
  // init btns
  pinMode(32, 0x01);
  pinMode(33, 0x01);
  pinMode(35, 0x01);
  // attachInterrupt(CONTRACT_PIN, contractIT, RISING);
  // attachInterrupt(RESET_PIN, resetIT, RISING);
  // attachInterrupt(MIDDLE_PIN, standaloneIT, RISING);

  // wait to connect to ble
  led->getRawLED()->bAnalog(255);
  ble = new BLE("Awesome Hand ESP32");
  // ble->waitForConnection();
  buzzer->buzzFor(100);
  delay(100);
  buzzer->buzzFor(100);
  delay(1000);

  // init hand
  hand = new Hand(&Serial2, led, buzzer);
  led->setColor(0, 255, 0);

  buzzer->buzzFor(100);
  delay(100);
  buzzer->buzzFor(100);
  delay(100);
  buzzer->buzzFor(100);
}

void loop()
{
  led->update();
  // Serial.println(led->curLevel);
  // Serial.println(millis());
  hand->update();
  if (ble->isAvailable())
  {
    std::string cmd = ble->getRecv();
    // Serial.println(cmd.c_str());
    if ('1' <= cmd[0] && cmd[0] <= '5')
    {
      Serial.println(atoi(cmd.substr(2,3).c_str()));
      hand->turnFinger(cmd[0]-'0', atoi(cmd.substr(2,3).c_str()));
    }
    else if (cmd[0] == 'c')
      hand->contract(atoi(cmd.substr(2, 2).c_str()));
    else if (cmd[0] == 'l')
      hand->fingerReset();
  }

  if (digitalRead(32) == 0x1)
    contractIT();
  else if (digitalRead(33) == 0x1)
    resetIT();
  else if (digitalRead(35) == 0x1)
    standaloneIT();
}

void contractIT()
{
  hand->turnFinger(5, 200);
}

void resetIT()
{
  hand->fingerReset();
}

void standaloneIT()
{
  hand->turnFinger(5, 280);
}

/**

 * AT debug

 */
# 115 "e:\\Code\\Arduino\\SoftFinger-esp32\\SoftFinger-esp32.ino"
//#include <SoftwareSerial.h>
////Pin10为RX，接HC05的TX针脚
////Pin11为TX，接HC05的RX针脚
//SoftwareSerial BT(3, 4);
//char val;
//
//void setup() {
//  Serial.begin(38400);
//  Serial.println("Buletooth is ready!");
//  // HC-05默认，38400
//  BT.begin(38400);
//}
//
//void loop() {
//  if (Serial.available()) {
//    val = Serial.read();
//    BT.print(val);
//  }
//
//  if (BT.available()) {
//    val = BT.read();
//    Serial.print(val);
//  }
//}

/**

 * Breathing LED demo

 */
# 143 "e:\\Code\\Arduino\\SoftFinger-esp32\\SoftFinger-esp32.ino"
// #include "LED.h"
// #include "BreathingLED.h"

// // LED led = LED(9, 11, 10, 8);
// BreathingLED led = BreathingLED(LED(9, 11, 10, 8), 3000);

// void setup() {
//   led.init();
//   led.setColor(50, 200, 230);
//   Serial.begin(9600);
// }

// void loop() {
//   led.update();
// }

/**

 * test

 */
# 162 "e:\\Code\\Arduino\\SoftFinger-esp32\\SoftFinger-esp32.ino"
// #include "Buzzer.h"

// Buzzer buzzer(6,5,7);

// // #include "Hand.h"

// void setup()
// {
//   // Hand hand = Hand(&Serial);
//   // Serial.begin(9600);
//   buzzer.init();
//   // buzzer->init();
//   // buzzerInit();
// }

// void loop()
// {
//   buzzer.buzz();
//   // digitalWrite(6, HIGH);
//   // delayMicroseconds(1e6 / 300 / 2);
//   // digitalWrite(6, LOW);
//   // delayMicroseconds(1e6 / 300 / 2);
// }
