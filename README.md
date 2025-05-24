# I2C_LCD_Display_PCF8574

Ce projet regroupe **trois implémentations différentes** pour afficher du texte sur un écran LCD 16x2 via une interface I2C avec un expandeur PCF8574. L’objectif est d’explorer plusieurs manières de piloter un écran LCD sans utiliser de bibliothèques spécialisées comme `LiquidCrystal_I2C`.

---

## 📦 Contenu du projet

### 1. `LcdDisplay_Class.ino`
- Implémentation orientée objet avec une classe `MonAfficheurLcd`.
- Encapsulation complète des opérations d’écriture, initialisation et communication.
- Permet de réutiliser l'afficheur LCD facilement dans d'autres projets.

### 2. `LcdDisplay_Functions1.ino`
- Version procédurale sans classe, avec des fonctions globales.
- Affiche simplement le mot **"Bonjour"** sur la première ligne de l'écran.
- Structure claire avec séparation des fonctions privées/publiques.

### 3. `LcdDisplay_Functions2.ino`
- Extension de la version précédente avec gestion des deux lignes de texte.
- Utilise `EcrireSurLaLigne1()` et `EcrireSurLaLigne2()` pour afficher :
  ```
  GOD DIIIID
  A ANOTHER ONE
  ```

---

## 🧰 Matériel requis

- Carte Arduino (Uno, Nano, Mega…)
- Écran LCD 16x2 avec module I2C (PCF8574)
- Câbles Dupont
- Alimentation 5V
- Adresse I2C par défaut : `0x27`

---

## 🛠 Fonctionnement général

### Protocole

- Communication via I2C (`Wire.h`)
- Mode 4 bits (envoi des nibbles haut puis bas)
- Octet construit comme suit :  
  `Octet = 16*data + 8*r + 4*e + 2*rw + rs`

### Contrôle du LCD

| Bit  | Signification      |
|------|--------------------|
| RS   | Register Select    |
| RW   | Read/Write         |
| E    | Enable             |
| Data | Données 4 bits     |
| R    | Rétroéclairage     |

---

## 💡 Initialisation du LCD

Voici les étapes classiques utilisées dans les trois versions :

```cpp
data = 3; EcrireDataSurLCD(); delay(5);
data = 3; EcrireDataSurLCD(); 
data = 3; EcrireDataSurLCD(); 
data = 2; EcrireDataSurLCD();  // passage en mode 4 bits

data = 2; EcrireDataSurLCD(); 
data = 8; EcrireDataSurLCD();  // fonction set

data = 0; EcrireDataSurLCD(); 
data = 0xC; EcrireDataSurLCD();  // display ON

data = 0; EcrireDataSurLCD(); 
data = 6; EcrireDataSurLCD();  // entry mode

data = 0; EcrireDataSurLCD(); 
data = 1; EcrireDataSurLCD();  // clear display
```

---

## 📋 Fonctions principales

### `EcrireOctetSurLcd(unsigned char a)`
Découpe l'octet en deux nibbles et les transmet au LCD.

### `EcrireDataSurLCD()`
Envoie les données vers le LCD en activant le bit `E`.

### `EcrireSurLaLigne1(char* texte)`  
Affiche une chaîne de 16 caractères sur la première ligne.

### `EcrireSurLaLigne2(char* texte)`  
Affiche une chaîne de 16 caractères sur la deuxième ligne.

---

## 🖥️ Affichage attendu

Selon le fichier choisi :

- **Class version (`LcdDisplay_Class.ino`)** :
  ```
  IAM
  THEROOT
  ```

- **Function version 1 (`LcdDisplay_Functions1.ino`)** :
  ```
  Bonjour
  ```

- **Function version 2 (`LcdDisplay_Functions2.ino`)** :
  ```
  GOD DIIIID
  A ANOTHER ONE
  ```

---

## 🎯 Objectif pédagogique

- Comprendre comment fonctionne un écran LCD 4 bits sans bibliothèque
- Maîtriser les échanges I2C avec PCF8574
- Apprendre la différence entre approche procédurale et orientée objet

---

## ✅ À faire

- Ajouter le support pour le curseur
- Créer un scrolling automatique
- Permettre l'affichage dynamique (valeurs de capteurs, etc.)

---

## 👨‍💻 Auteur

Projet développé par **IAMTHEROOTx**  
Open-source – modifiable librement à des fins pédagogiques ou personnelles.

---

## 📝 Licence

Ce projet est proposé sous licence MIT. Vous pouvez l’utiliser, le modifier et le redistribuer librement.

