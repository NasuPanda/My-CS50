-- 他のアーティストをフィーチャーした曲の名前をリストする
-- 他のアーティストをフィーチャーした曲には 「feat」が曲の名前の中に含まれます。

SELECT name FROM songs WHERE name LIKE '%feat%';