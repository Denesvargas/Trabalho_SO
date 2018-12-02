/*apos criar o banco e ele estiver totalmente sem alterações desde sua criação execute os querys abaixo para popular as tabelas*/

INSERT INTO `almoxarifado`(`Descr`) VALUES ('Principal')
INSERT INTO `almoxarifado`(`Descr`) VALUES ('Secundario')
INSERT INTO `almoxarifado`(`Descr`) VALUES ('Temporario');

INSERT INTO `linha`(`Descr`) VALUES ('Eletronicos')
INSERT INTO `linha`(`Descr`) VALUES ('Moveis')
INSERT INTO `linha`(`Descr`) VALUES ('Eletrodomesticos')
INSERT INTO `linha`(`Descr`) VALUES ('Roupas')
INSERT INTO `linha`(`Descr`) VALUES ('Higiene')
INSERT INTO `linha`(`Descr`) VALUES ('Alimentos');

INSERT INTO `produto`(`Nome`, `Descr`, `Preco`, `fk_Linha_Id_linha`) VALUES ('Celular', 'Samsung Galaxy', '149.99', '1')
INSERT INTO `produto`(`Nome`, `Descr`, `Preco`, `fk_Linha_Id_linha`) VALUES ('Sofa', 'Estofado 2 lugares', '499.99', '2')
INSERT INTO `produto`(`Nome`, `Descr`, `Preco`, `fk_Linha_Id_linha`) VALUES ('Liquidificador', 'Walita', '79.9', '3')
INSERT INTO `produto`(`Nome`, `Descr`, `Preco`, `fk_Linha_Id_linha`) VALUES ('Blusa', 'Verde M', '40.0', '4')
INSERT INTO `produto`(`Nome`, `Descr`, `Preco`, `fk_Linha_Id_linha`) VALUES ('Blusa', 'Rosa P', '40.0', '4')
INSERT INTO `produto`(`Nome`, `Descr`, `Preco`, `fk_Linha_Id_linha`) VALUES ('Sabonete', 'Palmolive', '1.49', '5')
INSERT INTO `produto`(`Nome`, `Descr`, `Preco`, `fk_Linha_Id_linha`) VALUES ('Bolacha', 'Negresco', '2.49', '6');

INSERT INTO `fornecedor`(`CNPJ`, `CEP`) VALUES ('32.522.203/0001-34', '97105-100')
INSERT INTO `fornecedor`(`CNPJ`, `CEP`) VALUES ('32.522.206/0002-45', '97100-300')
INSERT INTO `fornecedor`(`CNPJ`, `CEP`) VALUES ('32.522.208/0005-82', '98730-350')
INSERT INTO `fornecedor`(`CNPJ`, `CEP`) VALUES ('32.522.215/0013-21', '91460-200');

INSERT INTO `nota_compra`(`Data_compra`, `fk_Fornecedor_Id_fornc`) VALUES ('2018/12/02', '1')
INSERT INTO `nota_compra`(`Data_compra`, `fk_Fornecedor_Id_fornc`) VALUES ('2018/12/01', '2')
INSERT INTO `nota_compra`(`Data_compra`, `fk_Fornecedor_Id_fornc`) VALUES ('2018/11/01', '3')
INSERT INTO `nota_compra`(`Data_compra`, `fk_Fornecedor_Id_fornc`) VALUES ('2018/12/01', '3');

INSERT INTO `cliente`(`CPF`, `Nome`, `Telef`) VALUES ('1', 'Denes Vargas Teixeira', '51996092243')
INSERT INTO `cliente`(`CPF`, `Nome`, `Telef`) VALUES ('2', 'Natan Luiz Berwaldt', '51998522632');

INSERT INTO `nota_venda`(`Data_venda`, `fk_Cliente_CPF`) VALUES ('2018/12/01', '2')
INSERT INTO `nota_venda`(`Data_venda`, `fk_Cliente_CPF`) VALUES ('2018/12/01', '1');

INSERT INTO `estocado`(`Qtde`, `fk_Almoxarifado_Id_almx`, `fk_Produto_Id_prod`) VALUES ('1', '1', '1')
INSERT INTO `estocado`(`Qtde`, `fk_Almoxarifado_Id_almx`, `fk_Produto_Id_prod`) VALUES ('1', '1', '2')
INSERT INTO `estocado`(`Qtde`, `fk_Almoxarifado_Id_almx`, `fk_Produto_Id_prod`) VALUES ('1', '2', '1')
INSERT INTO `estocado`(`Qtde`, `fk_Almoxarifado_Id_almx`, `fk_Produto_Id_prod`) VALUES ('5', '1', '3')
INSERT INTO `estocado`(`Qtde`, `fk_Almoxarifado_Id_almx`, `fk_Produto_Id_prod`) VALUES ('1', '2', '3')
INSERT INTO `estocado`(`Qtde`, `fk_Almoxarifado_Id_almx`, `fk_Produto_Id_prod`) VALUES ('1', '1', '4')
INSERT INTO `estocado`(`Qtde`, `fk_Almoxarifado_Id_almx`, `fk_Produto_Id_prod`) VALUES ('1', '2', '5')
INSERT INTO `estocado`(`Qtde`, `fk_Almoxarifado_Id_almx`, `fk_Produto_Id_prod`) VALUES ('1', '1', '6')
INSERT INTO `estocado`(`Qtde`, `fk_Almoxarifado_Id_almx`, `fk_Produto_Id_prod`) VALUES ('1', '3', '7');

INSERT INTO `entrada`(`Qtde`, `Preco_compra`, `fk_Nota_compra_Num_nota`, `fk_Estocado_Id_estoque`) VALUES ('8', '100.00', '1', '1')
INSERT INTO `entrada`(`Qtde`, `Preco_compra`, `fk_Nota_compra_Num_nota`, `fk_Estocado_Id_estoque`) VALUES ('15', '190.00', '2', '2');

INSERT INTO `saida`(`Qtde`, `Preco_venda`, `fk_Estocado_Id_estoque`, `fk_Nota_venda_Num_nota`) VALUES ('3', '470.00', '2', '1')
INSERT INTO `saida`(`Qtde`, `Preco_venda`, `fk_Estocado_Id_estoque`, `fk_Nota_venda_Num_nota`) VALUES ('1', '149.90', '1', '1');

