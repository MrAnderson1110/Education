# г. Ширина графа в пикселях (от максимальной сумма координаты по горизонтали с шириной отнять минимальную левую координату)
SELECT max_cor.max_x + max_cor.vsize - min_cor.min_x as graph_size, max_cor.gid as graph_id
FROM (
	SELECT vr.top_left_x as max_x, vr.vert_size as vsize, gr.graph_id as gid
	FROM vertexes as vr, graphs as gr
	WHERE vr.top_left_x >= ALL (
		SELECT internal_vr.top_left_x
		FROM vertexes as internal_vr
		WHERE internal_vr.graph_id = gr.graph_id
	) AND vr.graph_id = gr.graph_id
) as max_cor, (
	SELECT vr.top_left_x as min_x, gr.graph_id as gid
	FROM vertexes as vr, graphs as gr
	WHERE vr.top_left_x <= ALL (
		SELECT top_left_x
		FROM vertexes as internal_vr
		WHERE internal_vr.graph_id = gr.graph_id
	) AND vr.graph_id = gr.graph_id
) as min_cor
WHERE max_cor.gid = min_cor.gid;


# д. пользователи-авторы графов с максимальных количеством вершин
SELECT au.*
FROM authors as au
WHERE EXISTS (	
	SELECT *
	FROM (
		SELECT count(*) as vc
		FROM vertexes as vr, graphs as gr
		WHERE vr.graph_id = gr.graph_id AND gr.author_id = au.author_id 
		GROUP BY au.author_id
	) as counts
	WHERE counts.vc >= ALL (
		SELECT count(*)
		FROM vertexes as vr, graphs as gr
		WHERE vr.graph_id = gr.graph_id
		GROUP BY gr.author_id
	) 
);


# е. Вершины, для которых есть исходящие ребра, ведущие ко всем остальным вершинам еѐ графа
SELECT vr.*
FROM vertexes as vr
WHERE NOT EXISTS (	
	SELECT ivr1.vertex_id
	FROM graphs as gr
	INNER JOIN vertexes as ivr1
		ON ivr1.graph_id = gr.graph_id
	WHERE gr.graph_id = vr.graph_id AND ivr1.vertex_id NOT IN (
		SELECT ivr2.vertex_id
		FROM vertex_identity as vi
		INNER JOIN vertexes as ivr2
			ON ivr2.vertex_id = vi.end_vertex
		WHERE ivr2.graph_id = gr.graph_id 
			AND vi.start_vertex = vr.vertex_id 
			AND vi.end_vertex is not null
	)
);


# ж. Вершина, у которой нет входящих ребер от вершины о словом «ошибка»
SELECT *
FROM vertexes as vr
EXCEPT
SELECT vr.* FROM vertexes as vr
RIGHT JOIN vertex_identity as vi
ON vr.vertex_id = vi.end_vertex
LEFT JOIN vertexes as inner_vr
ON vi.start_vertex = inner_vr.vertex_id
WHERE inner_vr.vertex_name~*'ошибка+'
ORDER BY vertex_id;

SELECT *
FROM vertexes as vr
WHERE vr.vertex_id NOT IN (
	SELECT vi.end_vertex
	FROM vertex_identity as vi 
	LEFT JOIN vertexes as internal_vr
	ON internal_vr.vertex_id = vi.start_vertex
	WHERE internal_vr.vertex_name~*'ошибка+'
)
ORDER BY vertex_id;

