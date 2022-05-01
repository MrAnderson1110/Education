# table of params

DROP TABLE IF EXISTS vertex_params;
CREATE TABLE IF NOT EXISTS vertex_params (
	params_id 				serial NOT NULL,				# unique id	
	top_left_x				real NOT NULL,					# x of top left corner
	top_left_y				real NOT NULL,					# y of top left corner
	vert_size				integer NOT NULL,				# size of vertex
	
	PRIMARY KEY (params_id)	
);


# table of authors

DROP TABLE IF EXISTS authors;
CREATE TABLE IF NOT EXISTS authors (
	author_id				serial NOT NULL, 				# unique id
	author_name				varchar(50) DEFAULT NULL,			# author name
	author_surname				varchar(50) DEFAULT NULL,			# author surname
	
	PRIMARY KEY (author_id)			
);

DROP TABLE IF EXISTS graphs;
CREATE TABLE IF NOT EXISTS graphs (
	graph_name				varchar(50) NOT NULL UNIQUE,
	author_id				integer DEFAULT NULL,
	
	PRIMARY KEY (graph_name),
	
	FOREIGN KEY (author_id)
		REFERENCES
		authors(author_id) ON DELETE CASCADE
);


# table of vertexes

DROP TABLE IF EXISTS vertexes;
CREATE TABLE IF NOT EXISTS vertexes (
	vertex_id 				serial NOT NULL,				# unique id
	vertex_name				varchar(50) NOT NULL,				# vertex name
	vertex_params_id			integer NOT NULL,				# vertex parameters table id
	graph_id				integer DEFAULT NULL,				# graphs table id
	
	PRIMARY KEY (vertex_id),
	
	FOREIGN KEY (vertex_params_id) 
		REFERENCES 
		vertex_params(params_id)  ON DELETE RESTRICT,
	FOREIGN KEY (graph_id) 								
		REFERENCES
		graphs(graph_id)  ON DELETE CASCADE
);


# table of links

DROP TABLE IF EXISTS links;
CREATE TABLE IF NOT EXISTS links (
	link_id				serial NOT NULL,				# unique id
	start_vertex				integer NOT NULL,				# vertex where link starts
	end_vertex				integer DEFAULT NULL,				# vertex where link ends
	
	PRIMARY KEY (link_id),
	
	FOREIGN KEY (start_vertex)
		REFERENCES
		vertexes(vertex_id),
	FOREIGN KEY (end_vertex)
		REFERENCES
		vertexes(vertex_id)
);


# function to fill vertexes table

DROP FUNCTION IF EXISTS fill_schema(character varying, 
									character varying, 
									real, 
									real, 
									integer, 
									character varying, 
									character varying);
CREATE OR REPLACE FUNCTION public.fill_schema(
	gn character varying,
	vn character varying,
	tlx real,
	tly real,
	s integer,
	an character varying,
	asn character varying
)
    RETURNS TABLE ( 
    	id integer,
    	nm varchar(50),
    	vp integer,
    	va varchar(50)
    )
    LANGUAGE 'plpgsql'
AS $$
 
	DECLARE 
		params_table_id integer DEFAULT NULL;
		graph_table_id varchar(100) DEFAULT NULL;
		author_table_id integer DEFAULT NULL;
		
		start_vertex_id integer DEFAULT NULL;
		end_vertex_id integer DEFAULT 0;
		null_end_count integer DEFAULT 0;
		loop_count integer DEFAULT 0;
		last_graph_id integer;
		last_vert_id integer;
	BEGIN

	graph_table_id := (
		SELECT graph_name 
		FROM graphs
		WHERE graph_name = gn
	);
	
	IF graph_table_id IS NULL THEN 
		INSERT INTO graphs(graph_name)
		VALUES (gn);
		graph_table_id := (
			SELECT graph_name 
			FROM graphs
			WHERE graph_name = gn
		);
	END IF;

	author_table_id := (
		SELECT author_id
		FROM authors
		WHERE author_name = an AND author_surname = asn	
		LIMIT 1
	);
	IF author_table_id IS NULL THEN 
		INSERT INTO authors (author_name, author_surname)
		VALUES (an, asn);
		author_table_id := (
			SELECT author_id
			FROM authors
			WHERE author_name = an AND author_surname = asn
		);
	END IF;	

	UPDATE graphs SET author_id = author_table_id
	WHERE graph_table_id = graph_name;

	params_table_id := (
		SELECT params_id 
		FROM vertex_params
		WHERE top_left_x = tlx AND top_left_y = tly AND vert_size = s
	);
			
	IF params_table_id IS NULL THEN 
		INSERT INTO vertex_params (top_left_x, top_left_y, vert_size)
		VALUES (tlx, tly, s);
		params_table_id := (
			SELECT params_id
			FROM vertex_params
			WHERE top_left_x = tlx AND top_left_y = tly AND vert_size = S
		);
	END IF;	
		
	INSERT INTO vertexes (vertex_name, vertex_params_id, graph_id)
	VALUES (vn, params_table_id, graph_table_id);
	
	INSERT INTO links (start_vertex)
	SELECT vertex_id 
	FROM vertexes 
 	ORDER BY vertex_id DESC
	LIMIT 1;
	
	start_vertex_id := 0;	
	loop_count := 0;
	LOOP 
		EXIT WHEN start_vertex_id IS NULL 
			OR loop_count > 6 
			OR (SELECT count(*) FROM vertexes) 
				<= (SELECT count(*) FROM links WHERE end_vertex IS NOT NULL);
		start_vertex_id := (
			SELECT vertex_id
			FROM vertexes
			ORDER BY random() 
			LIMIT 1
		);
		end_vertex_id := (
			SELECT vertex_id
			FROM vertexes
			ORDER BY random() 
			LIMIT 1
		);
		
		null_end_count := (
			SELECT count(*) 
			FROM links
			WHERE start_vertex = start_vertex_id AND end_vertex IS NULL
		);
		
		IF start_vertex_id IS NOT NULL AND end_vertex_id IS NOT NULL THEN 
			IF null_end_count > 0 THEN 
				UPDATE links 
				SET end_vertex = end_vertex_id
				WHERE start_vertex = start_vertex_id AND end_vertex IS NULL;
			ELSE
				INSERT INTO links (start_vertex, end_vertex)
				VALUES (start_vertex_id, end_vertex_id);
			END IF;
		END IF;
		
		loop_count := loop_count + 1;		
	END LOOP;	
	
	RETURN QUERY SELECT * FROM vertexes;
