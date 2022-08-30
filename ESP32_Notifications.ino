// Header for this library, from https://www.github.com/Smartphone-Companions/ESP32-ANCS-Notifications.git
#include "esp32notifications.h"

BLENotifications notifications;

// Holds the incoming call's ID number, or zero if no notification
uint32_t incomingCallNotificationUUID;
unsigned long myTime;

// This callback will be called when a Bluetooth LE connection is made or broken.
void onBLEStateChanged(BLENotifications::State state)
{
  switch (state)
  {
  case BLENotifications::StateConnected:
    Serial.println("StateConnected - Connected to a phone or tablet");
    Serial.println("$s$ESP32$*$Connected$*$ESP32 has been connected for notifications");
    myTime = millis();
    break;
  case BLENotifications::StateDisconnected:
    Serial.println("StateDisconnected - Disconnected from a phone or tablet");
    Serial.println("$s$ESP32$*$DISCONNECTED$*$ESP32 is NOT longer connected");
    notifications.startAdvertising();
    ESP.restart();
    break;
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

int numberOfPoints(String myString)
{
  int total = 0;
  for (int i = 0; i < myString.length(); i++)
  {
    if (myString.charAt(i) == '.')
    {
      total++;
    }
  }
  return total;
}

void onNotificationArrived(const ArduinoNotification *notification, const Notification *rawNotificationData)
{
  if (millis() - myTime > 10000)
  {
    Serial.println("------------------------------------------");
    Serial.println("$s$" + getValue(notification->type, '.', numberOfPoints(notification->type)) + "$*$" + (notification->title) + "$*$" + (notification->message));
    // The next lines are only to see the message in the serial monitor more clearly. The Python file will ignore these lines
    // App name // Separate by dots and take the last one
    Serial.println(getValue(notification->type, '.', numberOfPoints(notification->type)));
    // Notification title
    Serial.println(notification->title);
    // Notification info
    Serial.println(notification->message);
    // Serial.println(notifications.getNotificationCategoryDescription(notification->category));  // ie "social media"
    // Serial.println(notification->categoryCount); // How may other notifications are there from this app (ie badge number)
    //  If there is a call
    if (notification->category == CategoryIDIncomingCall)
    {
      Serial.println("Someone is calling");
    }
  }
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }
  Serial.println("ESP32 Started");
  Serial.println("------------------------------------------");
  notifications.begin("notif win"); // Bluetooth Name
  notifications.setConnectionStateChangedCallback(onBLEStateChanged);
  notifications.setNotificationCallback(onNotificationArrived);
}

void loop() {}
