-- すべてのハリー・ポッター映画のタイトルと公開年を時系列でリストする

SELECT year, title FROM movies
WHERE title LIKE 'Harry Potter%'
ORDER BY year;