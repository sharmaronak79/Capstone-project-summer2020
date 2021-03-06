#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>   // header file of Blynk app for ESP32

#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"

#define LED 4  //connect flash led with gpio 4
#define BUTTON 12   //connect button with gpio 12

const char* ssid = "  WAQAS";   //username
const char* password = "Rogers3082";  //enter password
char auth[] = "i1K6e0AKRGTDsm_sH8hpmp2-OPMAyggD";   //type authetication token which is received upon creating a new project in Blynk

String my_Local_IP;

void startCameraServer();


void capture()
{
  digitalWrite(LED,HIGH);   //set led status as high
  uint32_t number = random(40000000);
  Blynk.notify("Someone is attacking");   //set blynk notifications
  Serial.println("http://"+my_Local_IP+"/capture?_cb="+ (String)number);   // image link sent to serial monitor
  Blynk.setProperty(V1, "urls", "http://"+my_Local_IP+"/capture?_cb="+(String)number);  //set visions v1
   Blynk.setProperty(V2, "urls", "http://"+my_Local_IP+"/capture?_cb="+(String)number);   //set vision v2
  Blynk.setProperty(V3, "urls", "http://"+my_Local_IP+"/capture?_cb="+(String)number);     //set vision v3
 
  delay(1000);
  digitalWrite(LED,LOW);
  
}
void setup() {
  Serial.begin(115200);  //set baurd rate
  pinMode(LED,OUTPUT);  //set led as an ouput
  Serial.setDebugOutput(true);
  Serial.println();
//configure pins of camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  //initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);//flip it back
    s->set_brightness(s, 1);//up the blightness just a bit
    s->set_saturation(s, -2);//lower the saturation
  }
  //drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

#if defined(CAMERA_MODEL_M5STACK_WIDE)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

  WiFi.begin(ssid, password);  //begin wifi with username and password

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");   //print wifi connected

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  my_Local_IP = WiFi.localIP().toString();
  Serial.println("' to connect");
  Blynk.begin(auth, ssid, password);   // begin the function of connecting ESP32 with Blynk and internet
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();                         // keeps connection alive,send and receive data
  if(digitalRead(BUTTON) == HIGH)     //if the button is pressed then picture will be clicked
  capture();
}
