import os
import pymysql

# αν δεν κάνει connect το κρατάμε εδώ για να το δείξουμε στο results (αλλιώς νομίζεις ότι δεν βρήκε τίποτα)
last_connection_error = None


def get_connection():
    global last_connection_error
    last_connection_error = None
    try:
        return pymysql.connect(
            host=os.environ.get("MYSQL_HOST", "localhost"),
            user=os.environ.get("MYSQL_USER", "root"),
            password=os.environ.get("MYSQL_PASSWORD", "test123!"),  # άλλαξε το αν χρειάζεται / βάλε env
            database=os.environ.get("MYSQL_DB", "flights"),
            cursorclass=pymysql.cursors.DictCursor,
        )
    except Exception as e:
        last_connection_error = str(e)
        print(f"Connection error: {e}")
        return None


def _close(conn):
    if conn is not None:
        conn.close()


# --- 1 findAirlinebyAge (από εκφώνηση: ηλικία μεταξύ Υ και Χ, δηλ >Y και <X) ---
def get_airlines_by_age(age_y, age_x):
    conn = get_connection()
    if conn is None:
        return None
    try:
        try:
            lo = int(age_y)
            hi = int(age_x)
        except (TypeError, ValueError):
            return None

        sql = """
            SELECT a.id, a.name, COUNT(DISTINCT p.id) AS p_count
            FROM flights_has_passengers fh, flights f, passengers p, routes r, airlines a
            WHERE fh.flights_id = f.id
              AND fh.passengers_id = p.id
              AND f.routes_id = r.id
              AND r.airlines_id = a.id
              AND (YEAR(CURDATE()) - p.year_of_birth) > %s
              AND (YEAR(CURDATE()) - p.year_of_birth) < %s
            GROUP BY a.id, a.name
        """
        with conn.cursor() as cursor:
            cursor.execute(sql, (lo, hi))  # lo=Y, hi=X
            candidates = cursor.fetchall()
            if not candidates:
                return None
            best = max(candidates, key=lambda r: r["p_count"])
            # δεύτερο query για πόσα αεροπλάνα έχει η εταιρεία που βγήκε πρώτη
            cursor.execute(
                "SELECT COUNT(*) AS air_count FROM airlines_has_airplanes WHERE airlines_id = %s",
                (best["id"],),
            )
            air_count = cursor.fetchone()["air_count"]
            return [best["name"], best["p_count"], air_count]
    finally:
        _close(conn)


# --- 2 findAirportVisitors ---
def get_airport_visitors(airline_name, date_a, date_b):
    conn = get_connection()
    if conn is None:
        return None
    # ένα query για αεροδρόμιο αναχώρησης + ένα για άφιξη, μετά τα βάζω μαζί με sum
    sql = """
        SELECT airport_name, SUM(visitors) AS visitors
        FROM (
            SELECT ap.name AS airport_name, COUNT(*) AS visitors
            FROM flights f, routes r, airlines a, flights_has_passengers fh, airports ap
            WHERE f.routes_id = r.id
              AND r.airlines_id = a.id
              AND f.id = fh.flights_id
              AND ap.id = r.source_id
              AND a.name = %s AND f.date BETWEEN %s AND %s
            GROUP BY ap.name
            UNION ALL
            SELECT ap.name, COUNT(*)
            FROM flights f, routes r, airlines a, flights_has_passengers fh, airports ap
            WHERE f.routes_id = r.id
              AND r.airlines_id = a.id
              AND f.id = fh.flights_id
              AND ap.id = r.destination_id
              AND a.name = %s AND f.date BETWEEN %s AND %s
            GROUP BY ap.name
        ) t
        GROUP BY airport_name
        ORDER BY visitors DESC
    """
    try:
        with conn.cursor() as cursor:
            cursor.execute(sql, (airline_name, date_a, date_b, airline_name, date_a, date_b))
            return cursor.fetchall()
    finally:
        _close(conn)


