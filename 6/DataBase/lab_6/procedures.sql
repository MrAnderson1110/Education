DROP PROCEDURE IF EXISTS insert_vertex_proc(character varying,integer,real,real,integer,integer);
CREATE OR REPLACE PROCEDURE insert_vertex_proc(
	vname character varying,
	vgraph int,
	vtlx real,
	vtly real,
	vrsize int,
	vlink int
)	
	LANGUAGE 'plpgsql'
AS $$	
	DECLARE
		seq_name varchar(100);
		found_vert_id integer;
		graph_of_link integer;
		
	BEGIN		
		if not exists (
			SELECT graph_id 
			FROM graphs 
			WHERE graph_id = vgraph
		) or vrsize <= 0 then
			RETURN;
		end if;		
		
		if exists (
			select vertex_id 
			from vertexes 
			where vname = vertex_name
				and vgraph = graph_id
				and vtlx = top_left_x
				and vtly = top_left_y
				and vrsize = vert_size
			) then

			INSERT INTO vertex_identity (start_vertex, end_vertex)
			select vertex_id, vlink
			from vertexes
			where vname = vertex_name
				and vgraph = graph_id
				and vtlx = top_left_x
				and vtly = top_left_y
				and vrsize = vert_size;
			 
		else
			seq_name := (select pg_get_serial_sequence('vertexes', 'vertex_id') as new_id);
			found_vert_id := (select nextval(seq_name) as new_id) + 1;	
		
			INSERT INTO vertexes (vertex_name, graph_id, top_left_x, top_left_y, vert_size)
			VALUES (vname, vgraph, vtlx, vtly, vrsize);

			INSERT INTO vertex_identity (start_vertex, end_vertex)
			VALUES (found_vert_id, vlink);
		end if;	
		
	END
$$;

call insert_vertex_proc('Содержит отказ', 1, 1, 10, 15, 9);
call insert_vertex_proc('name of inserted vertex', 19, 7.1, 8.3, 9, NULL);
call insert_vertex_proc('name of inserted vertex with link', 19, 7.1, 8.3, 9, 7);
call insert_vertex_proc('name of inserted vertex with link', 19, 7.1, 8.3, 9, 63);

---------

DROP PROCEDURE IF EXISTS delete_with_clear_proc(integer);
CREATE OR REPLACE PROCEDURE delete_with_clear_proc(vid integer)
	LANGUAGE 'plpgsql'
AS $$	
	DECLARE
		gid integer;
		auid integer;
	BEGIN		
		gid := (
			SELECT graph_id 
			FROM vertexes
			WHERE vertex_id = vid
		);

		auid := (
			SELECT author_id
			FROM graphs
			WHERE graph_id = gid
		);

		if exists (SELECT vertex_id FROM vertexes WHERE vertex_id = vid) then
			DELETE FROM vertexes WHERE vertex_id = vid;
		end if;

		if not exists (SELECT vertex_id FROM vertexes WHERE graph_id = gid) then
			DELETE FROM graphs WHERE graph_id = gid;
		end if;

		if not exists (SELECT graph_id FROM graphs WHERE author_id = auid) then
			DELETE FROM authors WHERE author_id = auid;
		end if;
	END
$$;

call delete_with_clear_proc(75);

---------

DROP PROCEDURE IF EXISTS delete_author_cascade(integer);
CREATE OR REPLACE PROCEDURE delete_author_cascade(auid integer)	
	LANGUAGE 'plpgsql'
AS $$	
	BEGIN	
		DELETE FROM vertexes WHERE vertex_id IN (
			SELECT vr.vertex_id 
			FROM vertexes as vr
			INNER JOIN graphs as gr
			ON gr.graph_id = vr.graph_id
			WHERE gr.author_id = auid
		)
		DELETE FROM graphs WHERE author_id = auid;
		DELETE FROM authors WHERE author_id = auid;
	END
$$;

