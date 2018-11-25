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
