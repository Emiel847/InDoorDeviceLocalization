#define NUMBER_OF_MACS 53


//location of AP 
/*
x[0]: level
x[1],X[2]: AP nr 
*/
static const char location[NUMBER_OF_MACS][4] =
{
    "000",  // 40:01:7a:80:7f:13 -> onderwijslab bouwkunde, muur kant station
    "001",  // 40:01:7a:12:e0:74 -> onderzoekslab recycon
    "002",  // 00:a7:42:8e:8b:33 -> onderzoekslab omgevingstechnieken
    "003",  // f8:0b:cb:3d:87:63 -> opslag bulk en puin
    "004",  // 40:01:7a:12:ec:d3 -> naast toiletten inkom, boven plafond
    "005",  // 00:2c:c8:f1:36:d2 -> inkomhal, rechts van trappengang
    "006",  // 00:2c:c8:ep:23:79 -> inkomhal, links van trappengang
    "100",  // 40:01:7a:14:08:03 -> AP landschapskantoor 1e, midden vergaderzalen
    "101",  // 40:01:7a:14:05:33 -> onderwijslab mechanische structuren en vibro akoestiek
    "102",  // 40:01:7a:80:78:53 -> onderwijslab aandrijf en energietechnieken
    "103",  // 40:01:7a:12:c1:53 -> bergruimte machines en vermogenapp.
    "104",  // 40:01:7a:80:56:01 -> onderwijslab energie en automatisering, kant gang
    "105",  // 40:01:7a:80:56:01 -> onderwijslab mechanische vormgevingstechnieken, kant liften
    "106",  // 18:80:90:c6:a1:c3 -> naast wc's, tegen plafond
    "200",  // 40:01:7a:80:7e:7c -> landschapsbureau 2e, hoek printernis
    "201",  // 40:01:7a:12:e8:83 -> onderwijslab mechanische meettechnieken
    "202",  // 40:01:7a:80:78:03 -> onderwijslab ICT, midden muur LCD
    "203",  // 18:80:90:c6:a8:03 -> onderwijslab elektronica, kant tussendeur
    "204",  // 40:01:7a:1c:09:23 -> onderwijslab embedded software, rechtsboven doorgang IT lokaal
    "205",  // f8:0b:cb:3d:80:63 -> AP bovenop datakast geplaatst, rechtstreeks in poort
    "300",  // 00:2c:c8:8b:e2:53 -> aula, kant foyer
    "301",  // 00:2c:c8:e9:3b:21 -> aula, kant raam
    "302",  // 00:2c:c8:6a:ad:c1 -> aula, kant projectiescherm
    "303",  // 40:01:7a:14:0f:c3 -> foyer aula, boven plafond zitbank
    "304",  // 00:2c:c8:ed:dc:23 -> AP 1 cafetaria, kant zitbank tov keuken
    "305",  // 00:2c:c8:19:24:d3 -> AP 2 cafetaria, kant keuken
    "306",  // 00:2c:c8:6a:8f:03 -> AP 3 cafetaria, doorgang buitenterras
    "307",  // 2c:5a:0f:09:a9:a3 -> AP 4 cafetaria, kant liften
    "308",  // 00:a7:42:8e:88:c3 -> gang 3e, kant parking
    "400",  // 40:01:7a:14:04:f3 -> grote pc klas achter boven
    "401",  // 40:01:7a:13:fc:03 -> kleine pc klas vooraan boven bord
    "402",  // 18:80:90:dc:c8:23 -> klas medium 1
    "403",  // 40:01:7a:1c:08:23 -> klas small 1
    "404",  // 40:01:7a:14:10:33 -> onderzoekslokaal kine
    "405",  // 00:a7:42:8e:90:d3 -> groot praktijklokaal kiné, hoek secretariaat
    "406",  // 40:01:7a:1c:0a:73 -> AP praktijklokaal kiné
    "407",  // 00:2c:c8:f0:fa:c3 -> AP 1 secretariaat, tussen 4.174/4.170
    "408",  // 00:2c:c8:ed:c9:23 -> AP 2 secretariaat, tussen 4.110/4.118
    "500",  // 70:df:2f:e2:06:a3 -> lab fysica, midden plafond
    "501",  // 70:df:2f:e2:06:83 -> klas medium, aan ingang
    "502",  // 70:df:2f:ec:16:43 -> klas medium, aan ingang
    "503",  // 40:01:7a:55:84:73 -> lab organische chemie, naast deur
    "504",  // 18:80:90:dc:bf:b3 -> lab algemene chemie, muur tov kant station
    "506",  // 70:df:2f:e7:b5:63 -> lab instrumentele chemie, muur kant station
    "507",  // 70:df:2f:e7:e4:73 -> klas large, nis
    "508",  // 70:df:2f:e2:0a:f3 -> klas medium 5, naast ingang
    "600",  // 70:df:2f:ec:16:53 -> leercentrum, naast ingang, links van nis
    "601",  // 70:df:2f:ec:c3:43 -> leercentrum, naast ingang, rechts van nis
    "602",  // 70:df:2f:7b:8e:63 -> klas medium 6, achter
    "603",  // 70:df:2f:34:dc:53 -> klas medium 7, naast deur
    "604",  // 40:01:7a:1c:05:23 -> klas small 3, naast deur
    "605",  // 70:df:2f:ec:c5:43 -> klas small 4, naast deur
    "606"   // f8:0b:cb:3d:82:a3 -> groepswerkruimte
};

