CREATE TABLE STUDENTS 
  ( 
     ID        	    INT           IDENTITY(1, 1)    PRIMARY KEY, 
     FIRSTNAME 	    VARCHAR(250), 
     LASTNAME  	    VARCHAR(250), 
     ADMISSIONDATE  DATETIME,
     GRADE     	    CHAR(1) 
  ) 
  
INSERT INTO STUDENTS 
VALUES      ('NISARG', 'UPADHYAY', '2018-09-11', 'A'), 
            ('RAGHAV', 'DATTA', '2017-10-01', 'A'), 
            ('KIRAN', 'AMIN', '2016-01-31', 'A')
            
