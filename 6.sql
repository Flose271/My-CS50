SELECT AVG(r.rating)
FROM ratings r
INNER JOIN movies m ON m.id = r.movie_id
GROUP BY(m.year)
HAVING m.year = 2012