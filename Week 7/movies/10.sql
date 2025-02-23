SELECT DISTINCT people.name FROM ratings JOIN movies ON ratings.movie_id = movies.id JOIN directors ON movies.id = directors.movie_id JOIN people ON directors.person_id = people.id WHERE ratings.rating >= 9.0;
