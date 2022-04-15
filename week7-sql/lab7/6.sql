-- Post Maloneの曲の名前をリストする

SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = "Post Malone");