#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <TTGO.h>

bool rele = true;

TTGOClass *ttgo;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";                                               // Необходимо указать токен ведущего устройства

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

// Bridge widget on virtual pin 1
WidgetBridge bridge1(V0);                                       // Необходимо указать виртуальный пин ведомого устройства

static void event_handler(lv_obj_t *obj, lv_event_t event)      // Обработчик нажатия на сенсорную кнопку
{
    if (event == LV_EVENT_VALUE_CHANGED) {
        rele =!rele;
        Serial.println(rele);
        bridge1.virtualWrite(V0, rele);
       }
}

BLYNK_CONNECTED() {
  bridge1.setAuthToken("");                                     // Необходимо указать токен ведомого устройства
}

void setup()
{
    Serial.begin(115200);
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    ttgo->lvgl_begin();
    
    Blynk.begin(auth, ssid, pass);
    
    lv_obj_t *label;
    lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn2, event_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_btn_set_toggle(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Light");

}

void loop()
{
    lv_task_handler();
    Blynk.run();
    delay(5);
}
