USE vertexes

DROP TABLE IF EXISTS vertexes;
DESC vertexes;

DROP TABLE IF EXISTS vertex_params;
DESC vertex_params;

DROP TABLE IF EXISTS author;
DESC author;

CREATE TABLE IF NOT EXISTS vertex_params (
	params_id 				INT unsigned NOT NULL AUTO_INCREMENT,		# unique id
	top_left_x				REAL NOT NULL,					# x of top left corner
	top_left_y				REAL NOT NULL,					# y of top left corner
	vert_size				INT NOT NULL,					# size of vertex
	PRIMARY KEY (params_id)	
);

DESC vertex_params;

CREATE TABLE IF NOT EXISTS author (
	author_id				INT unsigned NOT NULL AUTO_INCREMENT,		# unique id
	name					VARCHAR(50) NOT NULL,				# author name
	surname				VARCHAR(50) NOT NULL,				# author surname
	PRIMARY KEY (author_id)			
);

DESC author;

CREATE TABLE IF NOT EXISTS vertexes (
	vertex_id 				INT unsigned NOT NULL AUTO_INCREMENT,		# unique id
	name 					VARCHAR(50) NOT NULL,				# vertex name
	vertex_params_id			INT unsigned NOT NULL,				# vertex parameters table id
	author_id				INT unsigned DEFAULT NULL,			# author table id
	PRIMARY KEY(vertex_id),
	
	FOREIGN KEY (vertex_params_id) 
		REFERENCES 
		vertex_params(params_id),
		
	FOREIGN KEY (author_id) 		
		REFERENCES
		author(author_id)
);

DESC vertexes;	


# fill vertex params table

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (0.1, 1.32, 10);

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (1.31, 2.61, 1);

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (3.14, 14.1, 15);

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (14.5, 1.1, 6);

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (5.1, 6.6, 11);

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (9.2, 15.15, 43);

SELECT * FROM vertex_params;

# fill author table

INSERT INTO author (name, surname)
VALUES ('Ivan', 'Ivanov');

INSERT INTO author (name, surname)
VALUES ('Andrew', 'Andreev');

INSERT INTO author (name, surname)
VALUES ('Sergey', 'Sergeev');

INSERT INTO author (name, surname)
VALUES ('Artem', 'Bazhenov');

INSERT INTO author (name, surname)
VALUES ('Dmitry', 'Andreev');

INSERT INTO author (name, surname)
VALUES ('Denis', 'Maximov');

SELECT * FROM author;

# fill vertexes table

DROP FUNCTION IF EXISTS get_vertex_params_id;

CREATE FUNCTION get_vertex_params_id(tlx REAL, tly REAL, s INT)
RETURNS INT
BEGIN
	DECLARE params_table_id INT DEFAULT NULL;
	SET params_table_id = (
		SELECT params_id 
		FROM vertex_params
		WHERE top_left_x = tlx AND top_left_y = tly AND vert_size = S
	);
	IF params_table_id = NULL THEN
		INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
		VALUES (tlx, tly, s);
	
	RETURN (
		SELECT params_id 
		FROM vertex_params
		WHERE top_left_x = tlx AND top_left_y = tly AND vert_size = s
	);
END
		

DROP FUNCTION IF EXISTS add_vertex;

DELIMITER //
CREATE FUNCTION add_vertex(vn VARCHAR(50), tlx REAL, tly REAL, s INT, an VARCHAR(50), asn VARCHAR(50))
RETURNS INT
BEGIN
	DECLARE params_table_id INT DEFAULT NULL;
	SET params_table_id = get_vertex_params_id(tlx, tly, s);
		
	DECLARE author_table_id INT DEFAULT NULL;
	SET author_table_id = (
		SELECT author_id
		FROM author
		WHERE name = an AND surname = asn
	);
		
	IF author_table_id = NULL THEN (
		INSERT INTO author (name, surname)
		VALUES (an, asn);
		SET author_table_id = (
			SELECT author_id
			FROM author
			WHERE name = an AND surname = asn
		);
	);
		
	INSERT INTO vertexes (name, vertex_params_id, author_id)
	VALUES (vn, params_table_id, author_table_id);
	
	RETURN NULL;
END //
DELIMITER ;
	
add_vertex('vert_name', 1.31, 2.61, 1, 'Ivan', 'Ivanov');


	
SELECT * FROM vertexes;
