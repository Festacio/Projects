-- Exercício 1
  CREATE VIEW filmes_pos_2000 AS (
  SELECT filme.nome, filme.nome_original FROM filme WHERE filme.ano > 2000 
  ORDER BY filme.ano ASC )


-- Exercício 2
  CREATE VIEW filmes_com_kenneth AS (
  SELECT DISTINCT filme.nome, filme.nome_original FROM filme, participacao WHERE filme.ano < 2000 
  AND participacao.cod_profissional_cinema = (SELECT cod_profissional_cinema FROM profissional_cinema WHERE profissional_cinema.nome = 'Kenneth Branagh') 
  AND participacao.cod_filme = filme.cod_filme
  ORDER BY filme.ano ASC )

-- Exercício 3 
  CREATE VIEW filmes_com_kenneth_principal AS (
  SELECT filme.nome, filme.nome_original FROM filme, participacao WHERE filme.ano < 2000 
  AND participacao.cod_profissional_cinema = (SELECT cod_profissional_cinema FROM profissional_cinema WHERE profissional_cinema.nome = 'Kenneth Branagh') 
  AND participacao.cod_papel = (SELECT cod_papel FROM papel WHERE descricao = 'ATOR PRINCIPAL') 
  AND participacao.cod_filme = filme.cod_filme
  ORDER BY filme.ano ASC )

-- Exercício 4
  CREATE VIEW atores_todos_papeis AS (
  SELECT pro.nome from profissional_cinema pro 
  WHERE pro.cod_profissional_cinema = (SELECT part.cod_profissional_cinema FROM participacao part
                                       GROUP BY part.cod_profissional_cinema
                                       HAVING COUNT (DISTINCT part.cod_papel) = 5)
  )