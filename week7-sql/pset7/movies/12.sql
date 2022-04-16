-- Johnny DeppとHelena Bonham Carterの両方が主演したすべての映画のタイトルをリストする

SELECT movies.title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Johnny Depp'
-- ↑Johny Deppが主演の映画をSELECT
-- ↓Johny Deppが主演の映画の中から、Helena Bonham Carterも主演の映画をSELECT
AND title IN (
SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Helena Bonham Carter'
);