call delete_author_cascade(4);

---------

DROP FUNCTION IF EXISTS authors_count();
CREATE OR REPLACE FUNCTION authors_count()	
RETURNS integer
	LANGUAGE 'plpgsql'
AS $$	
	DECLARE
		counts integer;
	BEGIN
		counts := (
			SELECT count(*) 
			FROM authors
		);

		RETURN counts;			
	END
$$;

select * from authors_count();

DROP FUNCTION IF EXISTS graphs_count_of_author(integer);
CREATE OR REPLACE FUNCTION graphs_count_of_author(auid integer)	
RETURNS integer
	LANGUAGE 'plpgsql'
AS $$	
	DECLARE
		counts integer;
	BEGIN
		counts := (
			SELECT count(*) 
			FROM graphs 
			WHERE author_id = auid
		);

		RETURN counts;
	END
$$;

select * from graphs_count_of_author(18);

DROP FUNCTION IF EXISTS vertexes_count_of_author(integer);
CREATE OR REPLACE FUNCTION vertexes_count_of_author(auid integer)	
RETURNS integer
	LANGUAGE 'plpgsql'
AS $$	
	DECLARE
		counts integer;
	BEGIN
		counts := (
			SELECT count(*) 
			FROM vertexes as vr
			LEFT JOIN graphs as gr
			ON gr.graph_id = vr.graph_id
			WHERE gr.author_id = auid
		);

		RETURN counts;
	END
$$;

select * from vertexes_count_of_author(18);

DROP FUNCTION IF EXISTS links_count_of_author(integer);
CREATE OR REPLACE FUNCTION links_count_of_author(auid integer)	
RETURNS integer
	LANGUAGE 'plpgsql'
AS $$	
	DECLARE
		counts integer;
	BEGIN
		counts := (
			SELECT count(*) 
			FROM vertex_identity as vi
			LEFT JOIN vertexes as vr
			ON vr.vertex_id = vi.start_vertex
			LEFT JOIN graphs as gr
			ON gr.graph_id = vr.graph_id
			WHERE gr.author_id = auid
		);

		RETURN counts;
	END
$$;

select * from links_count_of_author(18);

---------

DROP FUNCTION IF EXISTS get_statistic();
CREATE OR REPLACE FUNCTION get_statistic()	
RETURNS TABLE(
	stat_author_id integer,
	graphs_count integer,
	vertexes_count integer,
	links_count integer
)
	LANGUAGE 'plpgsql'
AS $$	
	DECLARE
		auid RECORD;
		grcount integer;
		vrcount integer;
		vicount integer;
	BEGIN	

		DROP TABLE IF EXISTS stat;
		CREATE TEMPORARY TABLE IF NOT EXISTS stat (
			stat_author_id integer NOT NULL,
			graphs_count integer DEFAULT 0,
			vertexes_count integer DEFAULT 0,
			links_count integer DEFAULT 0
		) ON COMMIT DROP;

		for auid in SELECT author_id FROM authors loop
			grcount := (
				SELECT count(*) FROM graphs WHERE author_id = auid.author_id
			);

			vrcount := (
				SELECT count(vr.*) FROM vertexes as vr
				LEFT JOIN graphs as gr
				ON vr.graph_id = gr.graph_id
				WHERE gr.author_id = auid.author_id
			);

			vicount := (
				SELECT count(vi.*) FROM vertex_identity as vi
				LEFT JOIN vertexes as vr
				ON vr.vertex_id = vi.start_vertex
				LEFT JOIN graphs as gr
				ON gr.graph_id = vr.graph_id
				WHERE gr.author_id = auid.author_id
			);

			INSERT INTO stat (stat_author_id, graphs_count, vertexes_count, links_count)
			VALUES (auid.author_id, grcount, vrcount, vicount);
		end loop;

		RETURN QUERY SELECT * FROM stat;
	END
$$;
 
select * from get_statistic();

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
