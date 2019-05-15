# InDoorDeviceLocalization

DOEL: 
Het doel van dit project is om een ‘proof of concept’ te maken voor indoor device localisation. Binnen werkt een GPS niet goed, als oplossing hiervoor kunnen wifi-acces points (kortweg AP) gebruikt worden. 
In de campus van Brugge hangen er overal acces-points. Deze kunnen gebruikt worden om je locatie binnen het gebouw te bepalen. Dit kan aan de hand van RSSI (Received Signal Strength Indicator). Hoe sterker een signaal is, hoe dichter je bij een acces point staat.

IMPLEMENTATIE:
Om te beginnen is er een scanning geweest van de bestaande acces points, om hun locatie en MAC-adressen te bekomen. Dit is opgeslagen geweest in een array. We hebben ervoor gekozen om twee bytes naar het TTN te sturen. De eerste byte geeft aan op welk verdiep men zit, de tweede geeft aan om welke AP op dat verdiep het gaat. Aan de hand van deze herkenning gaat er een punt op de map verschijnen welke overeenkomt met de MAC-adres.
