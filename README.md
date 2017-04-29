# Drawing robotic hand

Zovemo se Dunja Šmigovec i Dino Grgić. Učenici smo III. gimnazije Osijek i volimo računalnu znanost i IoT.  Već druge godine sudjelujemo na Osijek Mini Maker Fairu, a ove godine(2017.) predstavljamo projekt Drawing robotic hand.

* [Uvod](#uvod)

* [Dizajn i shema](#dizajn-i-shema)

* [Mehanika](#mehanika)

* [Inverzna kinematika](#inverzna-kinematika)

* [Kontakt](#kontakt)

## Uvod

Drawing robotic hand je robotska ruka sa tri članka koja uz pomoć inverzne kinematike te pričvršćene olovke na zadnjem članku slika zadanu sliku na papiru. Na prva dva članka nalaze se servo motori koji su pričvršćeni za kostur ruke dok se na zadnjem servo motoru nalazi članak koji podiže i spušta olovku.. 

<u>Potrebni dijelovi</u>:

 * 2 kotačića koja imaju slobodu kretnje u svim smjerovima
 * Dvije letvice koje predstavljaju kostur ruke jednakih duljina
 * Mikrokontroler(Arduino, Croduino, Genuino...)
 * 3 servo motora(sa momentom većim od 7 g/cm)
 * Power supply za servo motore
 * Različiti šarafi i matice
 * Vodiči
 
 <u>Potreban software</u>:

  * Arduino IDE
  * Processing *
  * MATLAB *
 
*različiti načini za slikanje na papiru (u svrhu demoa koristit ćemo Arduino IDE) kodovi za <i>Processing 2DOF Robotic Arm</i> i <i>MATLAB Image Processing Robotic Arm</i> mogu se naći na internetu

<u>Opcionalni dijelovi</u>:
(Nisu potrebni za osnovni rad ruke)
* Protoboard
* Lemilica i oprema za lemljenje
* Bušilica za sitne rupe na krni serva
* Drvena ploča na kojoj bi se nalazio prvi servo od kojeg ruka počinje
* Škripac

## Dizajn i schema
<u>Model ruke:</u>
![alt text](https://mandrillapp.com/track/click/30306441/osijek.makerfaire.com?p=eyJzIjoiSFlFWWJhQnlEbkl0ZmRuS2xKVEZQbzdrWmhzIiwidiI6MSwicCI6IntcInVcIjozMDMwNjQ0MSxcInZcIjoxLFwidXJsXCI6XCJodHRwOlxcXC9cXFwvb3NpamVrLm1ha2VyZmFpcmUuY29tXFxcL2luZGV4LnBocD9nZi1kb3dubG9hZD0yMDE3JTJGMDQlMkYxNzk2ODAyOV8xMjM5OTM3Mzg2MDU2MDQzXzE1OTY3MDIwNDFfby5wbmcmZm9ybS1pZD02JmZpZWxkLWlkPTIyJmhhc2g9YWNmMmE3NzAxMmJjNjA1N2NkZmQ3ZjJmOGRiMjE4YmYxMGEzNDk5MWNjNmQ1M2JjMDRlNWU2YmE5ZDgwYWRlN1wiLFwiaWRcIjpcImYyNmNlNzI2NzgwNzQ4MjA5OTVkYThkODBlODNlNTViXCIsXCJ1cmxfaWRzXCI6W1wiOTNmYWVjNWYwNTE3ODAxMDY3NWUxNmNmMjI2NmYyOWU1OGZiOGI5ZlwiXX0ifQ "3D model ruke")

Prvo je potrebno pronaći dvije letvice čija je udaljenost od serva do serva jednakih duljina (biti će nam potrebno kasnije za inverznu kinematiku). Ove dvije na slici su isprintane sad 3D printerom. Model nije teško napraviti. Prva letvica treba imati dio na koji će se staviti prvi servo te rupu kroz koju će se provući drugi servo koji se spaja na drugu letvicu. Na drugoj letvici nalazi se mjesto za zadnji, treći servo koji će držati olovku. Dobra ideja je ostaviti na svakom dijelu malu rupu za kabal od serva kako bi se on lagano mogao provući. Kao podrška za težinu ruke i kretanje na dva dijela na drugom članku mogu se staviti kotačići koji se okreću u svim smjerovima. 

<u>Isprintani kostur ruke:</u>
![alt text](https://scontent-fra3-1.xx.fbcdn.net/v/t35.0-12/18216300_1985323745029405_485590600_o.jpg?oh=fd78ac52cf3f3545d4582c944b0a1922&oe=5906384D "Isprintani kostur ruke")

<u>Schema elektroničkih dijelova:</u>
![alt text](https://scontent-fra3-1.xx.fbcdn.net/v/t35.0-12/18196076_1985322395029540_145663468_o.png?oh=c2262759fa4be70a66c7931f61ba3450&oe=5905E2E5 "Schema")

Za naš projekt kao mitrokontrole koristili smo Arduino Nano, servo motor isu Tower Pro MG995 i unvierzalni power adapter (na slici je power supply ali je schema ista). Korsitili smo voltažu od 6V.

## Mehanika
 
Ruku ovoga projekta možemo opisati i kao 2DOF rootska ruka. DOF je skračenica engleskoga jezika koja znači <i>degree of freedom,</i> a u našoj treminologiji mehanike poznata je kao stupanj slobode gibanja. Stupanj slobode gibanja predstavlja gibanje tijela i sustava tijela koje je opisano neovisnom koordinatom. Broj 2 govori nam da se naš mehanički sustav sastoji od 2 članka koji se gibaju nezavisno. Treći članak koji podiže i spušta olovku ne brojimo kao dio sustava članaka jer on ne ovisi o inverznoj kinematici već samo podiže i spušta samu olovku.

## Inverzna kinematika
Inverzna kinematika je metoda koja se koristi za računanje kuta serva za određenu točku 2D ili 3D prostora. U našem projektu koristimo inverznu kinematiku za računanje kuta serva za točku (x,y) koja se nalazi na papiru. Za glavna dva nezavisna serva (S1 - početni servo, S2 - slobodni servo) računamo kut uz pomoć inverzne kinematike. 
![alt text](
https://www.mathworks.com/help/examples/fuzzy_featured/win64/xxinvkine_angles.png "Inverzna kinematika")

Kao što se primjeti sa slike imamo dva članka. Članci mogu biti jednakih duljina od serva do serva ali se mogu razlikovati po cijeloj duljini letvice. Na slici vidimo letvice L1 i L2. L1 prvim krajem drži se za početni servo a zadnjim krajem drži S2 slobodni servo. L2 se svojim početkom drži za servo S2 a na kraju drži olovku koju podiže i spušta. Potrebno je izračunati kutove Θ1 i Θ2  kako bi ruku mogli staviti na bilo koji dio papira. A to možemo sa sljedećim trigonometrijskim funkcijama :

![alt text](
http://engineeronadisk.com/V2/hugh_jack_masters/engineeronadisk-26.gif "Inverzna kinematika formule")

Na kraju u kodu koristimo fomrule u funkciji :
```
void kutServo()
{
  c = sqrt( sq(x) + sq(y) );    // pitagorin poučak
  // kosinus, gornji clanak
  B = (acos( (sq(b) - sq(a) - sq(c))/(-2*a*c) )) * (180/pi);  
  // kosinus, kut nasuprot hipotenuze
  C = (acos( (sq(c) - sq(b) - sq(a))/(-2*a*b) )) * (180/pi);            
  // izračunaj kut koji kalibrira utjecaj donjeg clanka na prvi
  theta = (asin( y / c )) * (180/pi);                               
  // izracunaj kutove na kraju i dodaj korekciju
  s1_A = B + theta + s1_A;          
  s2_A = C + s2_A;                            
}
```

## Kontakt
Ovdje se nalaze naši kontakti rado ćemo vam odgovriti na bilo koje pitanje koje imate o ovome projektu:

Dunja Šmigovec - dunja.smigovec@gmail.com

Dino Grgić - dino.grgic1@gmail.com



