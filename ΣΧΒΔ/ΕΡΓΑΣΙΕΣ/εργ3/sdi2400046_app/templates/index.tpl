<!DOCTYPE html>
<html lang="el">
<head>
    <meta charset="UTF-8">
    <title>Σύστημα Πτήσεων 2026</title>

    <style>
        body {
            font-family: sans-serif;
            margin: 40px;
            line-height: 1.6;
            background: #fff0f6;
            color: #5c2d4a;
        }

        h1 {
            color: #c2185b; /* pink theme because we love pink */
        }

        .form-section {
            background: #fffafc;
            padding: 20px;
            border-radius: 10px;
            margin-bottom: 20px;
            border: 1px solid #f8bbd0;
            box-shadow: 0 2px 8px rgba(233, 30, 99, 0.08);
        }

        h2 {
            color: #ad1457;
        }

        label {
            display: block;
            margin-top: 10px;
        }

        input, select {
            padding: 8px;
            width: 280px;
            margin-top: 5px;
            border: 1px solid #f48fb1;
            border-radius: 5px;
            background: #fff;
        }

        input:focus, select:focus {
            outline: none;
            border-color: #e91e63;
            box-shadow: 0 0 0 2px rgba(233, 30, 99, 0.15);
        }

        button {
            background: #e91e63;
            color: white;
            border: none;
            padding: 10px 20px;
            cursor: pointer;
            margin-top: 15px;
            border-radius: 5px;
        }

        button:hover {
            background: #c2185b;
        }
    </style>
</head>

<body>

<!-- κάθε form πάει στο αντίστοιχο route στο app.py που έχουμε φτιάξει σε ξεχωριστό αρχείο -->
<div class="form-section">
    <h2>1. Εύρεση Αεροπορικών ανά ηλικία επιβατών</h2>

    <form action="/findAirlinebyAge" method="POST">
        <label>Ηλικία Υ (ελάχιστη):</label>
        <input type="number" name="ageY" min="0" max="120" required>

        <label>Ηλικία Χ (μέγιστη):</label>
        <input type="number" name="ageX" min="0" max="120" required>

        <button type="submit">Αναζήτηση</button>
    </form>
</div>

<!-- 2 findAirportVisitors -->
<div class="form-section">
    <h2>2. Επισκέπτες Αεροδρομίου</h2>

    <form action="/findAirportVisitors" method="POST">
        <label>Όνομα Αεροπορικής:</label>
        <input type="text" name="airlineName" placeholder="π.χ. Aegean Airlines" required>

        <label>Ημερομηνία Από:</label>
        <input type="date" name="dateA" required>

        <label>Ημερομηνία Έως:</label>
        <input type="date" name="dateB" required>

        <button type="submit">Εύρεση</button>
    </form>
</div>

<!-- 3 findAlternativeFlights -->
<div class="form-section">
    <h2>3. Εναλλακτικές Πτήσεις</h2>

    <form action="/findAlternativeFlights" method="POST">
        <label>Πόλη Αναχώρησης:</label>
        <input type="text" name="sourceCity" required>

        <label>Πόλη Προορισμού:</label>
        <input type="text" name="destCity" required>

        <label>Ημερομηνία:</label>
        <input type="date" name="flightDate" required>

        <button type="submit">Αναζήτηση</button>
    </form>
</div>

<!-- 4 findLargestAirlines -->
<div class="form-section">
    <h2>4. Μεγαλύτερες Αεροπορικές</h2>

    <form action="/findLargestAirlines" method="POST">
        <label>Top N:</label>
        <input type="number" name="nCount" required>

        <button type="submit">Εμφάνιση</button>
    </form>
</div>

<!-- 5 updatePassengerStatus -->
<div class="form-section">
    <h2>5. Ενημέρωση Tier Επιβάτη</h2>

    <form action="/updatePassengerStatus" method="POST">
        <label>Όνομα Αεροπορικής:</label>
        <input type="text" name="airlineName" required>

        <label>Tier:</label>
        <select name="tier">
            <option value="Basic">Basic</option>
            <option value="Silver">Silver</option>
            <option value="Gold">Gold</option>
            <option value="Platinum">Platinum</option>
        </select>

        <button type="submit">Ενημέρωση</button>
    </form>
</div>

</body>
</html>