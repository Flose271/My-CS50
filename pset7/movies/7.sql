SELECT m.title, r.rating
FROM movies m
INNER JOIN ratings r ON m.id = r.movie_id
WHERE m.year = 2010
ORDER BY 2 DESC,1