-- 1. put the result into a variable
-- Authors list excluding the author(s) with most articles:

DECLARE @MaxArticles INT = (
SELECT TOP 1 COUNT(*) as Total_Articles 
FROM Article art INNER JOIN Author ath ON art.AuthorId = ath.AuthorId
GROUP BY ath.AuthorId, ath.Name
ORDER BY COUNT(*) DESC
)

SELECT ath.Name, ath.RegistrationDate, COUNT(*) as Total_Articles 
FROM Author ath INNER JOIN Article art ON ath.AuthorId = art.AuthorId
GROUP BY ath.Name, ath.RegistrationDate
HAVING COUNT(*) <> @MaxArticles



-- 2. NULL
-- 2.1. ISNULL – Replaces NULL with a specified replacement value
SELECT ISNULL (NULL, 3) NULLREPLACEMENT;
SELECT ISNULL (NULL,'GREEN') NULLREPLACEMENT;
SELECT ISNULL (NULL,'2018-12-25') NULLREPLACEMENT;

-- 2.2. NULLIF returns NULL if the values of the two arguments are equal
SELECT NULLIF(3,3) AS NULLIFF;
SELECT NULLIF(3,5) AS NULLIFF;
SELECT NULLIF('RED','RED') AS NULLIFF;
SELECT NULLIF('GREEN','RED') AS NULLIFF;

-- 2.3. COALESCE returns the first non-NULL value from the list provided
SELECT COALESCE (NULL,'','GREEN','','') AS NULLRESPONSE;
SELECT COALESCE (NULL,'GREEN','HOPE','') AS NULLRESPONSE;
SELECT COALESCE (1,'','GREEN','','') AS NULLRESPONSE;
