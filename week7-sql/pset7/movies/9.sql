-- 2004年に公開された映画に主演したすべての人の名前を、誕生年順にリストする

SELECT name, birth FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies on stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth;