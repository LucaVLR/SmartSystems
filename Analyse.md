# Analyse Smart Systems Robotwagen
### Luca Van Laer
### 2ITIOT

# Probleemstelling

Ontwerp van een schakelingen om een robotwagentje aan te sturen. Dit is opgedeeld in twee schakelingen. Een stuurschakeling PCB met een ESP32 en een trackermodule PCB met een ATMega en sensoren om de sturing te kunnen realiseren.


# As-Is situatie

### Specificaties / Situation As Is:

- Voltage Regulator LM7805 through hole
- Motor driver SN754410 through hole + 2x 2 motor pins: 1A, 1B, 2A, 2B
- 4x LED's: 1x rood, 2x geel, 1x groen
- LCD scherm module, I²C pins op PCB: GND, SDA, SCL, 3V3
- Ultrasoon module aansluiting: 5V, TRIG, ECHO, GND
- 3 voeding pins: 3V3, 5V, GND
- 2 pin aansluiting: 3V3, PQ_L
- 2x 2 GPIO spare pins


# Situation To Be

### Goals:
- Sensoren toepassen in een praktische schakeling.
- Voldoende materiaal genereren voor gebruik in het eerste jaar.
- Automatische besturing voorzien.


## Schakelingen

### Stuurschakeling: 
<ul>
  <li>2x UART connectoren</li>
  <li>3x I²C connectoren</li>
  <li>Voltage regulator LDL1117 SMD</li>
  <ul>
      <li>5V</li>
      <li>3V3</li> 
    
  </ul>
  <li>OLED-scherm I²C</li>
  <li>SMD Motor driver TC78H621FNG</li>
  <li>Reverse Polarity Protection</li>
  <li>ESP32 WROVER Module</li>
  <li>Batterij aansluiting</li>
</ul>

### Sensorschakeling: 

<ul>
      <li>Ultrasoon + IR afstandssensoren</li>
      <li>8 channel IR Linetracker</li>
  </ul>
  
### Sturing Goals:

<ul>
 <li>Manueel of automatisch rijden</li>
 <li>Hindernissen vermijden</li>
</ul>

# Hardware Analyse

## Blokschema

![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/blokschema_ss.drawio.png?raw=true)


## Componentenlijst:
### Sturingschakeling:

**Microcontroller:**

**ESP32-WROVER Module:**
- ESP32 WROVER

Winkel : https://www.bol.com/be/nl/p/esp-wroom-32-ontwikkelbord/9200000114634593/?Referrer=ADVNLGOO002013-G-137016892532-S-1080766724149-9200000114634593&gclid=CjwKCAjwoduRBhA4EiwACL5RP3gmvcCjgniShMIKJF6Tj-c8ILHCnZigB3Wc8GkKKFBQUkc2TnLEZBoC6nkQAvD_BwE

**Motor Driver**

**TC78H621FNG(O,EL)**


Winkel: https://be.farnell.com/toshiba/tc78h621fng-o-el/motor-driver-ic-h-bridge-tssop/dp/3869999?st=motordriver

**Display**

**Seeed Studio Grove OLED Display**

- 0.96" OLED Display 128x64
- Vcc = 3.3 - 5 V
- Icc = 9 - 15 mA
- Controller: SSD1315
- Comm protocol: I²C or SPI
- Connector: JST 4P
- Eenheidsprijs: €4,60 - €7,00

Winkel: https://www.tinytronics.nl/shop/nl/displays/oled/0.96-inch-oled-display-128*64-pixels-wit

**Voeding**

**Conrad Energy LiPo accupack**

- Vnomonaal = 7.4 V
- Inominaal = 1200 mAh
- Aantal cellen: 2
- Belastbaarheid: 20 C
- Aansluiting: XT60, XH-balancer
- Afmetingen: 112 x 35 x 19 mm
-Eenheidsprijs: €16,49

Winkel: https://www.conrad.be/nl/p/conrad-energy-lipo-accupack-7-4-v-2400-mah-aantal-cellen-2-20-c-softcase-xt60-1344133.html?t=1&utm_source=google&utm_medium=surfaces&utm_term=1344133&utm_content=free-google-shopping-clicks&utm_campaign=shopping-feed&vat=true&gclid=CjwKCAjwxOCRBhA8EiwA0X8hi6Dpvaew0u-kTnIyrUmKE2RRHzkksSaw41QoJ36AmjOCY1n-dP7VnRoC240QAvD_BwE&gclsrc=aw.ds&tid=13894944235_122657379817_pla-301443522443_pla-1344133&WT.srch=1


**Voltage Regulators**

**LDL1117S50R**