END 
$$;



# fill vertexes table
SELECT * FROM fill_schema('graph of ivan', 'first vert', 0.1, 1.32, 10, 'Ivan', 'Ivanov');
SELECT * FROM fill_schema('graph of ivan', 'отказ',	5.1, 6.6, 11, 'Ivan', 'Ivanov');
SELECT * FROM fill_schema('graph of ivan', 'содержит отказ', 9.2, 15.15, 43, 'Ivan', 'Ivanov');

SELECT * FROM fill_schema('second graph of ivan', 'содержит отказ или нет', 9.2, 15.15, 43, 'Ivan', 'Ivanov');

SELECT * FROM fill_schema('graph of andrew', 'sec vert', 1.31, 2.61, 1, 'Andrew', 'Andreev');
SELECT * FROM fill_schema('graph of andrew', 'third vert',	6.12, 11.1, 15, 'Andrew', 'Andreev');
SELECT * FROM fill_schema('graph of andrew', 'эта ошибка в середине', 3.14, 14.1, 11, 'Andrew', 'Andreev');

SELECT * FROM fill_schema('graph of artem', 'ошибка', 14.5, 13.3, 5, 'Artem', 'Bazhenov');
SELECT * FROM fill_schema('graph of artem', 'этот отказ в середине', 12.5, 1.3, 4, 'Artem', 'Bazhenov');
SELECT * FROM fill_schema('graph of artem', 'отказ в начале',	1.5, 5.1, 16, 'Artem', 'Bazhenov');


# truncate cascade 
TRUNCATE vertexes CASCADE;
TRUNCATE authors CASCADE;
TRUNCATE graphs CASCADE;
TRUNCATE vertex_params CASCADE;
TRUNCATE links CASCADE

# drop tables
DROP TABLE IF EXISTS vertexes CASCADE;
DROP TABLE IF EXISTS graphs CASCADE;
DROP TABLE IF EXISTS authors CASCADE;
DROP TABLE IF EXISTS vertex_params CASCADE;
DROP TABLE IF EXISTS links CASCADE;

# add and remove coulumn
ALTER TABLE authors ADD age integer
ALTER TABLE authors DROP COLUMN age

# increese column values
UPDATE vertex_params SET vert_size=vert_size+1

# delete row
DELETE FROM authors WHERE author_name='Ivan'

# merge (not supported by psql)
MERGE INTO authors as au USING vertexes as v
on au.author_id=v.author_id
WHEN MATCHED
THEN UPDATE SET name='Ivan', surname='Ivanov'
WHEN NOT MATCHED and v.name='ошибка'
THEN INSERT VALUES ('Roman', 'Romanov')

# а. Вершины, название/текст которых содержит слово «отказ», но не зканчивается им
SELECT * FROM vertexes WHERE vertex_name~*'отказ +'


# б. Вершины, у которых нет исходящих ребер
SELECT v.*
FROM vertexes AS v, links AS l
WHERE v.vertex_id = l.start_vertex AND l.end_vertex IS NULL


# в. Графы, в которых есть пара вершин, связанных ребрами в обе стороны



# г. Ширина графа в пикселях (от максимальной сумма координаты по горизонтали с шириной отнять минимальную левую координату)
SELECT max_cor.max_x + max_cor.vert_size - min_cor.min_x as graph_size
FROM (
	SELECT top_left_x as max_x, vert_size, params_id
	FROM vertex_params
	WHERE top_left_x = (
		SELECT DISTINCT max(top_left_x)
		FROM vertex_params
	)
) as max_cor, (
	SELECT DISTINCT min(top_left_x) as min_x
	FROM vertex_params
) as min_cor


# д. пользователи-авторы графов с максимальных количеством вершин
SELECT gr.graph_name, au.author_name, au.author_surname, counts.vert_count
FROM (
	SELECT count(*) AS vert_count, v.graph_id as graph_id
	FROM vertexes as v
	GROUP BY graph_id
) as counts,
graphs as gr
RIGHT JOIN authors as au ON gr.author_id = au.author_id
WHERE counts.vert_count = (
	SELECT max(max_counts.vert_count)
	FROM (
		SELECT count(*) AS vert_count, v.graph_id as graph_id
		FROM vertexes as v
		GROUP BY graph_id
	) AS max_counts
) AND gr.graph_name = counts.graph_id


# е. Вершины, для которых есть исходящие ребра, ведущие ко всем остальным вершинам еѐ графа



# ж. Вершина, у которой нет входящих ребер от вершины о словом «ошибка»
SELECT * FROM vertexes
WHERE vertex_id != ALL(
	SELECT l.end_vertex 
	FROM links as l, vertexes as v
	WHERE 
		l.end_vertex IS NOT NULL AND 
		l.start_vertex = v.vertex_id AND 
		v.vertex_name~*'ошибка'
)

