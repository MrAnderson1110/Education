DROP TABLE IF EXISTS authors;
CREATE TABLE IF NOT EXISTS authors (
	author_id serial NOT NULL,
	author_name varchar(50) NOT NULL,
	author_surname varchar(50) DEFAULT NULL,	
	PRIMARY KEY (author_id)			
);

DROP TABLE IF EXISTS graphs;
CREATE TABLE IF NOT EXISTS graphs (
	graph_id serial NOT NULL,
	graph_name varchar(50) NOT NULL,
	author_id integer DEFAULT NULL,	
	PRIMARY KEY (graph_id),	
	FOREIGN KEY (author_id)
		REFERENCES
		authors(author_id) ON DELETE SET DEFAULT
);

DROP TABLE IF EXISTS vertexes;
CREATE TABLE IF NOT EXISTS vertexes (
	vertex_id serial NOT NULL,
	vertex_name varchar(50) NOT NULL,
	graph_id integer NOT NULL,
	top_left_x real DEFAULT 0.0,
	top_left_y real DEFAULT 0.0,
	vert_size integer NOT NULL,	
	PRIMARY KEY (vertex_id),
	FOREIGN KEY (graph_id)
		REFERENCES
		graphs(graph_id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS vertex_identity;
CREATE TABLE IF NOT EXISTS vertex_identity (
	link_id serial NOT NULL,
	start_vertex integer NOT NULL,
	end_vertex integer DEFAULT NULL,
	PRIMARY KEY (link_id),	
	FOREIGN KEY (start_vertex)
		REFERENCES
		vertexes(vertex_id) ON DELETE CASCADE,
	FOREIGN KEY (end_vertex)
		REFERENCES
		vertexes(vertex_id) ON DELETE SET DEfAULT
);

ALTER TABLE authors ADD age integer
ALTER TABLE authors DROP COLUMN age
