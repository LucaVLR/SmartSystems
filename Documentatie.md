# Eind documentatie SmartCar
### Luca Van Laer
### 2ITIOT

# Huidige situatie en analyse:
### Bekijk de analyse hier:
[Analyse](./Analyse.md)


# Algemene werking

Men bestuurt de auto met een NodeRED dashboard. Op dit dashboard kan men kiezen of manueel of automatisch gereden wordt.

Indien men manueel wilt rijden, kan men de knoppen gebruiken om de auto in allerhande richtingen te laten rijden. In automatisch mode zal de auto automatisch lijnen volgen en bij een barriere wachten. Men kan de auto ook in standby zetten in eender welke mode.

We beginnen met het bespreken van het dashboard zelf, daarna zullen we verder ingaan in de werking van de twee Arduino programma's.

# Dashboard

![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/dashboard.png?raw=true)

Op het dashboard zien we 3 onderdelen:
 - De configuratie voor automatische modus
 - De configuratie voor manuele modus
 - De keuze tussen manueel en automatisch

We kunnen, zoals vooraf besproken, de auto in standby zetten (motoren uit) via de standby knop.
Met een snelheid selectie kan men kiezen hoe snel de auto rijd in manuele modus.
Via 8 richtingsknoppen kan men de auto laten rijden.


# ATSense

Om automatisch te kunnen rijden is er allerhande sensor data nodig. Deze data wordt opgehaald uit 3 sensoren:
 - Ultrasone afstandsensor
 - IR afstandsensor
 - IR lijnvolgersensor array van 8

Wanneer het moederbord deze data nodig heeft, wordt via I2C een request gestuurd naar het dochterbord. Dit is een klein bordje gebaseerd op een ATMega328P microcontroller. Het dochterbord leest de sensordata in en structureerd dit in een array van 3 bytes (via shift operaties kan elke lijnvolger 1 bit opnemen uit een byte). De sensordata bytes worden daarna via I2C doorgestuurd naar het moederbord. Op basis van deze sensordata kan het moederbord beslissingen maken.

Het Arduino programma voor dit sensor bordje is [hier](./ATSense/ATSense.ino) te vinden.
Voor de IR sensoren worden standaard analoog en digitale pinoperaties gebruikt. Om het inlezen van de ultrasone sensor makkelijk te maken wordt gebruik gemaakt van de 'NewPing' bibliotheek. Deze bibliotheek doet al het werk van een puls te sturen en de responsetijd te meten voor ons en zet de data om in centimeter.


# Manueel rijden


# Automatisch rijden


# Struikelblokken

