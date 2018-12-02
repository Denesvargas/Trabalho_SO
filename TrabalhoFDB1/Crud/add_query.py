def choose_add_opt(opt, mydb):
    if (opt == 1):
        add_almx(mydb)
    elif (opt == 2):
        add_prod(mydb)
    elif (opt == 3):
        add_linha(mydb)
    elif (opt == 4):
        add_nota_compra(mydb)
    elif (opt == 5):
        add_fornc(mydb)
    elif (opt == 6):
        add_nota_venda(mydb)
    elif (opt == 7):
        add_client(mydb)
    elif (opt == 8):
        add_estoq(mydb)
    elif (opt == 9):
        add_entr(mydb)
    elif(opt == 10):
        add_saida(mydb)

def add_almx(mydb):
    print("Digite a descricao do almoxarifado a ser inserido: ")
    descr = input()
    mydb.query_insert("almoxarifado", ["Descr"], [descr])

def add_prod(mydb):
    print("Digite o nome do produto:")
    name = input()
    print("Digite o preco:")
    price = float(input())
    print("Digite a descricao do produto:")
    descr = input()
    print("Digite o id da linha ou coloque 'NULL'.")
    linha_id = input()
    if (linha_id != "NULL"):
        select = mydb.query_select("linha", ["Id_linha"], [("Id_linha", "=", linha_id, "")], None, True)
        if (len(select) > 0):
            linha_id = int(linha_id)
            mydb.query_insert("produto", ["Nome", "Descr", "Preco", "fk_Linha_Id_linha"],
                              [name, descr, price, linha_id])
        else:
            print("Linha de produto nao encontrada, cadastre a linha do produto desejada antes.")
    else:
        mydb.query_insert("produto", ["Nome", "Descr", "Preco"], [name, descr, price])


def add_linha(mydb):
    print("Digite a descrição da linha")
    descr = input()
    mydb.query_insert("linha", ["Descr"], [descr])


def add_nota_compra(mydb):
    print("Digite a data da compra(yyyy/mm/dd)")
    date = input()
    print("Digite o id do Forncedor desta compra ou deixe como 'NULL'")
    fornc_id = input()
    if (fornc_id != "NULL"):
        select = mydb.query_select("fornecedor", ["Id_fornc"], [("Id_fornc", "=", fornc_id, "")], None, True)
        if (len(select) > 0):
            fornc_id = int(fornc_id)
            mydb.query_insert("nota_compra", ["Data_compra", "fk_Fornecedor_Id_fornc"], [date, fornc_id])
        else:
            print("Fornecedor nao encontrado, cadastre o fornecedor desejado antes.")
    else:
        mydb.query_insert("nota_compra", ["Data_compra"], [date])


def add_fornc(mydb):
    print("Digite o CNPJ do Fornecedor")
    cnpj = input()
    print("Digite o CEP do Fornecedor")
    cep = input()
    mydb.query_insert("fornecedor", ["CNPJ", "CEP"], [cnpj, cep])


def add_nota_venda(mydb):
    print("Digite a data da venda(yyyy/mm/dd)")
    date = input()
    print("Digite o CPF do cliente desta compra ou deixe como 'NULL'")
    cliente_cpf = input()
    if (cliente_cpf != "NULL"):
        select = mydb.query_select("cliente", ["CPF"], [("CPF", "=", cliente_cpf, "")], None, True)
        if (len(select) > 0):
            mydb.query_insert("nota_venda", ["Data_venda", "fk_Cliente_CPF"], [date, cliente_cpf])
        else:
            print("Cliente nao encontrado, cadastre o cliente desejado antes.")
    else:
        mydb.query_insert("nota_venda", ["Data_venda"], [date])


def add_client(mydb):
    print("Digite o CPF do cliente")
    cpf = input()
    print("Digite o nome do cliente:")
    name = input()
    print("Digite o telefone do cliente:")
    tel = input()
    mydb.query_insert("cliente", ["CPF", "Nome", "Telef"], [cpf, name, tel])

def add_estoq(mydb):
    print("Digite o Produto a ir no estoque")
    id_prod = input()
    select = mydb.query_select("produto", ["Id_prod", "Nome", "Descr", "Preco", "fk_Linha_Id_linha"], [("Id_prod", "=", id_prod, "")])
    if(len(select) > 0):
        print("Digite a quantidade desse produto")
        qtde = input()
        print("Digite o id do almoxarifado correspondente")
        id_almx = input()
        select = mydb.query_select("almoxarifado", ["Id_almx"], [("Id_almx", "=", id_almx, "")])
        if (len(select) > 0):
            mydb.query_insert("estocado", ["Qtde", "fk_Almoaxarifado_Id_almx", "fk_Produto_Id_prod"], [qtde, id_almx, id_prod])
        else:
            print("Almoxarifado nao encontrado, tente novamente")
    else:
        print("Produto nao encontrado.")

def add_entr(mydb):
    print("Digite o numero da nota de compra correspondente")
    num_nota = input()
    select = mydb.query_select("nota_compra", ["Num_nota", "Data_compra", "fk_Fornecedor_Id_fornc"], [("Num_nota", "=", num_nota, "")])
    if (len(select) > 0):
        print("Digite o estoque correspondente")
        id_estoq = input()
        select = mydb.query_select("estocado", ["Id_estoque", "Qtde", "fk_Almoxarifado_Id_almx", "fk_Produto_Id_prod"],
                                   [("Id_estoque", "=", id_estoq, "")])
        if (len(select) > 0):
            print("Digite a quantidade desse produto")
            qtde = input()
            print("Digite o preco de compra deste produto")
            price = input()
            mydb.query_insert("entrada", ["Qtde", "Preco_compra", "fk_Nota_compra_Num_nota", "fk_Estocado_Id_estoque"],
                              [qtde, price, num_nota, id_estoq])
        else:
            print("Estoque nao encontrado, tente novamente")
    else:
        print("Nota de compra nao encontrada, tente novamente")

def add_saida(mydb):
    print("Digite o numero da nota de venda correspondente")
    num_nota = input()
    select = mydb.query_select("nota_venda", ["Num_nota", "Data_venda", "fk_Cliente_CPF"],
                               [("Num_nota", "=", num_nota, "")])
    if (len(select) > 0):
        print("Digite o estoque correspondente")
        id_estoq = input()
        select = mydb.query_select("estocado", ["Id_estoque", "Qtde", "fk_Almoxarifado_Id_almx", "fk_Produto_Id_prod"],
                                   [("Id_estoque", "=", id_estoq, "")])
        if (len(select) > 0):
            print("Digite a quantidade desse produto")
            qtde = input()
            print("Digite o preco de venda deste produto")
            price = input()
            mydb.query_insert("entrada", ["Qtde", "Preco_venda", "fk_Estocado_Id_estoque", "fk_Nota_compra_Num_nota"],
                              [qtde, price, id_estoq, num_nota])
        else:
            print("Estoque nao encontrado, tente novamente")
    else:
        print("Nota de venda nao encontrada, tente novamente")