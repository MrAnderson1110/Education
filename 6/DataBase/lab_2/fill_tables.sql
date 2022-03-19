USE vertexes

# fill vertex params table

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (0.1, 1.32, 10);

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (1,31, 2.61, 1);

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (3.14, 14.1, 15);

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (14.5, 1.1, 6);

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (5.1, 6.6, 11);

INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
VALUES (9.2, 15.15, 43);

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

# fill vertexes table

INSERT INTO author (name, vertex_params_id, author_id)
	(
	 "some_vert_1", 
	 SELECT params_id FROM vertex_params WHERE top_left_x = 0.1 LIMIT 1,
	 SELECT author_id FROM author WHERE name = 'Ivan' LIMIT 1
	)
