Delimiter $$

CREATE TRIGGER estocar BEFORE INSERT
ON entrada
FOR EACH ROW
BEGIN
	UPDATE estocado SET estocado.Qtde = estocado.Qtde + NEW.Qtde
WHERE estocado.Id_estoque = NEW.fk_Estocado_Id_estoque;
END

$$

Delimiter $$

CREATE TRIGGER desestocar BEFORE INSERT
ON saida
FOR EACH ROW
BEGIN
	UPDATE estocado SET estocado.Qtde = estocado.Qtde + NEW.Qtde
WHERE estocado.Id_estoque = NEW.fk_Estocado_Id_estoque;
END


$$