SELECT (movies.title)
FROM (
        (
        SELECT (stars.movie_id) AS helenas_movie_id
        FROM people
        JOIN stars ON stars.person_id = people.id
        WHERE people.name = 'Helena Bonham Carter'
    )
    JOIN (
        SELECT (stars.movie_id) AS both_movie_id
        FROM people
        JOIN stars ON stars.person_id = people.id
        WHERE people.name = 'Johnny Depp'
    ) ON both_movie_id = helenas_movie_id

    JOIN movies ON movies.id = both_movie_id
);
