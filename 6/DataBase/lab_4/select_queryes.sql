# а. Вершины, название/текст которых содержит слово «отказ», но не зканчивается им
SELECT * FROM vertexes WHERE vertex_name~*'отказ.';


# б. Вершины, у которых нет исходящих ребер
SELECT vr.*
FROM vertexes AS vr, vertex_identity AS vi
WHERE vr.vertex_id = vi.start_vertex AND vi.end_vertex IS NULL;


# в. Графы, в которых есть пара вершин, связанных ребрами в обе стороны
SELECT DISTINCT gr.*
FROM vertex_identity AS vi1
INNER JOIN vertex_identity AS vi2
ON vi1.start_vertex = vi2.end_vertex AND vi1.end_vertex = vi2.start_vertex
INNER JOIN vertexes AS vr 
ON vi1.start_vertex = vr.vertex_id
INNER JOIN graphs AS gr
ON vr.graph_id = gr.graph_id;
