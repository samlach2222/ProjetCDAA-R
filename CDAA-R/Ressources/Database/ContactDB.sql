/*
***** INFORMATIONS *****

Project : CDAA-R
Author : Samuel LACHAUD
CreationDate : 07/10/2021
LatestUpdate : 08/10/2021
Brief : This SQL file is linked to the QT project named CDAA-R,
which allows to graphically manage a SQLite database created from this SQL file.

***** SQLITE3 COMMANDS *****

Open .SQL file in SQLITE3 :
    sqlite3 .read <filename.sql>
Export .SQL to .DB file in SQLITE3 :
    sqlite3 <filename.db> ".read <filename.sql>"
    You can now open .DB file in "DB Browser For SQLite" program
*/

CREATE TABLE IF NOT EXISTS CONTACT(
    contactId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    contactFirstName VARCHAR(50) NOT NULL,
    contactLastName VARCHAR(50) NOT NULL,
    contactEntreprise VARCHAR(50),
    contactMail VARCHAR(50),
    contactPhone VARCHAR(15), -- longest phone number worldwide
    contactPicture BLOB,  -- to stock Base64 image
    contactCreationDate VARCHAR(19), -- 19 chars for xx/xx/xxxx xx:xx:xx
    age INT DEFAULT NULL);

CREATE TABLE IF NOT EXISTS INTERACTION(
    interactionId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    interactionTitle VARCHAR(50),
    interactionContent TEXT,
    interactionDate VARCHAR(19), -- 19 chars for xx/xx/xxxx xx:xx:xx
    contactId INT NOT NULL); -- multiple interaction possible for contact

CREATE TABLE IF NOT EXISTS LOGS(
    logsLinePosition INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    logsValue VARCHAR(50));

CREATE TABLE IF NOT EXISTS TAGS(
    tagId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, -- it's the row in tagsInteraction
    tagTodo TEXT,
    tagDate VARCHAR(10), -- 10 chars for xx/xx/xxxx
    interactionId INT NOT NULL); -- multiple tags possible for interaction
