from MySQL_func import MySQLManager
import add_query as add_db
import updt_query as updt_db

def choose(opt, name_opt, mydb):
    opt_add = -1
    while(opt_add != 0):
        print("Digite o numero da opcao que deseja " + name_opt + ":")
        print("1-almoxarifado.")
        print("2-produto.")
        print("3-linha de produto.")
        print("4-Nota de compra.")
        print("5-Fornecedor.")
        print("6-Nota de venda.")
        print("7-cliente.")
        print("0-Voltar ao menu anterior.")
        opt_add = int(input());
        if(opt == 1):
            add_db.choose_add_opt(opt_add, mydb)
        elif(opt == 2):
            updt_db.choose_edit_opt(opt_add, mydb)
        elif(opt == 3):
            choose_rem_opt()
        elif(opt == 4):
            choose_selec_opt()


def main():
    opt = -1
    name_opt = ""
    mydb = MySQLManager("localhost", "root", "1234", "estoque")
    while(opt != 0):
        print("Digite o numero da opcao desejada:")
        print("1-Incluir no banco de dados.")
        print("2-Editar no banco de dados.")
        print("3-Remover do banco de dados.")
        print("4-Selecionar no banco de dados.")
        print("0-Sair do programa.")
        opt = int(input());
        if(opt == 1):
            name_opt = "Adicionar"
        elif(opt == 2):
            name_opt = "Alterar"
        elif(opt == 3):
            name_opt = "Remover"
        elif (opt == 4):
            name_opt = "Selecionar"
        if(opt < 5 and opt > 0):
            choose(opt, name_opt, mydb)
    print("fim")

main()







'''

def choose_rem_opt(opt):
    if (opt == 1):
        # add_alm
    elif (opt == 2):
        # add_produto
    elif (opt == 3):
        # add_linha
    elif (opt == 4):
        # add_nota_comp
    elif (opt == 5):
        # add_fornc
    elif (opt == 6):
        # add_nota_vend
    elif (opt == 7):
        # add_cliente

def choose_selec_opt(opt):
    if (opt == 1):
        # add_alm
    elif (opt == 2):
        # add_produto
    elif (opt == 3):
        # add_linha
    elif (opt == 4):
        # add_nota_comp
    elif (opt == 5):
        # add_fornc
    elif (opt == 6):
        # add_nota_vend
    elif (opt == 7):
        # add_cliente
'''
