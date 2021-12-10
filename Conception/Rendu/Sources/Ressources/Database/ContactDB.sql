/*
***** INFORMATIONS *****

Project : CDAA-R
Author : Samuel LACHAUD
CreationDate : 07/10/2021
LatestUpdate : 05/12/2021
Brief : This SQL file is linked to the Qt project named CDAA-R,
which allows to graphically manage a SQLite database created from this SQL file.

***** SQLITE3 COMMANDS *****

Export .SQL to .DB file in SQLITE3 :
    sqlite3 <filename.db> ".read <filename.sql>"
    You can now open .DB file in "DB Browser For SQLite" program
Open .DB file in SQLITE3 :
    sqlite3 <filename.db>
*/
-------------------------
----- CREATION PART -----
-------------------------
CREATE TABLE IF NOT EXISTS CONTACT(
    contactId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    contactFirstName VARCHAR(50) NOT NULL,
    contactLastName VARCHAR(50) NOT NULL,
    contactEntreprise VARCHAR(50),
    contactMail VARCHAR(50),
    contactPhone VARCHAR(15), -- longest phone number worldwide
    contactPicture BLOB,  -- to stock Base64(data) image
    contactCreationDate TEXT);

CREATE TABLE IF NOT EXISTS INTERACTION(
    interactionId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    interactionTitle VARCHAR(50),
    interactionContent TEXT,
    interactionDate TEXT,
    contactId INT NOT NULL); -- multiple interaction possible for contact

CREATE TABLE IF NOT EXISTS LOGS(
    logsLinePosition INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    logsValue VARCHAR(50));

CREATE TABLE IF NOT EXISTS TAGS(
    tagId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, -- it's the row in tagsInteraction
    tagTodo TEXT,
    tagDate VARCHAR(10), -- 10 chars for xx/xx/xxxx
    interactionId INT NOT NULL); -- multiple tags possible for interaction

-----------------------
----- INSERT PART -----
-----------------------

INSERT INTO CONTACT
(
    contactId,
    contactFirstName,
    contactLastName,
    contactEntreprise,
    contactMail,
    contactPhone,
    contactPicture,
    contactCreationDate
)
VALUES
    (
        0,
		"Charles",
        "Jorais",
        "LIB",
        "CJ@mail.com",
        "0620158917",
        "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",
        "2021-08-10 11:12:13"
    ),
    (
        1,
        "Marion",
        "Hune",
        "LIB",
        "MH@mail.com",
        "0726274586",
        "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",
        "2010-05-06 16:00:00"
    ),
    (
        2,
		"Roger",
        "Baunne",
        "Université de Bourgogne",
        "RB@mail.com",
        "0880264578",
        "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",
        "2011-10-02 01:00:45"
    ),

    (
        3,
		"Viviane",
        "Nothe",
        "AIVA",
        "VN@mail.com",
        "0985864578",
        "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",
        "2021-09-02 16:47:00"
    ),
    (
        4,
		"Baptiste",
        "Nothe",
        "GitHub",
        "TN@mail.com",
        "0910154586",
        "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",
        "2019-01-01 00:00:01"
    );

