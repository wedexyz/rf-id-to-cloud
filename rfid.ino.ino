#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN    21
#define RST_PIN   22
#define SIZE_BUFFER     18
#define MAX_SIZE_BLOCK  16

#define FIREBASE_HOST "user-49128.firebaseio.com"
#define FIREBASE_AUTH "IDY4zJ8JI6SSpkODLNiFP4vNEooA2xQukpsuvuK9"
#define WIFI_SSID "S50"
#define WIFI_PASSWORD "widhiwinata"

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

int n=0; 

void setup() {
  Serial.begin(9600);
  Serial.println("LABEL,Date,Time,Nama");
  SPI.begin();     
  mfrc522.PCD_Init();   
                                             
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
byte block;
byte len;

if ( ! mfrc522.PICC_IsNewCardPresent()) {
return;
}

if ( ! mfrc522.PICC_ReadCardSerial()) {
return;
}
Serial.println(F("**Card Detected:**"));
byte buffer1[18];
block = 4;
len = 18;
status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));

if (status != MFRC522::STATUS_OK) {
return;
}
    status = mfrc522.MIFARE_Read(block, buffer1, &len);
if (status != MFRC522::STATUS_OK) {
  return;
  }
    String value = "";
    for (uint8_t i = 0; i < 16; i++)
{
value += (char)buffer1[i];
}
value.trim();
    Serial.print(value);
    Serial.println(F("\n**End Reading**\n"));
mfrc522.PICC_HaltA();
mfrc522.PCD_StopCrypto1();




Serial.println( (String) "DATA,DATE,TIME," + value + ",AUTOSCROLL_20" );




    if(value=="widhi"){
  Firebase.pushInt("nomor", n++);
//  Firebase.pushString("waktu", String ((String)""+(daysOfTheWeek[timeClient.getDay()])+":"+(jam)+":"+(menit)+":"+(detik)+" "+" Widhi"+"")); 
 Firebase.pushString("Nama"," Widhi"); 
   
    }
 
  if(value=="sutran"){
  Firebase.pushInt("nomor", n++);
Firebase.pushString("Nama"," sutran"); 


    }
  }


