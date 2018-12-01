def choose_selec_opt(opt, mydb):
    if (opt == 1):
        selec_alm(mydb)
    elif (opt == 2):
        selec_prod(mydb)
    elif (opt == 3):
        selec_linha(mydb)
    elif (opt == 4):
        selec_nota_comp(mydb)
    elif (opt == 5):
        selec_fornc(mydb)
    elif (opt == 6):
        selec_nota_vend(mydb)
    elif (opt == 7):
        selec_cliente(mydb)

def selec_alm(mydb):
    select = mydb.query_select("almoxarifado", ["Id_almx", "Descr"])
    if (len(select) > 0):
        print("#########################################################")
        print("# " + ("Id_almx").center(10) + " | " + ("Descr").center(40) + " #")
        for i in select:
            print("# " + str(i['Id_almx']).center(10) + " | " + str(i['Descr']).center(40) + " #")
        print("#########################################################")

def selec_prod(mydb):
    select = mydb.query_select("produto", ["Id_prod", "Nome", "Descr", "Preco", "fk_Linha_Id_linha"])
    if (len(select) > 0):
        print("###############################################################################")
        print("# " + ("Id_prod").center(8) + " | " + ("Nome").center(10) + " | " + ("Descr").center(30) + " | " +
              ("Preço").center(8) + " | " + ("Linha").center(7) + " #")
        for i in select:
            print("# " + str(i['Id_prod']).center(8) + " | " + str(i['Nome']).center(10) + " | " + str(i['Descr']).center(30) +
                  " | " + str(i['Preco']).center(8) + " | " + str(i['fk_Linha_Id_linha']).center(7) + " #")
        print("###############################################################################")

def selec_linha(mydb):
    select = mydb.query_select("linha", ["Id_linha", "Descr"])
    if (len(select) > 0):
        print("#########################################################")
        print("# " + ("Id_linha").center(10) + " | " + ("Descr").center(40) + " #")
        for i in select:
            print("# " + str(i['Id_linha']).center(10) + " | " + str(i['Descr']).center(40) + " #")
        print("#########################################################")

def selec_nota_comp(mydb):
    select = mydb.query_select("nota_compra", ["Num_nota", "Data_compra", "fk_Fornecedor_Id_fornc"])
    if (len(select) > 0):
        print("########################################")
        print("# " + ("Num_nota").center(8) + " | " + ("Data_compra").center(12) + " | " + ("Id_fornc").center(
            10) + " #")
        for i in select:
            print("# " + str(i['Num_nota']).center(8) + " | " + str(i['Data_compra']).center(12) + " | " + str(
                i['fk_Fornecedor_Id_fornc']).center(10) + " #")
        print("########################################")
def selec_fornc(mydb):
    select = mydb.query_select("fornecedor", ["Id_fornc", "CNPJ", "CEP"])
    if (len(select) > 0):
        print("#####################################################")
        print("# " + ("Id_fornc").center(8) + " | " + ("CNPJ").center(20) + " | " + ("CEP").center(
            15) + " #")
        for i in select:
            print("# " + str(i['Id_fornc']).center(8) + " | " + str(i['CNPJ']).center(20) + " | " + str(
                i['CEP']).center(15) + " #")
        print("#####################################################")

def selec_nota_vend(mydb):
    select = mydb.query_select("nota_venda", ["Num_nota", "Data_venda", "fk_Cliente_CPF"])
    if (len(select) > 0):
        print("###########################################")
        print("# " + ("Num_nota").center(8) + " | " + ("Data_venda").center(10) + " | " + ("Cliente_CPF").center(
            15) + " #")
        for i in select:
            print("# " + str(i['Num_nota']).center(8) + " | " + str(i['Data_venda']).center(10) + " | " + str(
                i['fk_Cliente_CPF']).center(15) + " #")
        print("###########################################")

def selec_cliente(mydb):
    select = mydb.query_select("cliente", ["CPF", "Nome", "Telef"])
    if (len(select) > 0):
        print("######################################################################")
        print("# " + ("CPF").center(15) + " | " + ("Nome").center(30) + " | " + ("Telef").center(
            15) + " #")
        for i in select:
            print("# " + str(i['CPF']).center(15) + " | " + str(i['Nome']).center(30) + " | " + str(
                i['Telef']).center(15) + " #")
        print("######################################################################")