WITH both_movies AS
(
    SELECT movie_id FROM people
    INNER JOIN stars ON people.id = stars.person_id
    WHERE people.name = "Johnny Depp"
    
    INTERSECT
    
    SELECT movie_id FROM people
    INNER JOIN stars ON people.id = stars.person_id
    WHERE people.name = "Helena Bonham Carter"
    
)

SELECT movies.title
FROM movies
INNER JOIN both_movies ON both_movies.movie_id = movies.id