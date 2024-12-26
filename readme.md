# Horloge Numérique avec Matrices LED et Synchronisation NTP

## Description

Ce projet consiste en la création d'une horloge numérique utilisant des matrices LED contrôlées par un microcontrôleur ESP8266. L'horloge se connecte à un réseau Wi-Fi pour obtenir l'heure précise via le protocole NTP (Network Time Protocol). L'heure est ensuite affichée sur les matrices LED. L'horloge prend en compte le décalage horaire ainsi que le changement d'heure d'été et d'hiver. Pour faciliter la configuration du Wi-Fi, le projet utilise la bibliothèque WiFiManager, qui permet de configurer le réseau Wi-Fi via une interface web accessible depuis un smartphone ou un ordinateur.

## Requirements

### Matériel

- Microcontrôleur ESP8266
- Matrices LED (4 matrices de 8x8)
- Alimentation 5V et GND pour les matrices LED

### Logiciel

- Bibliothèques Arduino :
  - MD_Parola
  - MD_MAX72XX
  - SPI
  - WiFiManager
  - NTPClient
  - WiFiUdp

### Branchements

- Connectez la broche DATA des matrices LED à la broche D7 (GPIO 13) de l'ESP8266.
- Connectez la broche CLK des matrices LED à la broche D5 (GPIO 14) de l'ESP8266.
- Connectez la broche CS des matrices LED à la broche D8 (GPIO 15) de l'ESP8266.
- Assurez-vous que les matrices LED sont correctement alimentées avec 5V et GND.

## Fonctionnalités

- Affichage de l'heure actuelle sur les matrices LED.
- Synchronisation de l'heure via NTP.
- Prise en compte du décalage horaire et du changement d'heure d'été et d'hiver.
- Configuration Wi-Fi via une interface web.

## Installation

1. **Télécharger les bibliothèques nécessaires** :
   - Ouvrez l'IDE Arduino.
   - Allez dans `Croquis` > `Inclure une bibliothèque` > `Gérer les bibliothèques`.
   - Recherchez et installez les bibliothèques suivantes :
     - MD_Parola
     - MD_MAX72XX
     - WiFiManager
     - NTPClient

2. **Configurer le projet** :
   - Ouvrez le fichier `.ino` du projet dans l'IDE Arduino.
   - Assurez-vous que les broches de connexion (DATA_PIN, CLK_PIN, CS_PIN) correspondent à votre configuration matérielle.

3. **Téléverser le code** :
   - Sélectionnez le bon port et la bonne carte (ESP8266) dans l'IDE Arduino.
   - Téléversez le code sur votre ESP8266.

4. **Configurer le Wi-Fi** :
   - Après le téléversement, l'ESP8266 créera un point d'accès Wi-Fi nommé `Horloge_Config`.
   - Connectez-vous à ce réseau Wi-Fi avec le mot de passe `password`.
   - Ouvrez un navigateur web et accédez à l'adresse IP du point d'accès (généralement `192.168.4.1`).
   - Suivez les instructions pour configurer votre réseau Wi-Fi domestique.

## Utilisation

Une fois configuré, l'ESP8266 se connectera automatiquement à votre réseau Wi-Fi et synchronisera l'heure via NTP. L'heure actuelle sera affichée sur les matrices LED, avec prise en compte du décalage horaire et du changement d'heure d'été et d'hiver.

## Auteur

Ce projet a été réalisé par [Julien ROY]

## Remerciements

Merci aux contributeurs des bibliothèques utilisées dans ce projet.
