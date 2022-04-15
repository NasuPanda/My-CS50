-- 最も長い曲の上位5曲の名前を長さの降順でリストする

SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;