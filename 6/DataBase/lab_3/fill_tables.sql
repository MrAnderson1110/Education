INSERT INTO authors (author_name, author_surname) 
VALUES ('Иван', 'Иванов'), ('Андрей', 'Андреев'), ('Сергей', 'Сергеев'), ('Евгений', 'Краснов');

# ------------------------------------------------------------ #

INSERT INTO graphs (graph_name, author_id)
VALUES (
	'Граф 1',
	(
		SELECT author_id 
		FROM authors as au
		WHERE au.author_name = 'Иван' AND au.author_surname = 'Иванов'
	)
), (
	'Граф 2',
	(		
		SELECT author_id 
		FROM authors as au
		WHERE au.author_name = 'Андрей' AND au.author_surname = 'Андреев'
	)
), (
	'Граф 3',
	(
		SELECT author_id 
		FROM authors as au
		WHERE au.author_name = 'Сергей' AND au.author_surname = 'Сергеев'
	)
), (
	'Граф 4', 
	(
		SELECT author_id 
		FROM authors as au
		WHERE au.author_name = 'Евгений' AND au.author_surname = 'Краснов'
	)
);

# ------------------------------------------------------------ #

INSERT INTO vertexes (vertex_name, top_left_x, top_left_y, vert_size, graph_id)
VALUES 
(
	'Содержит отказ', 1, 10, 15, 
	(SELECT graph_id FROM graphs WHERE graph_name = 'Граф 1')
), (
	'Вершина 4', 13, 8, 6, 
	(SELECT graph_id FROM graphs WHERE graph_name = 'Граф 1')
), (
	'Содержит отказ, но не заканчивается им', 0, 6, 10, 
	(SELECT graph_id FROM graphs WHERE graph_name = 'Граф 2')
), (
	'Вершина 5', 2, 0, 3, 
	(SELECT graph_id FROM graphs WHERE graph_name = 'Граф 2')
), (
	'Отказ содержит в начале', 5, 0, 66, 
	(SELECT graph_id FROM graphs WHERE graph_name = 'Граф 3')
), (
	'Вершина 2', 2, 44, 34, 
	(SELECT graph_id FROM graphs WHERE graph_name = 'Граф 3')
), (
	'Вершина 3', 6, 2, 1, 
	(SELECT graph_id FROM graphs WHERE graph_name = 'Граф 3')
), (
	'Вершина 1', 4, 2, 2, 
	(SELECT graph_id FROM graphs WHERE graph_name = 'Граф 4')
), (
	'Вершина, со словом ошибка', 3, 1, 32, 
	(SELECT graph_id FROM graphs WHERE graph_name = 'Граф 4')
), (
	'Вершина 6', 5, 2, 1, 
	(SELECT graph_id FROM graphs WHERE graph_name = 'Граф 4')
);

# ------------------------------------------------------------ #

INSERT INTO vertex_identity (start_vertex, end_vertex)
VALUES 
(
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Содержит отказ'), 
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Вершина 4')
), (
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Вершина 4'), 
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Содержит отказ')
), (
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Содержит отказ, но не заканчивается им'), 
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Вершина 5')
), (
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Отказ содержит в начале'), 
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Отказ содержит в начале')
), (
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Отказ содержит в начале'), 
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Вершина 2')
), (
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Отказ содержит в начале'), 
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Вершина 3')
), (
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Вершина 3'), 
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Отказ содержит в начале')
), (
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Вершина, со словом ошибка'),
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Вершина 1')
), (
	(SELECT vertex_id FROM vertexes WHERE vertex_name = 'Вершина 6'), 
	NULL
);
