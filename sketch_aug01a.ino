#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Anirudh's iPhone";
const char* password = "1234567890";

ESP8266WebServer server(80);

#define LED_RED    5 // D1
#define LED_YELLOW 4 // D2
#define LED_GREEN  0 // D3

bool redState = false;
bool yellowState = false;
bool greenState = false;



void handleStatus() {
  
  String statusMessage = "";
  statusMessage += "Red LED: ";
  statusMessage += (redState ? "ON\n" : "OFF\n");

  statusMessage += "Yellow LED: ";
  statusMessage += (yellowState ? "ON\n" : "OFF\n");

  statusMessage += "Green LED: ";
  statusMessage += (greenState ? "ON\n" : "OFF\n");

  
  server.send(200, "text/plain", statusMessage);
}


void turnOffAllLEDs() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  // Also update our memory
  redState = false;
  yellowState = false;
  greenState = false;
}

void handleRedOn() {
  turnOffAllLEDs(); // This turns off all LEDs and sets states to false
  digitalWrite(LED_RED, HIGH);
  redState = true; // Now we remember that red is on
  server.send(200, "text/plain", "Red LED ON");
}

void handleYellowOn() {
  turnOffAllLEDs();
  digitalWrite(LED_YELLOW, HIGH);
  yellowState = true; // Remember yellow is on
  server.send(200, "text/plain", "Yellow LED ON");
}

void handleGreenOn() {
  turnOffAllLEDs();
  digitalWrite(LED_GREEN, HIGH);
  greenState = true;
  server.send(200, "text/plain", "Green LED ON");
}

void handleRedYellowOn() {
  turnOffAllLEDs();
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YELLOW, HIGH);
  redState = true;
  yellowState = true;
  server.send(200, "text/plain", "Red and Yellow LEDs ON");
}


