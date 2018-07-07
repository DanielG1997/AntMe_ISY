using AntMe.Deutsch;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AntMe.Player.Grossenbier
{
    /// <summary>
    /// Diese Datei enthält die Beschreibung für deine Ameise. Die einzelnen Code-Blöcke 
    /// (Beginnend mit "public override void") fassen zusammen, wie deine Ameise in den 
    /// entsprechenden Situationen reagieren soll. Welche Befehle du hier verwenden kannst, 
    /// findest du auf der Befehlsübersicht im Wiki (http://wiki.antme.net/de/API1:Befehlsliste).
    /// 
    /// Wenn du etwas Unterstützung bei der Erstellung einer Ameise brauchst, findest du
    /// in den AntMe!-Lektionen ein paar Schritt-für-Schritt Anleitungen.
    /// (http://wiki.antme.net/de/Lektionen)
    /// </summary>
    [Spieler(
        Volkname = "Grossenbier",   // Hier kannst du den Namen des Volkes festlegen
        Vorname = "Daniel Großenbach ,",       // An dieser Stelle kannst du dich als Schöpfer der Ameise eintragen
        Nachname = "Lennart Bierwolf"       // An dieser Stelle kannst du dich als Schöpfer der Ameise eintragen
    )]

    /// Kasten stellen "Berufsgruppen" innerhalb deines Ameisenvolkes dar. Du kannst hier mit
    /// den Fähigkeiten einzelner Ameisen arbeiten. Wie genau das funktioniert kannst du der 
    /// Lektion zur Spezialisierung von Ameisen entnehmen (http://wiki.antme.net/de/Lektion7).
    [Kaste(
        Name = "Späher",                  // Name der Berufsgruppe
        AngriffModifikator = -1,             // Angriffsstärke einer Ameise
        DrehgeschwindigkeitModifikator = -1, // Drehgeschwindigkeit einer Ameise
        EnergieModifikator = -1,             // Lebensenergie einer Ameise
        GeschwindigkeitModifikator = 2,     // Laufgeschwindigkeit einer Ameise
        LastModifikator = -1,                // Tragkraft einer Ameise
        ReichweiteModifikator = 1,          // Ausdauer einer Ameise
        SichtweiteModifikator = 1           // Sichtweite einer Ameise
    )]

    [Kaste(
        Name = "Krieger",                  // Name der Berufsgruppe
        AngriffModifikator = 2,             // Angriffsstärke einer Ameise
        DrehgeschwindigkeitModifikator = 0, // Drehgeschwindigkeit einer Ameise
        EnergieModifikator = -1,             // Lebensenergie einer Ameise
        GeschwindigkeitModifikator = 2,     // Laufgeschwindigkeit einer Ameise
        LastModifikator = -1,                // Tragkraft einer Ameise
        ReichweiteModifikator = -1,          // Ausdauer einer Ameise
        SichtweiteModifikator = -1           // Sichtweite einer Ameise
    )]

    [Kaste(
        Name = "Störer",                  // Name der Berufsgruppe
        AngriffModifikator = -1,             // Angriffsstärke einer Ameise
        DrehgeschwindigkeitModifikator = 0, // Drehgeschwindigkeit einer Ameise
        EnergieModifikator = -1,             // Lebensenergie einer Ameise
        GeschwindigkeitModifikator = 2,     // Laufgeschwindigkeit einer Ameise
        LastModifikator = 2,                // Tragkraft einer Ameise
        ReichweiteModifikator = -1,          // Ausdauer einer Ameise
        SichtweiteModifikator = -1           // Sichtweite einer Ameise
    )]
    public class GrossenbierKlasse : Basisameise
    {
        public int Hilferufe = 0;
        public static List<Basisameise> Hilferuf = new List<Basisameise>();
        public static bool Späherswitch = false;
        bool apfeltarget = false;
        public static Spielobjekt bau = null;
        public static HashSet<Obst> Äpfel = new HashSet<Obst>();
        public static Tuple<int, int> GenaueBauKoordinaten = null;
        Ameise target = null;
        Basisameise kriegerziel = null;
        //public static List<Tuple<int,int>> SpähKoordinaten = new List<Tuple<int, int>>();

        #region Kasten

        /// <summary>
        /// Jedes mal, wenn eine neue Ameise geboren wird, muss ihre Berufsgruppe
        /// bestimmt werden. Das kannst du mit Hilfe dieses Rückgabewertes dieser 
        /// Methode steuern.
        /// Weitere Infos unter http://wiki.antme.net/de/API1:BestimmeKaste
        /// </summary>
        /// <param name="anzahl">Anzahl Ameisen pro Kaste</param>
        /// <returns>Name der Kaste zu der die geborene Ameise gehören soll</returns>
        public override string BestimmeKaste(Dictionary<string, int> anzahl)
        {
            // Gibt den Namen der betroffenen Kaste zurück.
            if (Späherswitch == false && anzahl["Späher"] < 10)
                return "Späher";
            else if (Späherswitch == true && anzahl["Späher"] < 5)
                return "Späher";
            else if(anzahl["Krieger"] < 20)
            {
                Späherswitch = true;
                return "Krieger";
            }
            else if (anzahl["Störer"] < 10)
            {
                return "Störer";
            }
            else
                return "Krieger";
        }   


        #endregion

        #region Fortbewegung

        /// <summary>
        /// Wenn die Ameise keinerlei Aufträge hat, wartet sie auf neue Aufgaben. Um dir das 
        /// mitzuteilen, wird diese Methode hier aufgerufen.
        /// Weitere Infos unter http://wiki.antme.net/de/API1:Wartet
        /// </summary>
        public override void Wartet()
        {
            if(Kaste == "Krieger")
            {
                if(GenaueBauKoordinaten != null && Hilferuf.Count == 0 && kriegerziel == null)
                {
                    GeheZuKoordinate(AddiereTuple(GenaueBauKoordinaten, new Tuple<int, int>(Zufall.Zahl(-100, 100), Zufall.Zahl(-100, 100))));
                }
                if(Hilferuf.Count > 0 && kriegerziel == null)
                {
                    kriegerziel = Hilferuf.ElementAt(0);
                    Hilferuf.Remove(Hilferuf.ElementAt(0));
                }
                if(kriegerziel != null)
                {
                    GeheZuKoordinate(HoleKoordinaten(kriegerziel));
                }

            }else if(Kaste == "Späher")
            {
                if (Kaste == "Späher" && GenaueBauKoordinaten != null)
                {
                    GeheZuKoordinate(AddiereTuple(GenaueBauKoordinaten, new Tuple<int, int>(Zufall.Zahl(-300, 300), Zufall.Zahl(-300, 300))));
                }
                else
                {
                    //LaufeSpirale();
                    //GeheZuKoordinate(SpähKoordinaten.ElementAt(0));
                    GeheGeradeaus();
                }
            }else if(Kaste == "Störer")
            {
                foreach(Obst o in Äpfel)
                {
                    if(GenaueBauKoordinaten != null)
                    {
                        int Bauentfernung = (int)(Math.Sqrt(Math.Pow(GenaueBauKoordinaten.Item1- HoleKoordinaten(o).Item1, 2) + Math.Pow(GenaueBauKoordinaten.Item2 - HoleKoordinaten(o).Item2, 2)));
                        if(Bauentfernung < 300)
                        {
                            apfeltarget = true; 
                            Denke("Aktives Stören");
                            //GeheZuKoordinate(HoleKoordinaten(o));
                            GeheZuZiel(o);
                            Nimm(o);

                            Tuple<int, int> position = HoleKoordinaten(this);
                            Tuple<int, int> differenz = new Tuple<int, int>(GenaueBauKoordinaten.Item1 - position.Item1, GenaueBauKoordinaten.Item2 - position.Item2);

                            int distanz = (int)(Math.Sqrt(differenz.Item1 * differenz.Item1 + differenz.Item2 * differenz.Item2));
                            double radiant = Math.Atan2(differenz.Item2, differenz.Item1);
                            int richtung = (int)(radiant * 360 / (2 * Math.PI));

                            if (richtung >= 0)
                                richtung -= 180;
                            else
                                richtung += 180;
                            DreheInRichtung(richtung);
                            GeheGeradeaus(10);
                        }
                        if(AktuelleLast == 0 && apfeltarget == false)
                             GeheZuKoordinate(GenaueBauKoordinaten);
                    }
                }
            }
            
        }

        /// <summary>
        /// Erreicht eine Ameise ein drittel ihrer Laufreichweite, wird diese Methode aufgerufen.
        /// Weitere Infos unter http://wiki.antme.net/de/API1:WirdM%C3%BCde
        /// </summary>
        public override void WirdMüde()
        {
            //if (AktuelleEnergie < MaximaleEnergie / 2 || ZurückgelegteStrecke < Reichweite / 2)
            //    GeheZuBau();
        }

        /// <summary>
        /// Wenn eine Ameise stirbt, wird diese Methode aufgerufen. Man erfährt dadurch, wie 
        /// die Ameise gestorben ist. Die Ameise kann zu diesem Zeitpunkt aber keinerlei Aktion 
        /// mehr ausführen.
        /// Weitere Infos unter http://wiki.antme.net/de/API1:IstGestorben
        /// </summary>
        /// <param name="todesart">Art des Todes</param>
        public override void IstGestorben(Todesart todesart)
        {
        }

        /// <summary>
        /// Diese Methode wird in jeder Simulationsrunde aufgerufen - ungeachtet von zusätzlichen 
        /// Bedingungen. Dies eignet sich für Aktionen, die unter Bedingungen ausgeführt werden 
        /// sollen, die von den anderen Methoden nicht behandelt werden.
        /// Weitere Infos unter http://wiki.antme.net/de/API1:Tick
        /// </summary>
        public override void Tick()
        {

            if(Kaste == "Störer" && AktuelleLast > 0 && AnzahlFremderAmeisenInSichtweite > 2 && Hilferufe < 1) {
                Hilferuf.Add(this);
                Hilferufe++;
            }
            if (Kaste == "Störer" && AktuelleLast > 0 && (int)(Math.Sqrt(Math.Pow(GenaueBauKoordinaten.Item1 - HoleKoordinaten(this).Item1, 2) + Math.Pow(GenaueBauKoordinaten.Item2 - HoleKoordinaten(this).Item2, 2))) > 300)
            {
                LasseNahrungFallen();
                apfeltarget = false;
                Hilferufe = 0;
            }
            if(kriegerziel != null)
            {
                if (Koordinate.BestimmeEntfernung(this, kriegerziel) < 20 && AnzahlFremderAmeisenInSichtweite == 0)
                {
                    kriegerziel = null;
                }
            }
            for (int i = Äpfel.Count-1; i >= 0; i--)
            {
                if(Äpfel.ElementAt(i).Menge == 0)
                {
                    Äpfel.Remove(Äpfel.ElementAt(i));
                }
            }
            if(bau == null)
            {
                GeheZuBau();
                bau = Ziel;
                BleibStehen();
            }

            if (target != null && GenaueBauKoordinaten == null)
            {
                if (target.AktuelleLast == 0)
                {
                    GenaueBauKoordinaten = HoleKoordinaten(target);
                }
                GeheZuKoordinate(HoleKoordinaten(target));
            }

        }

        #endregion

        #region Nahrung

        /// <summary>
        /// Sobald eine Ameise innerhalb ihres Sichtradius einen Apfel erspäht wird 
        /// diese Methode aufgerufen. Als Parameter kommt das betroffene Stück Obst.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:Sieht(Obst)"
        /// </summary>
        /// <param name="obst">Das gesichtete Stück Obst</param>
        public override void Sieht(Obst obst)
        {
            Äpfel.Add(obst);
        }

        /// <summary>
        /// Sobald eine Ameise innerhalb ihres Sichtradius einen Zuckerhügel erspäht wird 
        /// diese Methode aufgerufen. Als Parameter kommt der betroffene Zuckerghügel.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:Sieht(Zucker)"
        /// </summary>
        /// <param name="zucker">Der gesichtete Zuckerhügel</param>
        public override void Sieht(Zucker zucker)
        {
        }

        /// <summary>
        /// Hat die Ameise ein Stück Obst als Ziel festgelegt, wird diese Methode aufgerufen, 
        /// sobald die Ameise ihr Ziel erreicht hat. Ab jetzt ist die Ameise nahe genug um mit 
        /// dem Ziel zu interagieren.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:ZielErreicht(Obst)"
        /// </summary>
        /// <param name="obst">Das erreichte Stück Obst</param>
        public override void ZielErreicht(Obst obst)
        {
        }

        /// <summary>
        /// Hat die Ameise eine Zuckerhügel als Ziel festgelegt, wird diese Methode aufgerufen, 
        /// sobald die Ameise ihr Ziel erreicht hat. Ab jetzt ist die Ameise nahe genug um mit 
        /// dem Ziel zu interagieren.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:ZielErreicht(Zucker)"
        /// </summary>
        /// <param name="zucker">Der erreichte Zuckerhügel</param>
        public override void ZielErreicht(Zucker zucker)
        {
        }

        #endregion

        #region Kommunikation

        /// <summary>
        /// Markierungen, die von anderen Ameisen platziert werden, können von befreundeten Ameisen 
        /// gewittert werden. Diese Methode wird aufgerufen, wenn eine Ameise zum ersten Mal eine 
        /// befreundete Markierung riecht.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:RiechtFreund(Markierung)"
        /// </summary>
        /// <param name="markierung">Die gerochene Markierung</param>
        public override void RiechtFreund(Markierung markierung)
        {
        }

        /// <summary>
        /// So wie Ameisen unterschiedliche Nahrungsmittel erspähen können, entdecken Sie auch 
        /// andere Spielelemente. Entdeckt die Ameise eine Ameise aus dem eigenen Volk, so 
        /// wird diese Methode aufgerufen.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:SiehtFreund(Ameise)"
        /// </summary>
        /// <param name="ameise">Erspähte befreundete Ameise</param>
        public override void SiehtFreund(Ameise ameise)
        {
        }

        /// <summary>
        /// So wie Ameisen unterschiedliche Nahrungsmittel erspähen können, entdecken Sie auch 
        /// andere Spielelemente. Entdeckt die Ameise eine Ameise aus einem befreundeten Volk 
        /// (Völker im selben Team), so wird diese Methode aufgerufen.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:SiehtVerb%C3%BCndeten(Ameise)"
        /// </summary>
        /// <param name="ameise">Erspähte verbündete Ameise</param>
        public override void SiehtVerbündeten(Ameise ameise)
        {
        }

        #endregion

        #region Kampf

        /// <summary>
        /// So wie Ameisen unterschiedliche Nahrungsmittel erspähen können, entdecken Sie auch 
        /// andere Spielelemente. Entdeckt die Ameise eine Ameise aus einem feindlichen Volk, 
        /// so wird diese Methode aufgerufen.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:SiehtFeind(Ameise)"
        /// </summary>
        /// <param name="ameise">Erspähte feindliche Ameise</param>
        public override void SiehtFeind(Ameise ameise)
        {
             
            if(ameise.AktuelleLast == ameise.MaximaleLast)
            {
                if (target == null && GenaueBauKoordinaten == null)
                {
                    target = ameise;
                    GeheZuKoordinate(HoleKoordinaten(ameise));
                }                
                if (Kaste == "Späher")
                {
                    if (ameise.AktuelleLast > 0)
                    {
                        GeheZuKoordinate(HoleKoordinaten(ameise));

                    }
                }
                else if (Kaste == "Krieger" && (kriegerziel == null || (kriegerziel != null && Koordinate.BestimmeEntfernung(this, kriegerziel) < 30)))
                {
                    if (ameise.AktuelleGeschwindigkeit < this.MaximaleGeschwindigkeit || ameise.AktuelleLast > 0)
                    {
                        this.Denke("Charrrrrge");
                        FangeAb(ameise);
                        if (Koordinate.BestimmeEntfernung(ameise, this) < 25)
                        {
                            GreifeAn(ameise);
                        }
                    }
                }
                
            }
        }

        /// <summary>
        /// So wie Ameisen unterschiedliche Nahrungsmittel erspähen können, entdecken Sie auch 
        /// andere Spielelemente. Entdeckt die Ameise eine Wanze, so wird diese Methode aufgerufen.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:SiehtFeind(Wanze)"
        /// </summary>
        /// <param name="wanze">Erspähte Wanze</param>
        public override void SiehtFeind(Wanze wanze)
        {
        }

        /// <summary>
        /// Es kann vorkommen, dass feindliche Lebewesen eine Ameise aktiv angreifen. Sollte 
        /// eine feindliche Ameise angreifen, wird diese Methode hier aufgerufen und die 
        /// Ameise kann entscheiden, wie sie darauf reagieren möchte.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:WirdAngegriffen(Ameise)"
        /// </summary>
        /// <param name="ameise">Angreifende Ameise</param>
        public override void WirdAngegriffen(Ameise ameise)
        {
            if(Kaste == "Krieger")
            {
                GreifeAn(ameise);
            }
        }

        /// <summary>
        /// Es kann vorkommen, dass feindliche Lebewesen eine Ameise aktiv angreifen. Sollte 
        /// eine Wanze angreifen, wird diese Methode hier aufgerufen und die Ameise kann 
        /// entscheiden, wie sie darauf reagieren möchte.
        /// Weitere Infos unter "http://wiki.antme.net/de/API1:WirdAngegriffen(Wanze)"
        /// </summary>
        /// <param name="wanze">Angreifende Wanze</param>
        public override void WirdAngegriffen(Wanze wanze)
        {
        }

        #endregion

        #region Methoden

        public Tuple<int,int> HoleAmeisenZiel(Ameise ameise)
        {
            double distance = ameise.RestStrecke;
            double richtung = ameise.RestWinkel + ameise.Richtung;

            double angle = (richtung / 360) * (Math.PI * 2);

            int x = (int)(Math.Cos(angle) * distance) + HoleKoordinaten(ameise).Item1;
            int y = (int)(Math.Sin(angle) * distance) + HoleKoordinaten(ameise).Item2;

            return new Tuple<int, int>(x, y);
        }

        public Tuple<int, int> AddiereTuple(Tuple<int,int> a, Tuple<int, int> b)
        {
            return new Tuple<int, int>(a.Item1 + b.Item1, a.Item2 + b.Item2);
        }

        public Tuple<int, int> SubtrahiereTuple(Tuple<int, int> a, Tuple<int, int> b)
        {
            return new Tuple<int, int>(a.Item1 - b.Item1, a.Item2 - b.Item2);
        }

        public Tuple<int,int> HoleKoordinaten(Spielobjekt spielobjekt)
        {
            if(bau != null) { 
                double distanz = Koordinate.BestimmeEntfernung(spielobjekt, bau);
                double richtung = Koordinate.BestimmeRichtung(bau, spielobjekt);

                double winkel = (richtung / 360) * (Math.PI * 2);

                int x = (int)(Math.Cos(winkel) * distanz);
                int y = (int)(Math.Sin(winkel) * distanz);

                return new Tuple<int, int> (x,y);
            }
            GeheZuBau();
            bau = Ziel;
            BleibStehen();
            return HoleKoordinaten(spielobjekt);
        }

        public Tuple<int, int> HoleKoordinaten(Basisameise ameise)
        {
            if (bau != null)
            {
                double distanz = Koordinate.BestimmeEntfernung(ameise, bau);
                double richtung = Koordinate.BestimmeRichtung(bau, ameise);

                double winkel = (richtung / 360) * (Math.PI * 2);

                int x = (int)(Math.Cos(winkel) * distanz);
                int y = (int)(Math.Sin(winkel) * distanz);

                return new Tuple<int, int>(x, y);
            }
            GeheZuBau();
            bau = Ziel;
            BleibStehen();
            return HoleKoordinaten(ameise);
        }

        public void GeheZuKoordinate(Tuple<int, int> koord)
        {
            Tuple<int, int> position = HoleKoordinaten(this);
            Tuple<int, int> differenz = new Tuple<int, int>(koord.Item1 - position.Item1, koord.Item2 - position.Item2);

            int distanz = (int)(Math.Sqrt(differenz.Item1 * differenz.Item1 + differenz.Item2 * differenz.Item2));
            double radiant = Math.Atan2(differenz.Item2, differenz.Item1);
            int richtung = (int)(radiant * 360 / (2 * Math.PI));

            DreheInRichtung(richtung);
            GeheGeradeaus(distanz);
        }

        public void FangeAb(Ameise ameise)
        {
            Tuple<int, int> A = HoleKoordinaten(this);
            Tuple<int, int> B = HoleKoordinaten(ameise);


            Tuple<int, int> H = new Tuple<int, int>(HoleAmeisenZiel(ameise).Item1, HoleAmeisenZiel(ameise).Item2);

            double sin_beta = ((A.Item1 - B.Item1) * (H.Item2 - B.Item2) - (A.Item2 - B.Item2) * (H.Item1 - B.Item1)) / (Math.Sqrt(Math.Pow((B.Item1 - A.Item1), 2) + Math.Pow((B.Item2 - A.Item2), 2)) * Math.Sqrt((Math.Pow((B.Item1 - H.Item1), 2) + Math.Pow((B.Item2 - H.Item2), 2))));
            double sin_alpha = (ameise.AktuelleGeschwindigkeit / this.AktuelleGeschwindigkeit) * sin_beta;

            if (Math.Abs(sin_alpha) > 1)
            {
                return;
            }

            double sin_gamma = sin_alpha * Math.Sqrt(1 - Math.Pow(sin_beta, 2)) + sin_beta * Math.Sqrt(1 - Math.Pow(sin_alpha, 2));
            if (((Math.Sqrt(Math.Pow((B.Item1 - A.Item1), 2) + Math.Pow((B.Item2 - A.Item2), 2))) * (sin_alpha / sin_gamma) > Math.Sqrt((Math.Pow((A.Item1 - H.Item1), 2) + Math.Pow((A.Item2 - H.Item2), 2)))))
            {
                return;
            }

            DreheInRichtung((int) (Math.Asin(sin_alpha) * 180 / Math.PI));
            GeheGeradeaus((int) (Math.Cos((Math.Asin(sin_alpha) * 180 / Math.PI)) * Math.Sqrt(Math.Pow(SubtrahiereTuple(A, B).Item1, 2) + Math.Pow(SubtrahiereTuple(A, B).Item2, 2))));

        }

        #endregion
    }
}
