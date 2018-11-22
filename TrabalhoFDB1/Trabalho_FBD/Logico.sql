/* Lógico_1: */

CREATE TABLE Produto (
    Id_prod INTEGER PRIMARY KEY auto_increment not null,
    Nome VARCHAR(40),
    Descr VARCHAR(40),
    Preco FLOAT,
    fk_Linha_Id_linha INTEGER
);

CREATE TABLE Linha (
    Id_linha INTEGER PRIMARY KEY auto_increment not null,
    Descr VARCHAR(40)
);

CREATE TABLE Almoxarifado (
    Id_almx INTEGER PRIMARY KEY auto_increment not null,
    Descr VARCHAR(40)
);

CREATE TABLE Estocado (
    Id_estoque INTEGER PRIMARY KEY auto_increment not null,
    Qtde INTEGER,
    fk_Almoxarifado_Id_almx INTEGER,
    fk_Produto_Id_prod INTEGER
);

CREATE TABLE Entrada (
    Qtde INTEGER,
    Preco_compra FLOAT,
    fk_Nota_compra_Num_nota INTEGER,
    fk_Estocado_Id_estoque INTEGER
);

CREATE TABLE Nota_compra (
    Num_nota INTEGER PRIMARY KEY auto_increment not null,
    Data_compra DATE,
    fk_Fornecedor_Id_fornc INTEGER
);

CREATE TABLE Fornecedor (
    Id_fornc INTEGER PRIMARY KEY auto_increment not null,
    CNPJ VARCHAR(20),
    CEP VARCHAR(20)
);

CREATE TABLE Cliente (
    CPF VARCHAR(20) PRIMARY KEY not null,
    Nome VARCHAR(40),
    Telef VARCHAR(20)
);

CREATE TABLE Nota_venda (
    Num_nota INTEGER PRIMARY KEY auto_increment not null,
    Data_venda DATE,
    fk_Cliente_CPF VARCHAR(20)
);

CREATE TABLE Saida (
    Qtde INTEGER,
    Preco_venda FLOAT,
    fk_Estocado_Id_estoque INTEGER,
    fk_Nota_venda_Num_nota INTEGER
);
 
ALTER TABLE Produto ADD CONSTRAINT FK_Produto_2
    FOREIGN KEY (fk_Linha_Id_linha)
    REFERENCES Linha (Id_linha)
    ON DELETE CASCADE;
 
ALTER TABLE Estocado ADD CONSTRAINT FK_Estocado_2
    FOREIGN KEY (fk_Almoxarifado_Id_almx)
    REFERENCES Almoxarifado (Id_almx)
    ON DELETE RESTRICT;
 
ALTER TABLE Estocado ADD CONSTRAINT FK_Estocado_3
    FOREIGN KEY (fk_Produto_Id_prod)
    REFERENCES Produto (Id_prod)
    ON DELETE CASCADE;
 
ALTER TABLE Entrada ADD CONSTRAINT FK_Entrada_1
    FOREIGN KEY (fk_Nota_compra_Num_nota)
    REFERENCES Nota_compra (Num_nota)
    ON DELETE RESTRICT;
 
ALTER TABLE Entrada ADD CONSTRAINT FK_Entrada_2
    FOREIGN KEY (fk_Estocado_Id_estoque)
    REFERENCES Estocado (Id_estoque)
    ON DELETE CASCADE;
 
ALTER TABLE Nota_compra ADD CONSTRAINT FK_Nota_compra_2
    FOREIGN KEY (fk_Fornecedor_Id_fornc)
    REFERENCES Fornecedor (Id_fornc)
    ON DELETE CASCADE;
 
ALTER TABLE Nota_venda ADD CONSTRAINT FK_Nota_venda_2
    FOREIGN KEY (fk_Cliente_CPF)
    REFERENCES Cliente (CPF)
    ON DELETE CASCADE;
 
ALTER TABLE Saida ADD CONSTRAINT FK_Saida_1
    FOREIGN KEY (fk_Estocado_Id_estoque)
    REFERENCES Estocado (Id_estoque)
    ON DELETE CASCADE;
 
ALTER TABLE Saida ADD CONSTRAINT FK_Saida_2
    FOREIGN KEY (fk_Nota_venda_Num_nota)
    REFERENCES Nota_venda (Num_nota)
    ON DELETE RESTRICT;
