-- Create sample database (SQLDevBlog)
CREATE DATABASE SQLDevBlogV2;
GO

USE SQLDevBlogV2;

CREATE TABLE Author (
  AuthorId          INT            PRIMARY KEY         IDENTITY (1, 1),
  Name              VARCHAR(40),
  RegistrationDate  DATETIME2,
  Notes             VARCHAR(400)
)

CREATE TABLE Category (
  CategoryId        INT            PRIMARY KEY         IDENTITY (1, 1),
  Name              VARCHAR(50),
  Notes             VARCHAR(400)
)

CREATE TABLE Article (
  ArticleId         INT            PRIMARY KEY         IDENTITY (1, 1),
  CategoryId        INT,
  AuthorId          INT,
  Title             VARCHAR(150),
  Published         DATETIME2,
  Notes             VARCHAR(400)  
)

-- Adding foreign keys for author and article category
ALTER TABLE Article ADD CONSTRAINT FK_Category_CategoryId FOREIGN KEY (CategoryId) REFERENCES Category (CategoryId)
ALTER TABLE Article ADD CONSTRAINT FK_Author_AuthorId FOREIGN KEY (AuthorId) REFERENCES Author (AuthorId)

GO

INSERT INTO Author (Name, RegistrationDate, Notes)
  VALUES ('Sam', '2017-01-01', 'Database Analyst'),
         ('Asif', '2017-01-02', 'Database and Business Intelligence Developer'),
         ('Sadaf', '2018-01-01', 'Database Analyst Programmer')

INSERT INTO Category (Name, Notes)
  VALUES ('Development', 'Articles about database development'),
         ('Testing', 'Database testing related articles'),
         ('DLM', 'Database lifecycle management')

INSERT INTO Article (CategoryId, AuthorId, Title, Published, Notes)
  VALUES (1, 1, 'Fundamentals of SQL Database Development', '02-01-2018', ''),
         (1, 2, 'Advanced Database Development', '02-01-2018', ''),
         (2, 3, 'All About Database Testing', '03-01-2018', '');
GO