INSERT INTO INTERACTION
(
    interactionId,
    interactionTitle,
    interactionContent,
    interactionDate,
    contactId
)
VALUES
    (
        0,
        "Faire une Raclette",
        "@todo faire une raclette @date 08/10/2021",
        "2021-10-06 08:00:00",
        1
    ),

    (
        1,
        "Faire une Tartiflette",
        "@todo faire une tartiflette @date 09/10/2021",
        "2021-10-07 08:00:00",
        2
    ),

    (
        2,
        "Regarder My Little Pony",
        "@todo regarder my little pony avec mes amis @date 10/10/2021",
        "2021-10-08 08:00:00",
        2
    ),

    (
        3,
        "Travailler sur le projet",
        "@todo Travailler sur le projet de CDAA @date 02/12/2021",
        "2021-10-09 08:00:00",
        3
    ),

    (
        4,
        "Révision voiture",
        "@todo Emmener la voiture faire sa révision @date 10/12/2021",
        "2021-10-10 08:00:00",
        3
    ),

    (
        5,
        "Acheter Raclette",
        "@todo Acheter de la raclette pour fêter la fin du projet CDAA-R (signification : CDAA-Raclette) @date 15/12/2021",
        "2021-10-11 08:00:00",
        3
    ),

    (
        6,
        "Acheter sucreries",
        "@todo Acheter sucrerie pour combler notre chargin suite à la mauvaise note en CDAA @date 23/12/2021",
        "2021-10-12 08:00:00",
        4
    ),

    (
        7,
        "Acheter Yoat",
        "@todo Acheter un Yoat suite aux revenu du mondialement connu 'Projet CDAA-R' @date 01/04/2022",
        "2021-10-13 08:00:00",
        4
    ),

    (
        8,
        "RDV Important",
        "@todo Rendez-vous important pour le rachat de CDAA-R par MICROSOFT @date 10/04/2022",
        "2021-10-14 08:00:00",
        4
    ),

    (
        9,
        "Développement d'une nouvelle application",
        "@todo Commencer le développement de la nouvelle application CDAA-R-2 avec micro-transactions et toujours aussi peu de contenu @date 22/06/2022",
        "2021-10-15 08:00:00",
        4
    );



INSERT INTO LOGS
(
    logsLinePosition,
    logsValue
)
VALUES
    (
        0,
        "(06/05/2010 16:00:00)
Contact Added"
    ),

    (
        1,
        "(02/10/2011 01:00:45)
Contact Added"
    ),

    (
        2,
        "(01/01/2019 00:00:01)
Contact Added"
    ),

    (
        3,
        "(10/08/2021 11:12:13)
Contact Added"
    ),

    (
        4,
        "(02/09/2021 16:47:00)
Contact Added"
    ),

    (
        5,
        "(06/10/2021 08:00:00)
Interaction Added"
    ),

    (
        6,
        "(07/10/2021 08:00:00)
Interaction Added"
    ),

    (
        7,
        "(08/10/2021 08:00:00)
Interaction Added"
    ),

    (
        8,
        "(09/10/2021 08:00:00)
Interaction Added"
    ),

    (
        9,
        "(10/10/2021 08:00:00)
Interaction Added"
    ),

    (
        10,
        "(11/10/2021 08:00:00)
Interaction Added"
    ),

    (
        11,
        "(12/10/2021 08:00:00)
Interaction Added"
    ),

    (
        12,
        "(13/10/2021 08:00:00)
Interaction Added"
    ),

    (
        13,
        "(14/10/2021 08:00:00)
Interaction Added"
    ),

    (
        14,
        "(15/10/2021 08:00:00)
Interaction Added"
    );

INSERT INTO TAGS
(
    tagId,
    tagTodo,
    tagDate,
    interactionId
)
VALUES
    (
      0,
      "faire une raclette",
      "08/10/2021",
      0
    ),

    (
      1,
      "faire une tartiflette",
      "09/10/2021",
      1
    ),

    (
      2,
      "regarder my little pony avec mes amis",
      "10/10/2021",
      2
    ),
    (
      3,
      "Travailler sur le projet de CDAA",
      "02/12/2021",
      3
    ),

    (
      4,
      "Emmener la voiture faire sa révision",
      "10/12/2021",
      4
    ),

    (
      5,
      "Acheter de la raclette pour fêter la fin du projet CDAA-R (signification : CDAA-Raclette)",
      "15/12/2021",
      5
    ),

    (
      6,
      "Acheter sucrerie pour combler notre chargin suite à la mauvaise note en CDAA",
      "23/12/2021",
      6
    ),

    (
      7,
      "Acheter un Yoat suite aux revenu du mondialement connu 'Projet CDAA-R'",
      "01/04/2022",
      7
    ),

    (
      8,
      "Rendez-vous important pour le rachat de CDAA-R par MICROSOFT",
      "10/04/2022",
      8
    ),

    (
      9,
      "Commencer le développement de la nouvelle application CDAA-R-2 avec micro-transactions et toujours aussi peu de contenu",
      "22/06/2022",
      9
    );
