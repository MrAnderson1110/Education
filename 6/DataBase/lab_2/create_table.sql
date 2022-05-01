DROP TABLE IF EXISTS vertex_params;
CREATE TABLE IF NOT EXISTS vertex_params (
	params_id serial NOT NULL,
	top_left_x real NOT NULL,
	top_left_y real NOT NULL,
	vert_size integer NOT NULL,	
	PRIMARY KEY (params_id)	
);

DROP TABLE IF EXISTS authors;
CREATE TABLE IF NOT EXISTS authors (
	author_id serial NOT NULL,
	author_name varchar(50) NOT NULL,
	author_surname varchar(50) DEFAULT NULL,	
	PRIMARY KEY (author_id)			
);

DROP TABLE IF EXISTS graphs;
CREATE TABLE IF NOT EXISTS graphs (
	graph_name varchar(50) NOT NULL UNIQUE,
	author_id integer DEFAULT NULL,	
	PRIMARY KEY (graph_name),	
	FOREIGN KEY (author_id)
		REFERENCES
		authors(author_id) ON DELETE SET DEFAULT
);

DROP TABLE IF EXISTS vertexes;
CREATE TABLE IF NOT EXISTS vertexes (
	vertex_name varchar(50) NOT NULL UNIQUE,
	vertex_params_id integer NOT NULL,
	 graph_id varchar(50) NOT NULL,
	PRIMARY KEY (vertex_name),
	FOREIGN KEY (vertex_params_id) 
		REFERENCES 
		vertex_params(params_id)  ON DELETE RESTRICT,
	FOREIGN KEY (graph_id)
		REFERENCES
		graphs(graph_name) ON DELETE CASCADE
);

DROP TABLE IF EXISTS vertex_identity;
CREATE TABLE IF NOT EXISTS vertex_identity (
	link_id serial NOT NULL,
	start_vertex varchar(50) DEFAULT NULL,
	end_vertex varchar(50) DEFAULT NULL,
	PRIMARY KEY (link_id),	
	FOREIGN KEY (start_vertex)
		REFERENCES
		vertexes(vertex_name) ON DELETE CASCADE,
	FOREIGN KEY (end_vertex)
		REFERENCES
		vertexes(vertex_name) ON DELETE SET DEfAULT
);

