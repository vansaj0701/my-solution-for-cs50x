SELECT title FROM movies
JOIN
stars AS stars1 ON movies.id = stars1.movie_id
JOIN
people AS person1 ON stars1.person_id = person1.id
JOIN
stars AS stars2 ON movies.id = stars2.movie_id
JOIN
people AS person2 ON stars2.person_id = person2.id
WHERE
person1.name = 'Bradley Cooper'
AND
person2.name = 'Jennifer Lawrence';
