SELECT p.name
FROM directors d
INNER JOIN people p ON p.id = d.person_id
INNER JOIN ratings r ON r.movie_id = d.movie_id
GROUP BY p.id
HAVING MAX(r.rating) >= 9.0