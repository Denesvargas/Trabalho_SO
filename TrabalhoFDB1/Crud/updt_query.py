def choose_edit_opt(opt, mydb):
    if(opt == 1):
        edit_almx(mydb)
    elif(opt == 2):
        edit_prod(mydb)


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
    print(select[0]['Nome'])
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
            mydb.query_update("produto", ["Nome", "Descr", "Preco"], [name, descr, price], [("Id_prod", "=", id_prod), ""])
    else:
        print("O produto nao foi encontrado, tente novamente.")

#def edit_linha(mydb):