# --- 3 findAlternativeFlights ---
def get_alternative_flights(source_city, dest_city, flight_date):
    conn = get_connection()
    if conn is None:
        return None
    # πόλεις από routes (source/destination), αεροπλάνο από flights
    sql = """
        SELECT f.id, a.name AS airline_name, ap_dst.name AS airport_name, pl.model
        FROM flights f, routes r, airlines a, airports ap_src, airports ap_dst, airplanes pl
        WHERE f.routes_id = r.id
          AND r.airlines_id = a.id
          AND r.source_id = ap_src.id
          AND r.destination_id = ap_dst.id
          AND f.airplanes_id = pl.id
          AND ap_src.city = %s AND ap_dst.city = %s AND f.date = %s
          AND a.active = 'Y'
    """
    try:
        with conn.cursor() as cursor:
            cursor.execute(sql, (source_city, dest_city, flight_date))
            return cursor.fetchall()
    finally:
        _close(conn)


# --- 4 findLargestAirlines ---
def get_largest_airlines(n_count):
    conn = get_connection()
    if conn is None:
        return None
    try:
        n = max(1, int(n_count))
    except (TypeError, ValueError):
        n = 1
    sql = """
        SELECT a.name, a.code,
               (SELECT COUNT(*) FROM airlines_has_airplanes h WHERE h.airlines_id = a.id) AS plane_count,
               (SELECT COUNT(*) FROM flights f, routes r
                WHERE f.routes_id = r.id AND r.airlines_id = a.id) AS flight_count
        FROM airlines a
        ORDER BY flight_count DESC
        LIMIT %s
    """
    try:
        with conn.cursor() as cursor:
            cursor.execute(sql, (n,))
            return cursor.fetchall()
    finally:
        _close(conn)


# --- 5 updatePassengerStatus ---
def update_passenger_tiers(airline_name):
    conn = get_connection()
    if conn is None:
        return
    try:
        with conn.cursor() as cursor:
            cursor.execute("SHOW COLUMNS FROM passengers LIKE 'tier'")
            if not cursor.fetchone():
                # αν δεν υπάρχει στήλη την φτιάχνω (δεν ήταν στο dump)
                cursor.execute(
                    "ALTER TABLE passengers ADD COLUMN tier VARCHAR(20) DEFAULT 'Basic'"
                )
            sql = """
                SELECT p.id, COUNT(fh.flights_id) AS flight_count
                FROM passengers p, flights_has_passengers fh, flights f, routes r, airlines a
                WHERE p.id = fh.passengers_id
                  AND fh.flights_id = f.id
                  AND f.routes_id = r.id
                  AND r.airlines_id = a.id
                  AND a.name = %s
                GROUP BY p.id
            """
            cursor.execute(sql, (airline_name,))
            passengers = cursor.fetchall()
            for p in passengers:
                cnt = p["flight_count"]
                # κανόνες όπως στην εκφώνηση
                if cnt > 5:
                    tier = "Platinum"
                elif cnt == 5:
                    tier = "Gold"
                elif cnt > 1:
                    tier = "Silver"
                else:
                    tier = "Basic"
                cursor.execute(
                    "UPDATE passengers SET tier = %s WHERE id = %s",
                    (tier, p["id"]),
                )
            conn.commit()
    finally:
        _close(conn)


# --- 6 (μετά το update) φέρνουμε τους επιβάτες με συγκεκριμένο tier για την αεροπορική ---
def get_passengers_by_tier(airline_name, tier):
    conn = get_connection()
    if conn is None:
        return None
    sql = """
        SELECT DISTINCT p.name, p.surname, p.tier
        FROM passengers p, flights_has_passengers fh, flights f, routes r, airlines a
        WHERE p.id = fh.passengers_id
          AND fh.flights_id = f.id
          AND f.routes_id = r.id
          AND r.airlines_id = a.id
          AND a.name = %s AND p.tier = %s
    """
    try:
        with conn.cursor() as cursor:
            cursor.execute(sql, (airline_name, tier))
            return cursor.fetchall()
    finally:
        _close(conn)