- Voltage Regulator 5 V
- Package: SOT223 SMD
- Voutput = 5 V
- Vinput = 2.5 - 18 V
- Ioutput = 1.2 A
- Eenheidsprijs: €0,56

**Reverse Polarity Protection**

**SSM3J145TU**

- N-channel MOSFET
- Package: TODO
- Vdsmax = TODO
- Idmax = TODO
- Rds(on) = TODO
- Vgs(th) = TODO
- Pd = TODO
- Eenheidsprijs: TODO

Winkel: TODO

### Sensorschakeling

**Microcontroller**
- ATmega328p 

**Sensoren**

**MJKDZ MIR-3.0Y**

- 8x IR Line Tracking Module
- Vcc = 3 - 5 V
- Bereik (max. bij 5V) = 40 mm
- Afmetingen LxB: 17 x 67 mm
- Eenheidsprijs: €6,00

Winkel: https://www.tinytronics.nl/shop/nl/sensoren/optisch/infrarood/8x-ir-lijn-tracking-module-40mm-bereik

**Sharp GP2Y0A21YK0F**

- IR-afstandssensor
- Vcc = 4.5 - 5.5 V
- Ityp = 30 mA
- Bereik: 50 - 800 mm
- Afmetingen: 29.5 x 13 x 13.5 mm
- Eenheidsprijs: €5,50 - 12,06

Winkel: https://www.tinytronics.nl/shop/nl/sensoren/afstand/sharp-optische-afstandsensor-gp2y0a21yk0f

**HC-SR04**

- Ultrasoon afstandssensor
- Vcc = 5 V
- Icc = <2 - 15 mA
- Bereik: 20 - 4500 mm
- Resolutie: 3 mm
- Sensor hoek: <15°
- Ultrasone freq.: 40 kHz
- Eenheidsprijs: €3,00 - 7,21

Winkel: https://www.tinytronics.nl/shop/nl/sensoren/afstand/ultrasonische-sensor-hc-sr04

## Elektrisch Schema

**ESP32**

![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/schema_sturing.jpg?raw=true)

**ATmega328**

![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/schema_sensorbord.jpg?raw=true)


## PCB Ontwerp

**ESP32**

![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/pcb_sturing.jpg?raw=true)


**ATmega328**

![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/pcb_sensorbord.jpg?raw=true)

# Software Analyse

## Data Flow Analyse

### Stuurschakeling

|Component|Input|Output|
|---------|-----|------|
|ESP-Wrover|Motor config data - Sensordata|-|
|OLED Display|I²C grafische data|-|

### Sensorschakeling

|Component|Input|Output|
|---------|-----|------|
|ATMega| Line Tracker data D1-D8 Ultrasoon sensor echo IR-afstandssensor analoog|Sensordata I²C Line Tracker aan/uit, Afstandssensor data |
|Line Tracker|-|Data van 8 IR linetrack sensoren|
|Ultrasoon Sensor|Trigger puls|Echo puls|
|IR Afstandssensor|-|Afstand analoog|

### State Diagram

![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/statediagram_ss.png?raw=true)

### Flowchart

![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/smartcar_flow.png?raw=true)

## Planning

### Epics

1. Analyse
2. PCB ontwerp
3. Software ontwikkeling
4. Hardware samenstelling
5. Software implementatie
6. Test

## Stories

### 1. Analyse

**Analyse maken**


**Acceptance Criteria:**

- Probleemstelling in 2 tot 5 lijnen
- Mindmap
- Hardware analyse
- Hardware blokdiaram
- Specificatie tabel
- Argumentatie en alternatieven tabel
- Software analyse
- Data In -en Outputs
- State diagram
- Flowchart
- Release plan

### 2.PCB ontwerp

**Sturingsschakeling**

**Acceptance Criteria:**

- 2x UART connectoren
- 3x I²C connectoren
- Voltage regulator 5V & 3.3V
- Polariteitsbeveiliging
- SMD Motor driver
- OLED-scherm met I²C-sturing op PCB
- Batterij aansluiting (GND, VCC)
- Drill holes voor bevestiging van de PCB op het wagentje.

**Sensor schakeling**

**Acceptance Criteria:**

- Ultrasoon
- IR afstandssensoren
- 8 channel IR Line tracker

### 3.Software ontwikkeling

- Manuele bediening
- Automatisch rijden
- Patroon volgen

### 4.Hardware samenstelling

- Sturings PCB solderen
- Sensor PCB solderen
- Robotwagen samenstellen

### 5.Software implementatie

- ESP32 programmeren
- ATmega328 programmeren

### 6.Test

- Componenten
- Data in & out
- Modussen 

### Sprints
- Analyse 
- PCB ontwerp
- Afwezig internationaal week Brugge
- Software ontwikkeling
- Hardware samenstelling & Software implementatie & Test
