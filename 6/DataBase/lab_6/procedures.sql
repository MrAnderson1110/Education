DROP FUNCTION insert_vertex(character varying,integer,real,real,integer,integer);
CREATE OR REPLACE FUNCTION insert_vertex(
	vname character varying,
	vgraph int,
	vtlx real,
	vtly real,
	vsize int,
	vlink int
)
	RETURNS boolean
	LANGUAGE 'plpgsql'
AS $$	
	DECLARE
		new_vert_id integer;
		
	BEGIN
		
		if not exists (SELECT graph_id FROM graphs WHERE graph_id = vgraph) of vsize <= 0 then
			RETURN false;
		end if;
		
		new_vert_id := (
			SELECT max(vr.vertex_id) + 1
			FROM vertexes as vr
		);
		
		INSERT INTO vertexes (vertex_name, graph_id, top_left_x, top_left_y, vert_size)
		VALUES (vname, vgraph, vtlx, vtly, vsize);
		
		if vlink IS NOT NULL then
			INSERT INTO vertex_identity (start_vertex, end_vertex)
			VALUES (new_vert_id, vlink);
		end if;
		return true;
		
	END
$$

CREATE OR REPLACE FUNCTION fill(
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
