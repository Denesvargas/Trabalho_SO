def choose_edit_opt(opt, mydb):
    if(opt == 1):
        edit_almx(mydb)
    elif(opt == 2):
        edit_prod(mydb)
    elif(opt == 3):
        edit_linha(mydb)
    elif (opt == 4):
        edit_nota_compra(mydb)
    elif(opt == 5):
        edit_fornc(mydb)
    elif(opt == 6):
        edit_nota_venda(mydb)
    elif(opt == 7):
        edit_cliente(mydb)


def edit_almx(mydb):
    print("Digite o id do almoxarifado a ser editado: ")
    id_almx = int(input())
    select = mydb.query_select("almoxarifado", ["Id_almx"], [("Id_almx", "=", id_almx, "")])
    if(len(select) > 0):
        print("Digite a nova descricao a ser inserida no almoxarifado ou deixe vazio para cancelar: ")
        descr = input()
        if(descr != ""):
            mydb.query_update("almoxarifado", ["Descr"], [descr], [("Id_almx", "=", id_almx, "")])
    else:
        print("Nao foi encontrado o almoxerifado pesquisado, tente novamente.")

def edit_prod(mydb):
    print("Digite o id do produto a ser editado: ")
    id_prod = input()
    select = mydb.query_select("produto", ["Id_prod", "Nome", "Descr", "Preco", "fk_Linha_Id_linha"], [("Id_prod", "=", id_prod, "")], None, True)
    if(len(select) > 0):
        print("Digite o novo nome do produto ou deixe vazio para nao alterar:")
        name = input()
        if(name == ""):
            name = select[0]['Nome']
        print("Digite o novo preco ou deixe vazio para nao alterar:")
        price = input()
        if(price == ""):
            price = select[0]['Preco']
        else:
            price = float(price)
        print("Digite a nova descricao do produto ou deixe vazio para nao alterar:")
        descr = input()
        if(descr == ""):
            descr = select[0]['Descr']
        print("Digite o novo id da linha do produto, coloque 'NULL' ou deixe vazio para nao alterar.")
        linha_id = input()
        if(linha_id == ""):
            linha_id = select[0]['fk_Linha_Id_linha']
        if (linha_id != "NULL"):
            select = mydb.query_select("linha", ["Id_linha"], [("Id_linha", "=", linha_id, "")], None, True)
            if (len(select) > 0):
                linha_id = int(linha_id)
                mydb.query_update("produto", ["Nome", "Descr", "Preco", "fk_Linha_Id_linha"], [name, descr, price, linha_id], [("Id_prod", "=", id_prod, "")])
            else:
                print("Linha de produto nao encontrada, cadastre a linha do produto desejada antes.")
        else:
            mydb.query_update("produto", ["Nome", "Descr", "Preco", "fk_Linha_Id_linha"], [name, descr, price, "NULL"], [("Id_prod", "=", id_prod, "")])
    else:
        print("O produto nao foi encontrado, tente novamente.")

def edit_linha(mydb):
    print("Digite o id da linha a ser alterada:")
    id_linha = input()
    select = mydb.query_select("linha", ["Id_linha", "Descr"], [("Id_linha", "=", id_linha, "")])
    if(len(select) > 0 ):
        print("Digite a nova descrição da linha ou deixe vazio para nao alterar.")
        descr = input()
        if(descr != ""):
            mydb.query_update("linha", ["Descr"], [descr], [("Id_linha", "=", id_linha, "")])
    else:
        print("A linha de produto não foi encontrada, tente novamente.")

def edit_nota_compra(mydb):
    print("Digite o id da compra a ser editada:")
    id_compra = input()
    select = mydb.query_select("nota_compra", ["Num_nota", "Data_compra", "fk_Fornecedor_Id_fornc"], [("Num_nota", "=", id_compra, "")], None, True)
    if(len(select) > 0):
        print("Digite a nova data da compra(yyyy/mm/dd) ou deixe vazio para nao alterar.")
        date = input()
        if(date == ""):
            date = select[0]['Data_compra']
        print("Digite o novo id do Forncedor desta compra, deixe como 'NULL' ou deixe vazio para nao alterar.")
        fornc_id = input()
        if(fornc_id == ""):
            fornc_id = select[0]['fk_Fornecedor_Id_fornc']
        if (fornc_id != "NULL"):
            select = mydb.query_select("fornecedor", ["Id_fornc"], [("Id_fornc", "=", fornc_id, "")], None, True)
            if (len(select) > 0):
                fornc_id = int(fornc_id)
                mydb.query_update("nota_compra", ["Data_compra", "fk_Fornecedor_Id_fornc"], [date, fornc_id], [("Num_nota", "=", id_compra, "")])
            else:
                print("Fornecedor nao encontrado, cadastre o fornecedor desejado antes.")
        else:
            mydb.query_update("nota_compra", ["Data_compra", "fk_Fornecedor_Id_fornc"], [date, "NULL"], [("Num_nota", "=", id_compra, "")])  # change for except
    else:
        print("A nota de compra nao foi encontrada, tente novamente")

