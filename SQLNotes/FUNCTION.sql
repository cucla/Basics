-- A table-evaluated function - accepts parameter(s) and returns the result set in the table variable
   -- 1. It can be executed within the Select query.
   -- 2. It can be used in multiple parts of a query, e.g.g in the Case statement, where/having clauses.
   -- 3. The output of a table-valued function is a recordset, hence you can join the function with tables.
   
CREATE FUNCTION GETEMPLOYEESBYHIREDATE (@FROMDATE AS DATETIME, @TODATE AS DATETIME) 
RETURNS @EMPLOYEES TABLE ( 
  EMPLOYEENAME VARCHAR (MAX), 
  BIRTHDATE    DATETIME, 
  JOBTITLE     VARCHAR(150), 
  EMAILID      VARCHAR(100), 
  PHONENUMBER  VARCHAR(20), 
  HIREDATE     DATETIME ) 
AS 
  BEGIN 
      INSERT INTO @EMPLOYEES 
      SELECT ( ISNULL( B.FIRSTNAME, '') + ' ' 
               + ISNULL( B.MIDDLENAME, '') + ' ' 
               + ISNULL( B.LASTNAME, '') )AS EMPLOYEENAME, 
             A.BIRTHDATE, 
             B.JOBTITLE, 
             B.EMAILADDRESS, 
             B.PHONENUMBER, 
             A.HIREDATE 
      FROM   [HUMANRESOURCES].[EMPLOYEE] A 
             INNER JOIN [HUMANRESOURCES].[VEMPLOYEE] B 
                     ON A.BUSINESSENTITYID = B.BUSINESSENTITYID 
      WHERE  A.HIREDATE BETWEEN @FROMDATE AND @TODATE 
      
      RETURN 
  END
  
  
-- 1.1. To get a list

DECLARE @FROMDT DATETIME 
DECLARE @TODT DATETIME 
SET @FROMDT='2009-01-01' 
SET @TODT='2009-12-31' 

SELECT * FROM GETEMPLOYEESBYHIREDATE(@FROMDT, @TODT)

-- 1.2. Store into table

DECLARE @FROMDT DATETIME 
DECLARE @TODT DATETIME 

SET @FROMDT='2009-01-01' 
SET @TODT='2009-12-31' 

INSERT INTO TBLEMPLOYEES 
SELECT EMPLOYEENAME, 
       BIRTHDATE, 
       JOBTITLE, 
       EMAILID, 
       PHONENUMBER, 
       HIREDATE 
FROM GETEMPLOYEESBYHIREDATE(@FROMDT, @TODT)



-- Joining a table with a table-evaluated function

CREATE TABLE [DBO].[DEPARTMENT] 
  ( 
     [DEPARTMENTID]   INT IDENTITY (1, 1), 
     [DEPARTMENTNAME] [VARCHAR](MAX) NULL 
  ) 
                       
CREATE FUNCTION Getemployeesbydepartment (@DEPARTMENTID INT) 
RETURNS @EMPLOYEES TABLE ( 
  EMPLOYEENAME   VARCHAR (MAX), 
  BIRTHDATE      DATETIME, 
  JOBTITLE       VARCHAR(150), 
  EMAILID        VARCHAR(100), 
  PHONENUMBER    VARCHAR(20), 
  HIREDATE       DATETIME, 
  DEPARTMENTID VARCHAR(500)) 
AS 
  BEGIN 
      INSERT INTO @EMPLOYEES 
      SELECT A.EMPLOYEENAME, 
             A.BIRTHDATE, 
             A.JOBTITLE, 
             A.EMAILID, 
             A.PHONENUMBER, 
             A.HIREDATE, 
             A.DEPARTMENTID 
      FROM   [EMPLOYEES] A 
      WHERE  A.DEPARTMENTID = @DEPARTMENTID 

      RETURN 
  END
                  
-- CROSS APPLY, like inner join:                      
SELECT A.[EMPLOYEENAME], 
       A.[BIRTHDATE], 
       A.[JOBTITLE], 
       A.[EMAILID], 
       A.[PHONENUMBER], 
       A.[HIREDATE], 
       B.[DEPARTMENTNAME] 
FROM   DEPARTMENT B 
       CROSS APPLY GETEMPLOYEESBYDEPARTMENT(B.DEPARTMENTID) A

-- OUTER APPLY, like left join:
SELECT A.[EMPLOYEENAME], 
       A.[BIRTHDATE], 
       A.[JOBTITLE], 
       A.[EMAILID], 
       A.[PHONENUMBER], 
       A.[HIREDATE], 
       B.[DEPARTMENTNAME] 
FROM   DEPARTMENT B 
       OUTER APPLY GETEMPLOYEESBYDEPARTMENT(B.DEPARTMENTID) A

