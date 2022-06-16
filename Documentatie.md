# Eind documentatie SmartCar
### Luca Van Laer
### 2ITIOT

# Huidige situatie en analyse:
### Bekijk de analyse hier:
[Analyse](./Analyse.md)


# Algemene werking

Men bestuurt de auto met een NodeRED dashboard. Op dit dashboard kan men kiezen of manueel of automatisch gereden wordt.

Indien men manueel wilt rijden, kan men de knoppen gebruiken om de auto in allerhande richtingen te laten rijden. In automatisch mode zal de auto automatisch lijnen volgen en bij een barriere wachten.

We beginnen met het bespreken van het dashboard zelf, daarna zullen we verder ingaan in de werking van de twee Arduino programma's.

# Dashboard

![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/dashboard.png?raw=true)

Op het dashboard zien we 2 onderdelen:
 - De configuratie voor manuele modus
 - De keuze tussen manueel en automatisch

Met een snelheid selectie kan men kiezen hoe snel de auto rijd in manuele modus. Via 8 richtingsknoppen kan men de auto laten rijden.
In automatische mode moet er niks aangepast of geconfigureerd worden door de gebruiker.


# ATSense

![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/schema_sensorbord.jpg?raw=true)

Om automatisch te kunnen rijden is er allerhande sensor data nodig. Deze data wordt opgehaald uit 3 sensoren:
 - Ultrasone afstandsensor
 - IR afstandsensor
 - IR lijnvolgersensor array van 8

Wanneer het moederbord deze data nodig heeft, wordt via I2C een request gestuurd naar het dochterbord. Dit is een klein bordje gebaseerd op een ATMega328P microcontroller. Het dochterbord leest de sensordata in en structureerd dit in een array van 3 bytes (via shift operaties kan elke lijnvolger 1 bit opnemen uit een byte). De sensordata bytes worden daarna via I2C doorgestuurd naar het moederbord. Op basis van deze sensordata kan het moederbord beslissingen maken.

Het Arduino programma voor dit sensor bordje is [hier](./ATSense/ATSense.ino) te vinden.
Voor de IR sensoren worden standaard analoog en digitale pinoperaties gebruikt. Om het inlezen van de ultrasone sensor makkelijk te maken wordt gebruik gemaakt van de 'NewPing' bibliotheek. Deze bibliotheek doet al het werk van een puls te sturen en de responsetijd te meten voor ons en zet de data om in centimeter.


# SmartCarDrive
Programma is [hier](./SmartCarDrive/SmartCarDrive.ino) te vinden.
## Manueel rijden

Wanneer we manueel rijden, blijven we telkens de voorafgaande instructie uitvoeren tot er een nieuwe aankomt. We slagen dus de richting en snelheid op om ze te blijven gebruiken. Wanneer een nieuw MQTT bericht binnenkomt, overwriten we simpelweg deze data.

Afhanged van de richting dat we in willen rijden, moeten de twee motoren verschillend van elkaar draaien. Om bijvoorbeeld naar voor te rijden en tegelijk links te draaien, moet de linkermotor trager rijden dan de rechtermotor. Een simpele functie bespaard ons heel wat regels code en maakt het aansturen van de motoren simpel en leesbaar. Aangezien we geen sensoren gebruiken tijdens dit proces, is er geen nood om rekening te houden met obstakels.


## Automatisch rijden

Het algoritme om automatisch te rijden is redelijk simpel te vatten met volgende flowchart.
![image](https://github.com/LucaVLR/SmartSystems/blob/main/Afbeeldingen/automatisch_rijden_algoritme.png?raw=true)

Met de afstandsensoren kunnen we detecteren of een obstakel te dicht bij is. Indien dit waar is, kunnen we niet verder rijden en zetten we de motoren stil.

Indien dit niet is, kunnen we de status van de lijnvolgers bekijken. Met een simpele switch statement kunnen we de 3 condities opsplitsen:
 - Te ver naar links
 - In het midden
 - Te ver naar rechts

Afhangend van de status moeten we gewoon recht vooruit rijden of wat keren om op de lijn te blijven.
