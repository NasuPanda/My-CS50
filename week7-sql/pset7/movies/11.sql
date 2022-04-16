-- Chadwick Bosemanが主演した映画の評価の高い順に5つのタイトルをリスト

SELECT movies.title FROM movies
JOIN stars ON stars.movie_id = movies_id
    JOIN people ON stars.person_id = people.id -- イメージ的にはここがネストしているような感じ
JOIN ratings on ratings.movie_id = movies.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;