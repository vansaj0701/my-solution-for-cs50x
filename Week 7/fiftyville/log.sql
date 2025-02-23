-- Keep a log of any SQL queries you execute as you solve the mystery.


-- See descrition of crime scene
SELECT description FROM crime_scene_reports
WHERE
month=7 AND day=28
AND
street='Humphrey Street';


-- Find some clues to find thief
-- thief at parking lot
-- withdraw money from ATM
-- flight ticket to get out of Fiftyville
SELECT name, transcript FROM interviews
WHERE
month=7 AND day=28 AND year=2023;


-- Looking for license plate
-- Find some suspected license plate
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55
SELECT minute, activity, license_plate FROM bakery_security_logs
WHERE
year = 2023 AND month = 7 AND day = 28 AND hour = 10;


-- Getting account details for some clue
SELECT account_number, amount FROM atm_transactions
WHERE
year = 2023 AND month = 7 AND day = 28
AND
atm_location = 'Leggett Street'
AND
transaction_type = 'withdraw';



-- Checking Phone Calls for some clue
SELECT caller, receiver FROM phone_calls
WHERE
year = 2023 AND month = 7 AND day = 28 AND duration < 60;


-- Find where thief can go from Fiftyville
SELECT DISTINCT a.id, a.full_name, a.city AS destination FROM flights f
JOIN
airports a ON f.destination_airport_id = a.id
JOIN
airports origin ON f.origin_airport_id = origin.id
WHERE
origin.city = 'Fiftyville';


-- Find name of suspects through license_plate:-
-- Vanessa
-- Barry
-- Iman
-- Sofia
-- Luca
-- Diana
-- Kelsey
-- Bruce
SELECT name FROM people
WHERE
license_plate IN (
SELECT license_plate FROM bakery_security_logs
WHERE
year = 2023 AND month = 7 AND day = 28
AND
hour = 10 AND minute > 15 AND minute < 25
AND
activity = 'exit');


-- Find name of suspects through phone number:-
-- Kenny
-- Sofia
-- Benista
-- Taylor
-- Diana
-- Kelsey
-- Bruce
-- Carina
SELECT name FROM people
WHERE
phone_number IN (
SELECT caller FROM phone_calls
WHERE
year = 2023 AND month = 7 AND day = 28 AND duration < 60
);


-- Find common name of suspects between license plate and phone number
-- Bruce
-- Diana
-- Kelsey
-- Sofia
SELECT name FROM people
WHERE
license_plate IN (
SELECT license_plate FROM bakery_security_logs
WHERE
year = 2023 AND month = 7 AND day = 28
AND
hour = 10 AND minute > 15 AND minute < 25
AND
activity = 'exit')
INTERSECT
SELECT name FROM people
WHERE
phone_number IN (
SELECT caller FROM phone_calls
WHERE
year = 2023 AND month = 7 AND day = 28 AND duration < 60
);


-- Find name of suspects through id and account number:-
-- Bruce
-- Diana
-- Brooke
-- Kenny
-- Iman
-- Luca
-- Taylor
-- Benista
SELECT name FROM people
JOIN
bank_accounts ON bank_accounts.person_id = people.id
WHERE
bank_accounts.account_number IN (
SELECT account_number FROM atm_transactions
WHERE
year = 2023 AND month = 7 AND day = 28
AND
atm_location = 'Leggett Street'
AND
transaction_type = 'withdraw'
);


-- Narrowing down suspects list:-
-- Bruce
-- Diana
SELECT name FROM people
WHERE
license_plate IN (
SELECT license_plate FROM bakery_security_logs
WHERE
year = 2023 AND month = 7 AND day = 28
AND
hour = 10 AND minute > 15 AND minute < 25
AND
activity = 'exit')
INTERSECT
SELECT name FROM people
WHERE
phone_number IN (
SELECT caller FROM phone_calls
WHERE
year = 2023 AND month = 7 AND day = 28 AND duration < 60
)
INTERSECT
SELECT name FROM people
JOIN
bank_accounts ON bank_accounts.person_id = people.id
WHERE
bank_accounts.account_number IN (
SELECT account_number FROM atm_transactions
WHERE
year = 2023 AND month = 7 AND day = 28
AND
atm_location = 'Leggett Street'
AND
transaction_type = 'withdraw'
);


-- Get passport number of final suspects:-
-- Diana : 3592750733
-- Bruce : 5773159633
SELECT name, passport_number FROM people
WHERE
name IN ('Bruce', 'Diana');


-- Find thief
-- Bruce
-- Destination ID : 4
SELECT flights.destination_airport_id, people.name, flights.hour, flights.minute FROM flights
JOIN
passengers ON passengers.flight_id = flights.id
JOIN
people ON passengers.passport_number = people.passport_number
WHERE
flights.year = 2023 AND flights.month = 7 AND flights.day = 29
AND
people.name IN ('Bruce', 'Diana')
ORDER BY hour, minute
LIMIT 1;


-- Find the city the thief ESCAPED TO
-- New York City
SELECT city FROM airports
WHERE
id = 4;


-- Find accomplice of a thief
-- Robin
SELECT name
FROM people
WHERE phone_number IN (
SELECT receiver
FROM phone_calls
WHERE
year = 2023 AND month = 7 AND day = 28
AND
duration < 60
AND
caller IN (
SELECT phone_number
FROM people
WHERE name = 'Bruce'
)
);
