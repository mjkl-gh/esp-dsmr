#if defined(M5STICKC) || defined(M5STICKCPLUS)

#if defined(M5STICKC)
#include <M5StickC.h>
#endif

#if defined(M5STICKCPLUS)
#include <M5StickCPlus.h>
#endif

#include <time.h>
#include <lwip/apps/sntp.h>

RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

void displaySetup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  
  M5.Lcd.setTextSize(1.2);
  M5.Lcd.setCursor(40, 0, 2);
  M5.Lcd.println("ESP-DSMR PROTOTYPE V2");
  RTC_TimeTypeDef TimeStruct;
  TimeStruct.Hours   = 18;
  TimeStruct.Minutes = 56;
  TimeStruct.Seconds = 10;
  M5.Rtc.SetTime(&TimeStruct);
  RTC_DateTypeDef DateStruct;
  DateStruct.WeekDay = 3;
  DateStruct.Month = 3;
  DateStruct.Date = 22;
  DateStruct.Year = 2019;
  M5.Rtc.SetData(&DateStruct);
}

void displayLoop() {
  static uint32_t lastCycle;
  // put your main code here, to run repeatedly:
  if (lastCycle - millis() > 500) {
    lastCycle = millis();
    time_t now = time(nullptr);
    auto datetime = localtime(&now);
    M5.Lcd.setCursor(0, 15);
    M5.Lcd.printf("Data: %02d-%02d-%04d\n",datetime->tm_mday, datetime->tm_mon, datetime->tm_year+1900);
    M5.Lcd.printf("Time: %02d : %02d : %02d\n",datetime->tm_hour, datetime->tm_min, datetime->tm_sec);
  }
}
#endif