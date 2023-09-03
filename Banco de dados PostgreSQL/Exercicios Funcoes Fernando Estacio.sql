-- 1)

CREATE OR REPLACE FUNCTION concat(t1 VARCHAR, t2 VARCHAR)
RETURNS VARCHAR AS
$$
BEGIN
  RETURN t1 || t2;
END;
$$ LANGUAGE plpgsql;

-- 2)

CREATE OR REPLACE FUNCTION TitulosFilme(codFilme NUMERIC)
RETURNS TABLE (n VARCHAR, n_original VARCHAR) AS 
$$
BEGIN
  n := (SELECT f.nome FROM filme f WHERE f.cod_filme = codFilme);
  n_original := (SELECT f.nome_original FROM filme f WHERE f.cod_filme = codFilme);
  RETURN QUERY VALUES(n, n_original);
END;
$$ LANGUAGE plpgsql;

-- 3)

CREATE OR REPLACE FUNCTION ParOuImpar(valor INT)
RETURNS VARCHAR AS 
$$
BEGIN
  IF (valor%2 = 0) THEN
    RETURN 'Par';
  ELSE
    RETURN 'Impar'; 
  END IF;
END;
$$ LANGUAGE plpgsql;

-- 4)

CREATE OR REPLACE FUNCTION Fat(valor INT)
RETURNS INT AS 
$$
BEGIN
    IF (valor = 0) THEN
        RETURN 1;
    ELSE
        return valor * (SELECT fat(valor-1));
    END IF;
END;
$$
LANGUAGE plpgsql;


-- 5)

CREATE OR REPLACE FUNCTION ListaFilmes(lancamento NUMERIC, cens NUMERIC)
RETURNS INT AS 
$$
BEGIN
  RETURN (SELECT COUNT (*) FROM filme f WHERE f.ano = lancamento and f.censura = cens);
END;
$$ LANGUAGE plpgsql;