static const char macs[NUMBER_OF_MACS][18] =
{ 
    "40:01:7a:80:7f:13",
    "40:01:7a:12:e0:74",
    "00:a7:42:8e:8b:33",
    "f8:0b:cb:3d:87:63",
    "40:01:7a:12:ec:d3",
    "00:2c:c8:f1:36:d2",
    "00:2c:c8:ep:23:79",
    "40:01:7a:14:08:03",
    "40:01:7a:14:05:33",
    "40:01:7a:80:78:53",
    "40:01:7a:12:c1:53",
    "40:01:7a:80:56:01",
    "40:01:7a:80:56:01",
    "18:80:90:c6:a1:c3",
    "40:01:7a:80:7e:7c",
    "40:01:7a:12:e8:83",
    "40:01:7a:80:78:03",
    "18:80:90:c6:a8:03",
    "40:01:7a:1c:09:23",
    "f8:0b:cb:3d:80:63",
    "00:2c:c8:8b:e2:53",
    "00:2c:c8:e9:3b:21",
    "00:2c:c8:6a:ad:c1",
    "40:01:7a:14:0f:c3",
    "00:2c:c8:ed:dc:23",
    "00:2c:c8:19:24:d3",
    "00:2c:c8:6a:8f:03",
    "2c:5a:0f:09:a9:a3",
    "00:a7:42:8e:88:c3",
    "40:01:7a:14:04:f3",
    "40:01:7a:13:fc:03",
    "18:80:90:dc:c8:23",
    "40:01:7a:1c:08:23",
    "40:01:7a:14:10:33",
    "00:a7:42:8e:90:d3",
    "40:01:7a:1c:0a:73",
    "00:2c:c8:f0:fa:c3",
    "00:2c:c8:ed:c9:23",
    "70:df:2f:e2:06:a3",
    "70:df:2f:e2:06:83",
    "70:df:2f:ec:16:43",
    "40:01:7a:55:84:73",
    "18:80:90:dc:bf:b3",
    "70:df:2f:e7:b5:63",
    "70:df:2f:e7:e4:73",
    "70:df:2f:e2:0a:f3",
    "70:df:2f:ec:16:53",
    "70:df:2f:ec:c3:43",
    "70:df:2f:7b:8e:63",
    "70:df:2f:34:dc:53",
    "40:01:7a:1c:05:23",
    "70:df:2f:ec:c5:43",
    "f8:0b:cb:3d:82:a3"
};