--1)

CREATE OR REPLACE FUNCTION fc_atualiza_preco_fim_semana()
RETURNS TRIGGER AS $$
BEGIN
NEW.preco_aplicado = NEW.preco_aplicado + 0.10*NEW.preco_aplicado;
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER tg_atualiza_preco_fim_semana BEFORE INSERT ON locacao
FOR EACH ROW WHEN ((EXTRACT(DOW FROM NEW.dt_saida) = 6) OR (EXTRACT(DOW FROM NEW.dt_saida) = 0))
EXECUTE FUNCTION fc_atualiza_preco_fim_semana();

--2)

CREATE TABLE log_locacoes_abaixo_sugerido AS
SELECT * FROM locacao
WHERE FALSE;

CREATE OR REPLACE FUNCTION fc_log_precobaixo()
RETURNS TRIGGER AS $$
BEGIN
if (NEW.preco_aplicado < (SELECT filme.preco_sugerido_locacao FROM Filme WHERE NEW.cod_exemplar = filme.cod_filme)) THEN
INSERT INTO log_locacoes_abaixo_sugerido (cod_exemplar, cod_cliente, dt_saida, dt_devolucao, preco_aplicado)
VALUES (NEW.cod_exemplar, NEW.cod_cliente, NEW.dt_saida, NEW.dt_devolucao, NEW.preco_aplicado);
END IF;
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER tg_log_precobaixo
AFTER INSERT ON locacao FOR EACH ROW
EXECUTE FUNCTION fc_log_precobaixo();

--3)

CREATE SEQUENCE sequencia_chave_PC
START 67
OWNED BY profissional_cinema.cod_profissional_cinema;

CREATE OR REPLACE FUNCTION fc_preenche_chave_PC()
RETURNS TRIGGER AS $$
BEGIN
NEW.cod_profissional_cinema = NEXTVAL('sequencia_chave_PC');
RETURN NEW;
END;
$$
LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER tg_preenche_chave_PC
BEFORE INSERT ON profissional_cinema FOR EACH ROW
EXECUTE FUNCTION fc_preenche_chave_PC();