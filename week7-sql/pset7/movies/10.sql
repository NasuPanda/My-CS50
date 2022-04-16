-- 9.0以上のレーティングを受けた映画を監督したすべての人の名前をリストするS

SELECT name FROM people
JOIN directors ON directors.person_id = people.id
JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE ratings.rating >= 9.0;