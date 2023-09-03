-- 1)
CREATE OR REPLACE FUNCTION Nome_Classificacao_filmes()
RETURNS TABLE (nome_filme VARCHAR, classificacao VARCHAR) AS
$$
DECLARE
cursor_nome CURSOR FOR SELECT FILME.nome FROM FILME;
cursor_censura CURSOR FOR SELECT FILME.censura FROM FILME;
cens INT;

BEGIN
OPEN cursor_nome;
OPEN cursor_censura;

LOOP
FETCH cursor_nome INTO nome_filme;
EXIT WHEN NOT FOUND;
FETCH cursor_censura INTO cens;

IF cens >= 18 THEN
classificacao := 'Adulto';
ELSIF cens < 18 AND cens >= 16 THEN
classificacao := 'Adolescente';
ELSE
classificacao := 'Infantil';
END IF;

RETURN NEXT;

END LOOP;

CLOSE cursor_nome;
CLOSE cursor_censura;

END;
$$
LANGUAGE plpgsql;
SELECT Nome_Classificacao_filmes();

-- 2)

CREATE OR REPLACE FUNCTION dobra_preco(titulo VARCHAR)
RETURNS INT AS
$$
DECLARE
cursor_preco CURSOR FOR SELECT FILME.preco_sugerido_locacao FROM FILME WHERE filme.nome = titulo;
preco_dobrado INT;

BEGIN
OPEN cursor_preco;
FETCH cursor_preco INTO preco_dobrado;
CLOSE cursor_preco;

preco_dobrado := 2*preco_dobrado;
RETURN preco_dobrado;
END;
$$
LANGUAGE plpgsql;

SELECT dobra_preco('Amor Alem da Vida');