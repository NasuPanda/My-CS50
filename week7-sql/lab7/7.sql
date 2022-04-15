-- Drakeの曲の平均エネルギーを返す

SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = "Drake");