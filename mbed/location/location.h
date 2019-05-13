#define NUMBER_OF_MACS 54


//location of AP 
/*
x[0]: level
x[1],X[2]: AP nr 
*/
static const char location[NUMBER_OF_MACS][4] =
{
    "000",    //   onderwijslab bouwkunde, muur kant station
    "001",    //   onderzoekslab recycon
    "002",    //   onderzoekslab omgevingstechnieken
    "003",    //   opslag bulk en puin
    "004",    //   naast toiletten inkom, boven plafond
    "005",    //   inkomhal, rechts van trappengang
    "006",    //   inkomhal, links van trappengang
    "100",    //   AP landschapskantoor 1e, midden vergaderzalen
    "101",    //   onderwijslab mechanische structuren en vibro akoestiek
    "102",    //   onderwijslab aandrijf en energietechnieken
    "103",    //   bergruimte machines en vermogenapp.
    "104",    //   onderwijslab energie en automatisering, kant gang
    "105",    //   onderwijslab mechanische vormgevingstechnieken, kant liften
    "106",    //   naast wc's, tegen plafond
    "200",    //   landschapsbureau 2e, hoek printernis
    "201",    //   onderwijslab mechanische meettechnieken
    "202",    //   onderwijslab ICT, midden muur LCD
    "203",    //   onderwijslab elektronica, kant tussendeur
    "204",    //   onderwijslab embedded software, rechtsboven doorgang IT lokaal
    "205",    //   AP bovenop datakast geplaatst, rechtstreeks in poort
    "300",    //   aula, kant foyer
    "301",    //   aula, kant raam
    "302",    //   aula, kant projectiescherm
    "303",    //   foyer aula, boven plafond zitbank
    "304",    //   AP 1 cafetaria, kant zitbank tov keuken
    "305",    //   AP 2 cafetaria, kant keuken
    "306",    //   AP 3 cafetaria, doorgang buitenterras
    "307",    //   AP 4 cafetaria, kant liften
    "308",    //   gang 3e, kant parking
    "309",    //   extra AP cafetaria
    "400",    //   grote pc klas achter boven
    "401",    //   kleine pc klas vooraan boven bord
    "402",    //   klas medium 1
    "403",    //   klas small 1
    "404",    //   onderzoekslokaal kine
    "405",    //   groot praktijklokaal kiné, hoek secretariaat
    "406",    //   AP praktijklokaal kiné
    "407",    //   AP 1 secretariaat, tussen 4.174/4.170
    "408",    //   AP 2 secretariaat, tussen 4.110/4.118
    "500",    //   lab fysica, midden plafond
    "501",    //   klas medium, aan ingang
    "502",    //   klas medium, aan ingang
    "503",    //   lab organische chemie, naast deur
    "504",    //   lab algemene chemie, muur tov kant station
    "505",    //   lab instrumentele chemie, muur kant station
    "600",    //   klas large, nis
    "601",    //   klas medium 5, naast ingang
    "602",    //   leercentrum, naast ingang, links van nis
    "603",    //   leercentrum, naast ingang, rechts van nis
    "604",    //   klas medium 6, achter
    "605",    //   klas medium 7, naast deur
    "606",    //   klas small 3, naast deur
    "607",    //   klas small 4, naast deur
    "608"     //   groepswerkruimte
};

static const char macs[NUMBER_OF_MACS][18] =
{
    "40:01:7a:80:7f:15",
    "40:01:7a:12:e0:75",
    "00:a7:42:8e:8b:35",
    "f8:0b:cb:3d:87:65",
    "40:01:7a:12:ec:d5",
    "00:2c:c8:f1:36:d5",
    "00:2c:c8:ep:23:75",
    "40:01:7a:14:08:05",
    "40:01:7a:14:05:35",
    "40:01:7a:80:78:55",
    "40:01:7a:12:c1:55",
    "40:01:7a:80:56:05",
    "40:01:7a:1c:05:b5",
    "18:80:90:c6:a1:c5",
    "40:01:7a:80:7e:75",
    "40:01:7a:12:e8:85",
    "40:01:7a:80:78:05",
    "18:80:90:c6:a8:05",
    "40:01:7a:1c:09:25",
    "f8:0b:cb:3d:80:65",
    "00:2c:c8:8b:e2:55",
    "00:2c:c8:e9:3b:23",
    "00:2c:c8:6a:ad:C3",
    "40:01:7a:14:0f:c5",
    "00:2c:c8:ed:dc:25",
    "00:2c:c8:19:24:d5",
    "00:2c:c8:6a:8f:05",
    "2c:5a:0f:09:a9:a5",
    "00:a7:42:8e:88:c5",
    "00:2c:c8:e9:24:d5",
    "40:01:7a:14:04:f5",
    "40:01:7a:13:fc:05",
    "18:80:90:dc:c8:25",
    "40:01:7a:1c:08:25",
    "40:01:7a:14:10:35",
    "00:a7:42:8e:90:d5",
    "40:01:7a:1c:0a:75",
    "00:2c:c8:f0:fa:c5",
    "00:2c:c8:ed:c9:25",
    "70:df:2f:e2:06:a5",
    "70:df:2f:e2:06:85",
    "70:df:2f:ec:16:45",
    "40:01:7a:55:84:75",
    "18:80:90:dc:bf:b5",
    "70:df:2f:e7:b5:65",
    "70:df:2f:e7:e4:75",
    "70:df:2f:e2:0a:f5",
    "70:df:2f:ec:16:55",
    "70:df:2f:ec:c3:45",
    "70:df:2f:7b:8e:65",
    "70:df:2f:34:dc:55",
    "40:01:7a:1c:05:25",
    "70:df:2f:ec:c5:45",
    "f8:0b:cb:3d:82:a5"
};