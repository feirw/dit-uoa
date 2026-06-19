# bottle για routes + templates
from bottle import route, run, template, request

import db


def _rows_from_age_result(result):
    # το 1ο query γυρνάει λίστα [όνομα, πλήθος, αεροπλάνα] αλλά το results θέλει dict για τον πίνακα
    if result is None:
        return None
    if isinstance(result, list) and len(result) == 3:
        return [
            {
                "Αεροπορική": result[0],
                "Επιβάτες (στο διάστημα ηλικίας)": result[1],
                "Αριθμός αεροπλάνων": result[2],
            }
        ]
    return result


@route("/")
def index():
    return template("templates/index.tpl")


def _connection_error_if_no_rows(rows):
    # αν δεν έχει γραμμές μπορεί να είναι λάθος σύνδεσης όχι απλά κενό query — το δείχνουμε στο template
    if rows:
        return ""
    err = getattr(db, "last_connection_error", None)
    return err or ""


@route("/findAirlinebyAge", method="POST")
def find_airline():
    age_x = request.forms.get("ageX")  # μέγιστο Χ
    age_y = request.forms.get("ageY")  # ελάχιστο Υ
    raw = db.get_airlines_by_age(age_y, age_x)
    rows = _rows_from_age_result(raw)
    return template(
        "templates/results.tpl",
        title="Κορυφαία αεροπορική ανά ηλικία επιβατών",
        rows=rows,
        connection_error=_connection_error_if_no_rows(rows),
    )


@route("/findAirportVisitors", method="POST")
def find_visitors():
    airline_name = request.forms.get("airlineName")
    date_a = request.forms.get("dateA")
    date_b = request.forms.get("dateB")
    rows = db.get_airport_visitors(airline_name, date_a, date_b)
    return template(
        "templates/results.tpl",
        title=f"Επισκέπτες αεροδρομίων — {airline_name}",
        rows=rows,
        connection_error=_connection_error_if_no_rows(rows),
    )


@route("/findAlternativeFlights", method="POST")
def find_alt_flights():
    src = request.forms.get("sourceCity")
    dst = request.forms.get("destCity")
    dt = request.forms.get("flightDate")
    rows = db.get_alternative_flights(src, dst, dt)
    return template(
        "templates/results.tpl",
        title="Εναλλακτικές πτήσεις",
        rows=rows,
        connection_error=_connection_error_if_no_rows(rows),
    )


@route("/findLargestAirlines", method="POST")
def find_largest():
    n = request.forms.get("nCount")
    rows = db.get_largest_airlines(n)
    try:
        n_disp = int(n)
    except (TypeError, ValueError):
        n_disp = n  # αν βάλει κείμενο αντί για αριθμό
    return template(
        "templates/results.tpl",
        title=f"Top {n_disp} αεροπορικές (κατά αριθμό πτήσεων)",
        rows=rows,
        connection_error=_connection_error_if_no_rows(rows),
    )


@route("/updatePassengerStatus", method="POST")
def update_status():
    airline = request.forms.get("airlineName")
    tier = request.forms.get("tier")
    db.update_passenger_tiers(airline)  # πρώτα update tiers
    rows = db.get_passengers_by_tier(airline, tier)  # μετά φιλτράρουμε με το tier που διάλεξε
    return template(
        "templates/results.tpl",
        title=f"Επιβάτες {tier} — {airline}",
        rows=rows,
        connection_error=_connection_error_if_no_rows(rows),
    )


if __name__ == "__main__":
    run(host="localhost", port=8080, debug=True, reloader=True)
