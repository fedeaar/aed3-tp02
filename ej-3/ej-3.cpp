/* idea: 
 *  - representar el problema como un grafo G de N + W nodos donde:
 *    - o_1 ... o_N son las oficinas, y m_1 ... m_W son los modems.
 *    - m_i -> o_j, con costo 0, para todo 1 <= i <= W, 1 <= j <= N.
 *    - o_i -> o_j, con costo V * dist(o_i, o_j), para todo 1 <= i, j <= N.
 *    - o_i -> o_j, con costo U * dist(o_i, o_j) ssi dist(o_i, o_j) <= R, para todo 1 <= i, j <= N.
 *  - calcular el AGM con PRIM (n^2, ya que el grafo es denso) modificado tal que:
 *    - sea s_udp = 0, s_fo = 0
 *    - por cada arista seleccionada por PRIM:
 *      - si corresponde a un cable udp, sumar su costo a s_udp
 *      - si corresponde a un cable fo, sumar su costo a s_fo
 *    - retornar s_udp, s_fo
 * */