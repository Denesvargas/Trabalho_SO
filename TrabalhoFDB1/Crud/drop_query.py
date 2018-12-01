def choose_rem_opt(opt, mydb):
    if (opt == 1):
        rem_alm(mydb)
    elif (opt == 2):
        rem_prod(mydb)
    elif (opt == 3):
        rem_linha(mydb)
    elif (opt == 4):
        rem_nota_comp(mydb)
    elif (opt == 5):
        rem_fornc(mydb)
    elif (opt == 6):
        rem_nota_vend(mydb)
    elif (opt == 7):
        rem_cliente(mydb)

def rem_alm(mydb):
    print("Digite o id do almoxarifado a ser excluido: ")
    id_almx = int(input())
    select = mydb.query_select("almoxarifado", ["Id_almx"], [("Id_almx", "=", id_almx, "")])
    if (len(select) > 0):
        print("Tem certeza que deseja excluir o almoxarifado?(S/N)")
        descr = input()
        if (descr == "S"):
            mydb.query_delete("almoxarifado", [("Id_almx", "=", id_almx, "")])
    else:
        print("Nao foi encontrado o almoxerifado pesquisado, tente novamente.")

def rem_prod(mydb):
    print("Digite o id do produto a ser excluido: ")
    id_prod = input()
    select = mydb.query_select("produto", ["Id_prod", "Nome", "Descr", "Preco", "fk_Linha_Id_linha"], [("Id_prod", "=", id_prod, "")], None, True)
    if (len(select) > 0):
        print("Tem certeza que deseja excluir o produto?(S/N)")
        descr = input()
        if (descr == "S"):
            mydb.query_delete("produto", [("Id_prod", "=", id_prod, "")])
        else:
            print("Linha de produto nao encontrada, cadastre a linha do produto desejada antes.")
    else:
        print("O produto nao foi encontrado, tente novamente.")

def rem_linha(mydb):
    print("Digite o id da linha a ser excluida:")
    id_linha = input()
    select = mydb.query_select("linha", ["Id_linha", "Descr"], [("Id_linha", "=", id_linha, "")])
    if (len(select) > 0):
        print("Tem certeza que deseja excluir a linha?(S/N)")
        descr = input()
        if (descr == "S"):
            id_linha = int(id_linha)
            mydb.query_delete("estoque`.`linha", [("Id_linha", "=", id_linha, "")])
    else:
        print("A linha de produto não foi encontrada, tente novamente.")

def rem_nota_comp(mydb):
    print("Digite o id da compra a ser excluida:")
    id_compra = input()
    select = mydb.query_select("nota_compra", ["Num_nota", "Data_compra", "fk_Fornecedor_Id_fornc"],
                               [("Num_nota", "=", id_compra, "")], None, True)
    if (len(select) > 0):
        print("Tem certeza que deseja excluir a nota de compra?(S/N)")
        descr = input()
        if (descr == "S"):
            mydb.query_delete("nota_compra", [("Num_nota", "=", id_compra, "")])
    else:
        print("A nota de compra nao foi encontrada, tente novamente")

def rem_fornc(mydb):
    print("Digite o id do fornecedor a ser excluido:")
    id_fornc = input()
    select = mydb.query_select("fornecedor", ["Id_fornc", "CNPJ", "CEP"], [("Id_fornc", "=", id_fornc, "")], None, True)
    if (len(select) > 0):
        print("Tem certeza que deseja excluir o fornecedor?(S/N)")
        descr = input()
        if (descr == "S"):
            mydb.query_delete("fornecedor", [("Id_fornc", "=", id_fornc, "")])
    else:
        print("Fornecedor nao encontrado, tente novamente.")

def rem_nota_vend(mydb):
    print("Digite o id da nota de venda a ser excluida:")
    id_venda = input()
    select = mydb.query_select("nota_venda", ["Num_nota", "Data_venda", "fk_Cliente_CPF"], [("Num_nota", "=", id_venda, "")])
    if (len(select) > 0):
        print("Tem certeza que deseja excluir a nota de venda?(S/N)")
        descr = input()
        if (descr == "S"):
            mydb.query_update("nota_venda", [("Num_nota", "=", id_venda, "")])
    else:
        print("Nota de venda nao encontrada, tente novamente")

def rem_cliente(mydb):
    print("Digite o CPF do cliente a ser excluido")
    cpf = input()
    select = mydb.query_select("cliente", ["CPF", "Nome", "Telef"], [("CPF", "=", cpf, "")], None, True)
    if (len(select) > 0):
        print("Tem certeza que deseja excluir o cliente?(S/N)")
        descr = input()
        if (descr == "S"):
            mydb.query_delete("cliente", [("CPF", "=", cpf, "")])
    else:
        print("Cliente nao encontrado, tente novamente")