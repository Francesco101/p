-- Keep a log of any SQL queries you execute as you solve the mystery.

-- I get the crime_scene_report ragarding the CS50 duck
    -- Knowing that the theft took place the day July 28, 2021 in 'Humphrey Street':
        SELECT (description) -- QUERY 1.0
        FROM crime_scene_reports
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND street = 'Humphrey Street';

    -- I then find out that there are two crime reports on that day and street
    -- I can select the correct one by reading the output table or select with an sql query:

        SELECT (description) -- QUERY 1.1
        FROM crime_scene_reports
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND street = 'Humphrey Street'
        AND description LIKE '%CS50 duck%'; -- I have seen that it is mentioned in the description from the first query (1.0)

    -- I find out, reading the crime report:
    --  that the crime happend at 10:15 am,
    --  that there are three witnesses to the crime,
    --  that all witnesses where interviewed on the very same day (July 28, 2021),
    --  that all witnesses mentioned the bakery.

    -- I then query the database for all the transcripts and name of witness
    --  of interviews carried out on July 28, 2021 and that mention the bakery.

        SELECT (name), -- QUERY 2
            (transcript)
        FROM interviews
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND transcript LIKE '%bakery%';

    -- Reading the three interviews I find out that:
    --  (A) Within 10 minutes from the theft, the thief got out of the bakery's parking lot by car;
    --  (B) On the same morning, before the theft, the thief withdrew money from an ATM in Leggett Street;
    --  (C) The thief called someone for less than a minute while leaving the bakery
    --  (D) In the call the thief asked to the other person to buy a ticket
    --    for the earliest flight out of Fiftyville the next morning (July 29, 2021)

    -- Intersect all informations (A, B, C, D) to find a list of suspects

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

        -- The output of QUERY 3 is a table containing all the suspects.
        -- In fact the table contains only one row,
        -- therefore I found the first and only suspect for the theft.

--        +----------------------+---------------------------+--------------------+
--        | suspected_thief_name | suspected_accomplice_name | flight destination |
--        +----------------------+---------------------------+--------------------+
--        | Bruce                | Robin                     | New York City      |
--        +----------------------+---------------------------+--------------------+