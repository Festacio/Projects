-- 1)

CREATE OR REPLACE PROCEDURE Custo_por_censura() AS
$$
DECLARE
    cursor_preco CURSOR FOR SELECT FILME.preco_sugerido_locacao FROM FILME;
    cursor_censura CURSOR FOR SELECT FILME.censura FROM FILME;
    cens INT;
    prec INT;
    
BEGIN
    OPEN cursor_preco;
    OPEN cursor_censura;
    
    FETCH cursor_censura INTO cens;  
    FETCH cursor_preco INTO prec;
    
    LOOP 	
        IF cens = 12 THEN
            UPDATE FILME SET preco_sugerido_locacao = prec + (prec*0.05) WHERE CURRENT OF cursor_preco;
        ELSIF cens = 16 THEN
            UPDATE FILME SET preco_sugerido_locacao = prec + (prec*0.10) WHERE CURRENT OF cursor_preco;
        ELSEIF cens = 18 THEN
            UPDATE FILME SET preco_sugerido_locacao = prec + (prec*0.15) WHERE CURRENT OF cursor_preco;
        ELSE
        	UPDATE FILME SET preco_sugerido_locacao = prec + (prec*0.02) WHERE CURRENT OF cursor_preco;       
        END IF;
        
    	FETCH NEXT FROM cursor_censura INTO cens;
        EXIT WHEN NOT FOUND;
        FETCH NEXT FROM cursor_preco INTO prec;
         
    END LOOP;
    
    CLOSE cursor_preco;
    CLOSE cursor_censura;
    
END;
$$
LANGUAGE plpgsql;

CALL custo_por_censura();
SELECT nome,censura,preco_sugerido_locacao FROM filme;