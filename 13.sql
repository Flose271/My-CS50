WITH bacon_movies AS
(
    SELECT movie_id FROM people
    INNER JOIN stars ON people.id = stars.person_id
    WHERE people.name = "Kevin Bacon"
    AND people.birth = 1958
)

SELECT DISTINCT(people.name)
FROM people
INNER JOIN stars ON stars.person_id = people.id
WHERE stars.movie_id IN bacon_movies
AND NOT (people.name = "Kevin Bacon" AND people.birth = 1958)