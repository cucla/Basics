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
