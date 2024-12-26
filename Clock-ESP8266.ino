/**
 * Projet : Horloge Numérique avec Matrices LED et Synchronisation NTP
 *
 * Description :
 * Ce projet consiste en la création d'une horloge numérique utilisant des matrices LED contrôlées par un microcontrôleur ESP8266.
 * L'horloge se connecte à un réseau Wi-Fi pour obtenir l'heure précise via le protocole NTP (Network Time Protocol). L'heure est ensuite affichée sur les matrices LED.
 * L'horloge prend en compte le décalage horaire ainsi que le changement d'heure d'été et d'hiver. Pour faciliter la configuration du Wi-Fi, le projet utilise la bibliothèque WiFiManager,
 * qui permet de configurer le réseau Wi-Fi via une interface web accessible depuis un smartphone ou un ordinateur.
 *
 * Requirements :
 * - Microcontrôleur ESP8266
 * - Matrices LED (4 matrices de 8x8)
 * - Bibliothèques : MD_Parola, MD_MAX72XX, SPI, WiFiManager, NTPClient, WiFiUdp
 * - Connexions :
 *   - DATA_PIN (D7) connecté à la broche DATA des matrices LED
 *   - CLK_PIN (D5) connecté à la broche CLK des matrices LED
 *   - CS_PIN (D8) connecté à la broche CS des matrices LED
 *   - Alimentation 5V et GND pour les matrices LED
 *
 * Branchements :
 * - Connectez la broche DATA des matrices LED à la broche D7 de l'ESP8266.
 * - Connectez la broche CLK des matrices LED à la broche D5 de l'ESP8266.
 * - Connectez la broche CS des matrices LED à la broche D8 de l'ESP8266.
 * - Assurez-vous que les matrices LED sont correctement alimentées avec 5V et GND.
 *
 * Fonctionnalités :
 * - Affichage de l'heure actuelle sur les matrices LED.
 * - Synchronisation de l'heure via NTP.
 * - Prise en compte du décalage horaire et du changement d'heure d'été et d'hiver.
 * - Configuration Wi-Fi via une interface web.
 */

#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>
#include <WiFiManager.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define DATA_PIN 13
#define CLK_PIN 14
#define CS_PIN 15

#define NUM_MATRICES 4

MD_Parola parola = MD_Parola(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, NUM_MATRICES);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "fr.pool.ntp.org", 0);

void setup() {
  parola.begin();
  parola.setIntensity(0);
  parola.setTextAlignment(PA_CENTER);

  WiFiManager wifiManager;
  wifiManager.setTimeout(180);
  if (!wifiManager.autoConnect("Horloge_Config", "YOURPASSWORD")) {
    ESP.restart();
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  int rawHours = timeClient.getHours();
  int rawMinutes = timeClient.getMinutes();

  int offset = 3600;
  if (isDaylightSavingTime(timeClient.getEpochTime())) {
    offset += 3600;
  }

  int localHours = (rawHours + offset / 3600) % 24;

  char timeStr[6];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d", localHours, rawMinutes);

  parola.print(timeStr);
  delay(1000);
}

bool isDaylightSavingTime(unsigned long epochTime) {
  time_t t = epochTime;
  struct tm *ptm = gmtime(&t);

  if (ptm->tm_mon > 2 && ptm->tm_mon < 9) {
    return true;
  }

  if (ptm->tm_mon == 2) { // Mars
    return (ptm->tm_mday - ptm->tm_wday >= 25);
  }
  if (ptm->tm_mon == 9) { // Octobre
    return (ptm->tm_mday - ptm->tm_wday >= 25);
  }
  return false;
}
