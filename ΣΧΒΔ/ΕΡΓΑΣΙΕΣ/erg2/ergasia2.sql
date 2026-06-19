

#ΕΡΓΑΣΙΑ 2 ΣΧΕΔΙΑΣΗ ΚΑΙ ΧΡΗΣΗ ΒΑΣΕΩΝ ΔΕΔΟΜΕΝΩΝ
#################################################################################################
#1st

--  Βρείτε τους αριθμούς των αεροσκαφών της κατασκευάστριας εταιρείας “Airbus”
-- που πετούν για την αεροπορική εταιρεία “Lufthansa”.

SELECT DISTINCT a.number
FROM airplanes a, airlines_has_airplanes aha, airlines al
WHERE  a.manufacturer = 'Airbus' 
AND (a.id = aha.airplanes_id AND al.id = aha.airlines_id AND al.name ='Lufthansa');

#2nd

-- Βρείτε τα ονόματα των αεροπορικών εταιρειών με δρομολόγιο από “Athens" προς
-- “Prague”.

SELECT DISTINCT al.name 
FROM airlines al, routes r, airports src, airports dest
WHERE al.id = r.airlines_id AND r.source_id=src.id AND src.city = 'Athens' 
AND r.destination_id=dest.id AND dest.city = 'Prague';

#3rd

-- Πόσοι επιβάτες ταξίδεψαν την ημερομηνία 2012-02-19 με πτήσεις της “Aegean
-- Airlines”;

SELECT COUNT(DISTINCT fhp.passengers_id) 
FROM flights_has_passengers fhp, flights f, routes r, airlines al 
WHERE fhp.flights_id = f.id  AND f.date='2012-02-19' AND r.id = f.routes_id AND r.airlines_id= al.id AND al.name='Aegean Airlines';

#4th

-- Ελέγξτε αν υπήρξε πτήση της “Olympic Airways” την ημερομηνία 2014-12-12 από
-- “Athens El. Venizelos” σε “London Gatwick”. (Το ερώτημα θα πρέπει να
-- επιστρέφει ως απάντηση μια σχέση με μια πλειάδα και μια στήλη με τιμή “yes” ή
-- “no”). Απαγορεύεται η χρήση Flow Control Operators (δηλαδή, if, case, κλπ.).

SELECT 'yes'
WHERE EXISTS(
    SELECT *
    FROM routes r, flights f, airports src, airports dest, airlines al
    WHERE f.date='2014-12-12' 
      AND r.id = f.routes_id 
      AND r.airlines_id = al.id 
      AND al.name='Olympic Airways' 
      AND r.source_id = src.id 
      AND src.name = 'Athens El. Venizelos' 
      AND r.destination_id = dest.id 
      AND dest.name='London Gatwick'
)

UNION

SELECT 'no'
WHERE NOT EXISTS(
    SELECT *
    FROM routes r, flights f, airports src, airports dest, airlines al
    WHERE f.date='2014-12-12' 
      AND r.id = f.routes_id 
      AND r.airlines_id = al.id 
      AND al.name='Olympic Airways' 
      AND r.source_id = src.id 
      AND src.name = 'Athens El. Venizelos' 
      AND r.destination_id = dest.id 
      AND dest.name='London Gatwick'
);

#5th
-- Ποια είναι η μέση ηλικία των επισκεπτών της πόλης “Berlin”;

SELECT AVG(2026-p.year_of_birth) 
FROM passengers p, flights_has_passengers fhp, flights f, routes r, airports dest 
WHERE fhp.passengers_id=p.id AND fhp.flights_id=f.id AND f.routes_id=r.id AND r.destination_id=dest.id AND dest.city='Berlin';

#6th

-- Βρείτε τα ονόματα και τα επίθετα των επιβατών που έχουν κάνει όλα τα ταξίδια
-- τους με το ίδιο αεροπλάνο.

SELECT p.name , p.surname
FROM passengers p, flights f, flights_has_passengers fhp
WHERE fhp.flights_id=f.id AND fhp.passengers_id=p.id 
GROUP BY p.id, p.name, p.surname
HAVING COUNT(DISTINCT f.airplanes_id) = 1;

#7st
-- Βρείτε την πόλη αναχώρησης και προορισμού σε πτήσεις που έχουν
-- πραγματοποιηθεί ανάμεσα στις ημερομηνίες 2010-03-01 και 2014-07-17 εφόσον
-- οι πτήσεις αυτές είχαν πάνω από 5 επιβάτες.

SELECT DISTINCT src.city, dest.city
FROM flights f, routes r, airports src, airports dest, flights_has_passengers fhp
WHERE f.routes_id = r.id
  AND r.source_id = src.id
  AND r.destination_id = dest.id
  AND fhp.flights_id = f.id
  AND f.date >= '2010-03-01' AND f.date <= '2014-07-17'
GROUP BY f.id, src.city, dest.city
HAVING COUNT(fhp.passengers_id) > 5;


#8th
-- Για κάθε αεροπορική εταιρεία που έχει ακριβώς 4 αεροσκάφη, βρείτε το όνομα και
-- τον κωδικό της καθώς και τον αριθμό των δρομολογίων που διαθέτει.

SELECT al.id, al.name, COUNT(DISTINCT r.id)  
FROM airlines_has_airplanes aha, airlines al , routes r
WHERE aha.airlines_id=al.id  AND r.airlines_id=al.id 
GROUP BY al.id, al.name
HAVING COUNT(DISTINCT aha.airplanes_id) = 4 ;

#9th

-- Βρείτε τα ονοματεπώνυμα των επιβατών που έχουν πετάξει με όλες τις
-- αεροπορικές εταιρείες που είναι ενεργές.

SELECT p.name, p.surname
FROM passengers p, flights_has_passengers fhp, flights f, routes r, airlines al
WHERE p.id = fhp.passengers_id
  AND fhp.flights_id = f.id
  AND f.routes_id = r.id
  AND r.airlines_id = al.id
  AND al.active = 'Y' 
GROUP BY p.id, p.name, p.surname
HAVING COUNT(DISTINCT al.id) = (
    SELECT COUNT(*)
    FROM airlines
    WHERE active = 'Y'
);

#10th
-- Βρείτε τα ονόματα και τα επίθετα των επιβατών που έχουν πετάξει μόνο με την
-- εταιρεία “Aegean Airlines” και αυτά που έχουν κάνει πάνω από ένα ταξίδι στο
-- χρονικό διάστημα 2011-01-02 έως 2013-12-31


SELECT p.name, p.surname
FROM passengers p, flights_has_passengers fhp, flights f, routes r, airlines al
WHERE p.id = fhp.passengers_id
  AND fhp.flights_id = f.id
  AND f.routes_id = r.id
  AND r.airlines_id = al.id
  AND f.date >= '2011-01-02'
  AND f.date <= '2013-12-31'
GROUP BY p.id, p.name, p.surname
HAVING COUNT(DISTINCT al.name) = 1
   AND MAX(al.name) = 'Aegean Airlines'
   AND COUNT(f.id) > 1;


###########################################################################################
