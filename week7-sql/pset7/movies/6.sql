-- 2012年にリリースされたすべての映画の平均レーティングを決定する

SELECT AVG(rating) FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE year = 2012;