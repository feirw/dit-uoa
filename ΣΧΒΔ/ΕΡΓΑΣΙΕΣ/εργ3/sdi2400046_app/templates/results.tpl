<!DOCTYPE html>
<html lang="el">
<head>
    <meta charset="UTF-8">
    <title>{{title}}</title>
    <style>
        body {
            font-family: sans-serif;
            margin: 40px;
            line-height: 1.6;
            background: #fff0f6;
            color: #5c2d4a;
        }

        h1 {
            color: #c2185b;
        }

        table {
            border-collapse: collapse;
            width: 100%;
            margin-top: 20px;
            background: #fffafc;
            border-radius: 8px;
            overflow: hidden;
            box-shadow: 0 2px 8px rgba(233, 30, 99, 0.08);
        }

        th, td {
            border: 1px solid #f8bbd0;
            padding: 12px;
            text-align: left;
        }

        th {
            background-color: #e91e63;
            color: white;
        }

        tr:nth-child(even) {
            background-color: #fce4ec;
        }

        .back-link {
            display: inline-block;
            margin-top: 20px;
            text-decoration: none;
            color: #c2185b;
            font-weight: bold;
        }

        .back-link:hover {
            color: #880e4f;
        }

        .error-box {
            color: #880e4f;
            font-weight: bold;
        }

        pre {
            background: #fce4ec;
            padding: 12px;
            border: 1px solid #f8bbd0;
            border-radius: 5px;
        }
    </style>
</head>
<body>
    <!--Σφάλμα σύνδεσης με την βάση -->
    <h1>{{title}}</h1>

    % if connection_error:
        <p class="error-box">Σφάλμα σύνδεσης στη βάση: {{connection_error}}</p>
        <p>Έλεγξε ότι τρέχει η MySQL, ότι υπάρχει η βάση <code>flights</code> και ότι έχεις ορίσει το password, π.χ. στο PowerShell πριν το <code>python app.py</code>:</p>
        <pre>$env:MYSQL_PASSWORD = "το_password_σου"</pre>
    % elif rows:
        <table>
            <thead>
                <tr>
                    % for key in rows[0].keys():
                        <th>{{key}}</th>
                    % end
                </tr>
            </thead>
            <tbody>
                % for row in rows:
                    <tr>
                        % for val in row.values():
                            <td>{{val}}</td>
                        % end
                    </tr>
                % end
            </tbody>
        </table>
    % else:
        <p>Δεν βρέθηκαν αποτελέσματα για τα κριτήρια που έβαλες (ή λάθος ηλικίες).</p>
    % end

    <a href="/" class="back-link">← Επιστροφή στο Μενού</a>
</body>
</html>
