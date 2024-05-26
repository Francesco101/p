SELECT DISTINCT (movies.title) AS 'titolo',
    (director_name) AS 'regista',
    (movies.year) AS 'anno',
    (ratings.rating) AS 'rating'

FROM people
JOIN movies ON movies.id = stars.movie_id
LEFT JOIN stars ON stars.person_id = people.id
LEFT JOIN ratings ON ratings.movie_id = movies.id
LEFT JOIN (
    SELECT (people.name) AS director_name,
        (movies.id) AS film_id
    FROM directors
    JOIN people ON people.id = directors.person_id
    JOIN movies ON movies.id = directors.movie_id
) ON film_id = movies.id

WHERE people.name = 'Checco Zalone'
ORDER BY movies.year ASC;
