-- Declaring the Student cursor to rename all tables by adding ‘_backup’ 

USE UniversityV3
GO

DECLARE @TableName VARCHAR(50),
        @NewTableName VARCHAR(50)

DECLARE Student_Cursor CURSOR FOR 
SELECT T.TABLE_NAME FROM INFORMATION_SCHEMA.TABLES T;

OPEN Student_Cursor
FETCH NEXT FROM Student_Cursor INTO @TableName
WHILE @@FETCH_STATUS = 0
BEGIN
  IF RIGHT(@TableName, 6) <> 'Backup'
  BEGIN
    SET @NewTableName = @TableName + '_Backup'    -- SET @NewTableName = SUBSTRING(@TableName, 1, LEN(@TableName)-7)  [to remove]
    EXEC sp_rename @TableName, @NewTableName
  END
ELSE
PRINT 'Backup table name already exists: '+@TABLENAME
FETCH NEXT FROM Student_Cursor INTO @TableName
END
CLOSE Student_Cursor 
DEALLOCATE Student_Cursor 



-- Declare Student cursor with variables to process 2 columns from a table (concatenating their string values)
USE UniversityV3
GO

DECLARE @StudentId INT,
        @StudentName VARCHAR(40)
DECLARE Student_Cursor CURSOR FOR SELECT 
  StudentId, 
  Name
FROM dbo.Student;
OPEN Student_Cursor
FETCH NEXT FROM Student_Cursor INTO @StudentId, @StudentName -- Fetch first row and store it into variables
WHILE @@FETCH_STATUS = 0
BEGIN
PRINT CONCAT(@StudentId, '--', @StudentName) -- Show variables data
FETCH NEXT FROM Student_Cursor -- Get next row data into cursor and store it into variables
INTO @StudentId, @StudentName
END
CLOSE Student_Cursor 
DEALLOCATE Student_Cursor 