void setup() {
  Serial.begin(115200);

  // Configure LED pins as outputs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  
  turnOffAllLEDs();

  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);https://aax-eu.amazon.de/x/c/JMKMMGx6dxUGeiPMJ-hkETEAAAGYeYfJgQMAAAH2AQBvbm9fdHhuX2JpZDIgICBvbm9fdHhuX2ltcDIgICC-CzJC/clv1_CEuOPUxokZA0iHrVReAy3CjwWCtVa4hrlccY82KlztlQ8X8G7gD8Ev018HHz9hvVjq0yzpNb3XPFfU0cAmcAGE98KCuxDpHdKnNTRxFuTQWOJbxZhEfB8IkGXCQaUuW6XJfef1D8rsFSE0M9llvwdksJOldODd93Q196UuYlQRaY37qDjF4oXlv5OpjsdqwyCjQHbdXAhZRSWWhBJNwAffQdjs-hn4wsEjvWNPQG9gUahJtJn6j8Z0wG3nKH1EB2AHnpPv3v4jxS3xU8E-ErSSiJI16ZjAz9B7yl_bPrUYAZJ0SW56eH2BSUewSbSdGvndE5981OYuzmkMHiMvnvA8dF9dxIfB8PlI8C-9FHE6Fj0W5fDGi7yyidpLYGWBmaYxJzqXqqjEQnhinFOJGQaFdhRZzXuNdUWekbGEVr5yhxKPVak1QCImRE_6VGXQoMDaeUao3l4duAHS8cbA2SvJ4cQ2qPjVyBTCVtcaIio9aXLnR4zbqc0DvINkZhLIqIqq5T-xBnRZIJghejjVCK8hLhRShqbVAiLgGHUh_TOpLaaiKsFCNxy3wjFWbfVDjZYNkugPRbaweyr7dnhuUDDFLmKBs5yg9M_eAflIO3nGQmkZGF-IdPQEXztzW_YPWcNUlke-0Heytc3vdjNpsWijci-oPbHQpZeF8eiul-i7w6FxMEQweypFMnpQLhcuR90zQk8Upqxe0V3ewSHknrI34y_pLfF_vQ35vLBkwYECDVpgv5HOxSyjx-7tUHVdm1hrxtPB3Xrmvd6BjoNGD1LBZYthrlM2tm9t5jXf8VYRaXx0UgCe5-lxdu85-Uaz-hd-ecTQ5o2zeXmdFeXtBMs7W9hkkmuq2GSueMrMO8iE-A03vB7UstyTzgiW-7mmbKo9kPqt13vxvuAcEEXPodC6uIwMOV0AtsbHscBzfquRnj0TN5M3IkRE93WyzY11-VsxalRPDm-4WyquHr3Wm7UKluLdeSVqTBoliNWwFgM-I2bgtZcVhSab_4zgHHB20QDCOVx6J2_TwYZ7gY95Gx6RhNlypELrW_nXYj6IZitBEAeF61eK6wB225S7JQPNRgaVO_Xp3nABYrK62fYZaSuv7PSgfx2oRzcMwIODg2I7unVS6TLMc0gmIfX4CDouvhg5NAecjAhwI4D9d4nnwYalQfZcDBAnjvL7segLLe94WguACR_VeoyZ0VhTdue9chOkemJ1bSwV69bXo4lnuFGeLA6c5xga5wygis1Zp2EVvTCFMHU2DQ30OthTMsA6DJSJIlovuYf0j5a6ZpYaUKpUR4hqhPrZOx7jCtpmCVZ933X_tgE_zB9P0CrAmTqpsIKK85dyyB0kiTsN8mZ3Ij0ovKsvkO6HV7Vv8JMsRwuLouymCdX022m9CrBFyXbqlQSTHLZ0-3ewL6RRsuada0VNu3jzmrJ2VUwJMMy_nLoFR_PTNJ2Y1GJ8YMEAj5FSyZqX8iAUX-t4O7pzzlFzj7bVn28Tvtee8A_rJx9uEht1wLiw_9H266OwBDx4kkucuJ11ThTHNFYvFYEIPVROw4OGzAgsecPFm4PlLaHJoHseCSz9yd3pmUU6lDDuQykvZjJ-nuBU_K2aTNaebfCWJRQgRb5sXW4YEZhKOX-QvYzvuUSkjMGxSom01oqmxWfYOPKSzhL0_WwpoUdma8vABW_ag8HyGwUE0qEZRym_IRRPj3F4QvlJ_sdycW4_WWv_6bpfQkfJa74D92mnioiptPJAjAkywEknqmk9pPOSO6nFW-qenX-cQNSJd36UmVMf8ai6o59VOCgZNRKthZRdkT_FM3HfvFwwvye-35AA3495ywN8Sk74Id5sErYserrOZe5yxgYvd0Fqk1kfHzPkv-MYPLg75oQNuTRsdCUiJBriRSv_vtCJmdhEYJUJW75vEBlf_pfC5_i8Ss8yRFSy73GcudkQ9Q4-oNaOTQvL4Br0c2JRFXxrb7VqIL4wilMgJJpKXiRVsCF-236bGyDZzDGBrxv_AaeWShZYY_LDWISvupW4T_rj81yAlIEnSHIfGQsn7VP2KYmAagQv4Oxi9ONkG4ToBxAoGkWbNqIN4nAONc1NoXcAdMbPBxxng_BdbOv3oBakNhFsW-O2aRGyH4O2xYSY2vyc_VPb1b0Q4TEfzmCdZ1Um-LMLMshpJvqlznSDQrnWFwbj4eRSefKBju7TXON7mG73Yepg3gC5ZZQLIRFabFTvjPAOSHTk_QKAlbwoelIbDRiqjLpKQMc_A26t61xNN-vUJ5z-HRC25_4Mg8RKQhaRzG5oD2OeHGuqdJO0m7a5KKlVfcujp7II8KdpP7Up3r1A9JfrlJYOlQTFBpy7qw4paOMm4C8Xsp/https://www.amazon.de/gp/aw/d/B00EWHK714/?_encoding=UTF8&pd_rd_plhdr=t&aaxitk=e71068bdb928185c901d1d4757af540b&hsa_cr_id=1056878890202&qid=1754385598&sr=1-1-e0fa1fdd-d857-4087-adda-5bd576b25987&ref_=sbx_be_s_sparkle_mcd_asin_0_img&pd_rd_w=TnOJG&content-id=amzn1.sym.9e72596d-52d6-4b34-9f08-1195d4ef0692%3Aamzn1.sym.9e72596d-52d6-4b34-9f08-1195d4ef0692&pf_rd_p=9e72596d-52d6-4b34-9f08-1195d4ef0692&pf_rd_r=5G3MSA9FPX3CPKDX84KG&pd_rd_wg=zYUVY&pd_rd_r=5d8367e1-afea-4efe-93b7-88745d7ba374
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/redon", handleRedOn);
  server.on("/yellowon", handleYellowOn);
  server.on("/greenon", handleGreenOn);
  server.on("/status", handleStatus);
  server.on("/redyellow", handleRedYellowOn);

  server.begin();
}


void loop() {
  server.handleClient();
}
