        SELECT (thief.name) AS 'suspected_thief_name', -- QUERY 3
            (accomplice.name) AS 'suspected_accomplice_name',
            (destination.city) AS 'flight destination'

        FROM people AS thief
            INNER JOIN bakery_security_logs AS bsl -- (A)
            ON bsl.license_plate = thief.license_plate
                AND bsl.year = 2021
                AND bsl.month = 7
                AND bsl.day = 28
                AND bsl.hour = 10
                AND bsl.minute BETWEEN 10 AND 20
                AND bsl.activity = 'exit'

            INNER JOIN bank_accounts AS bank -- (B)
            ON bank.person_id = thief.id
                AND bank.account_number IN (
                SELECT (atm.account_number)
                FROM atm_transactions AS atm
                WHERE atm.year = 2021
                    AND atm.month = 7
                    AND atm.day = 28
                    AND atm.atm_location = 'Leggett Street'
                    AND atm.transaction_type = 'withdraw' )

            INNER JOIN phone_calls AS ph -- (C)
            ON ph.caller = thief.phone_number
                AND ph.year = 2021
                AND ph.month = 7
                AND ph.day = 28
                AND ph.duration < 60

            INNER JOIN people AS accomplice
            ON accomplice.phone_number = ph.receiver

            INNER JOIN passengers AS pas -- (D)
            ON pas.passport_number = thief.passport_number

            INNER JOIN flights AS f
            ON f.id = pas.flight_id
                AND f.origin_airport_id = (
                    SELECT (id)
                    FROM airports
                    WHERE airports.city = 'Fiftyville'
                )

            INNER JOIN airports AS destination
            ON destination.id = f.destination_airport_id