-- ダンサビリティ、エネルギー、バレンスが0.75を超える曲の名前をリストする

SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;