SELECT DISTINCT (people.name)
FROM (
    (
        SELECT (stars.movie_id) AS film_id
        FROM stars
        JOIN people ON stars.person_id = people.id
        WHERE people.name = 'Kevin Bacon'
        AND people.birth = 1958
    )
    JOIN stars ON stars.movie_id = film_id
    JOIN people ON people.id = stars.person_id
)
WHERE people.name != 'Kevin Bacon';