def edit_fornc(mydb):
    print("Digite o id do fornecedor a ser editado:")
    id_fornc = input()
    select = mydb.query_select("fornecedor", ["Id_fornc", "CNPJ", "CEP"], [("Id_fornc", "=", id_fornc, "")], None, True)
    if(len(select) > 0 ):
        print("Digite o novo CNPJ do Fornecedor ou deixe vazio para nao alterar")
        cnpj = input()
        if(cnpj == ""):
            cnpj = select[0]['CNPJ']
        print("Digite o novo CEP do Fornecedor ou deixe vazio para nao alterar")
        cep = input()
        if(cep == ""):
            cep = select[0]['CEP']
        mydb.query_update("fornecedor", ["CNPJ", "CEP"], [cnpj, cep], [("Id_fornc", "=", id_fornc, "")])
    else:
        print("Fornecedor nao encontrado, tente novamente.")

def edit_nota_venda(mydb):
    print("Digite o id da nota de venda a ser editada:")
    id_venda = input()
    select = mydb.query_select("nota_venda", ["Num_nota", "Data_venda", "fk_Cliente_CPF"], [("Num_nota", "=", id_venda, "")], None, True)
    if (len(select) > 0):
        print("Digite a data da venda(yyyy/mm/dd) ou deixe vazio para nao alterar")
        date = input()
        if (date == ""):
            date = select[0]['Data_venda']
        print("Digite o CPF do cliente desta compra, deixe como 'NULL' ou deixe vazio para nao alterar")
        cliente_cpf = input()
        if (cliente_cpf == ""):
            cliente_cpf = select[0]['fk_Cliente_CPF']
        if (cliente_cpf != "NULL"):
            select = mydb.query_select("cliente", ["CPF"], [("CPF", "=", cliente_cpf, "")], None, True)
            if (len(select) > 0):
                mydb.query_update("nota_venda", ["Data_venda", "fk_Cliente_CPF"], [date, cliente_cpf],  [("Num_nota", "=", id_venda, "")])
            else:
                print("Cliente nao encontrado, cadastre o cliente desejado antes.")
        else:
            mydb.query_update("nota_venda", ["Data_venda", "fk_Cliente_CPF"], [date, "NULL"], [("Num_nota", "=", id_venda, "")])
    else:
        print("Nota de venda nao encontrada, tente novamente")

def edit_cliente(mydb):
    print("Digite o CPF do cliente a ser alterado")
    cpf = input()
    select = mydb.query_select("cliente", ["CPF", "Nome", "Telef"], [("CPF", "=", cpf, "")], None, True)
    if(len(select) > 0 ):
        print("Digite o nome do cliente ou deixe vazio para nao alterar")
        name = input()
        if(name == ""):
            name = select[0]['Nome']
        print("Digite o telefone do cliente ou deixe vazio para nao alterar")
        tel = input()
        if(tel == ""):
            tel = select[0]['Telef']
        mydb.query_update("cliente", ["Nome", "Telef"], [name, tel], [("CPF", "=", cpf, "")])
    else:
        print("Cliente nao encontrado, tente novamente")

def edit_estoq(mydb):
    print("Digite o id do estoque a ser editado")
    id_estoq = input()
    select = mydb.query_select("estocado", ["Id_estoque", "Qtde", "fk_Almoxarifado_Id_almx", "fk_Produto_Id_prod"],
                               [("Id_estoque", "=", id_estoq, "")])
    if (len(select) > 0):
        print("Digite o novo id do produto, deixe como 'NULL' ou vazio para nao alterar")
        id_prod = input()
        if(id_prod == ""):
            id_prod = select[0]['fk_Produto_Id_prod']
        selectprod = mydb.query_select("produto", ["Id_prod", "Nome", "Descr", "Preco", "fk_Linha_Id_linha"], [("Id_prod", "=", id_prod, "")], None, True)
        if(len(selectprod) > 0):
            print("Digite o novo id do almoxarifado, deixe como 'NULL' ou vazio para nao alterar")
            id_almx = input()
            if(id_almx == ""):
                id_almx = select[0]['fk_Almoxarifado_Id_almx']
            selectalmx = mydb.query_select("almoxarifado", ["Id_almx"], [("Id_almx", "=", id_almx, "")])
            if (len(selectalmx) > 0):
                print("Digite a nova quantidade desse produto, ou deixe vazio para nao alterar")
                qtde = input()
                if (qtde == ""):
                   qtde = select[0]['Qtde']
                mydb.query_update("estocado", ["Qtde", "fk_Almoaxarifado_Id_almx", "fk_Produto_Id_prod"],
                                  [qtde, id_almx, id_prod], [("Id_estoque", "=", id_estoq, "")])
            else:
                print("Almoxarifado nao encontrado, tente novamente")
        else:
            print("Produto nao encontrado, tente novamente")
    else:
        print("Estoque nao encontrado, tente novamente")
