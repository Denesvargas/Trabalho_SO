import MySQLdb as Mdb
from sql_manager import SQLManager


class MySQLManager(SQLManager):
    def __init__(self, host, login, password, database):
        # Create the basic database configuration
        self.host = host
        self.login = login
        self.password = password
        self.database = database

        # Set the connected to false
        self.connected = False

        # Set the connection to None
        self.connection = None

        # We set the cursor to none
        self.cursor = None

    def connect_to_database(self):
        # conecta com o banco de dados
        try:
            self.connection = Mdb.connect(self.host, self.login, self.password, self.database)
        except:
            raise Exception("Unable to Connect to the Database")
        else:
            self.connected = True
            self.cursor = self.connection.cursor()

    def query_insert(self, table, columns, values):
        # retesta a conexão, constroi o query de insert com o manager e da update
        if not self.connected:
            self.connect_to_database()
        # constroi a query
        super().query_insert(table, columns, values)

        # manda executar
        self.query_without_result()

    def query_update(self, table, columns, values, where):
        # retesta a conexão, constroi o query de update com o manager e da update
        if not self.connected:
            self.connect_to_database()

        super().query_update(table, columns, values, where)

        # manda executar
        self.query_without_result()

    def query_delete(self, table, where):
        # retesta a conexão, constroi o query de delete com o manager e da update
        if not self.connected:
            self.connect_to_database()

        super().query_delete(table, where)

        # manda executar
        self.query_without_result()

    def query_select(self, table, columns, where=None, order=None, asc=True):
        # retesta a conexão, constroi o query de select com o manager e da update
        if not self.connected:
            self.connect_to_database()

        super().query_select(table, columns, where, order, asc)

        # obtem o resultado da query
        result = self.query_with_result()

        if columns == "*":
            columns = self.query_columns_names(table)

        # com o resultado das colunas obtidas ajustamos com o nome das tabelas
        return [{columns[j]: result[i][j] for j in range(len(columns))} for i in range(len(result))]

    def query_columns_names(self, table):
        # retesta a conexão, constroi o query de nomes de colunas
        if not self.connected:
            self.connect_to_database()

        super().query_columns(table)

        result = self.query_with_result()

        return [r[0] for r in result]

    def query_without_result(self):
        # execucao sem retorno
        try:
            self.cursor.execute(self.query)
        except:
            raise Exception("Fail to Execute Database Query")
        else:
            self.connection.commit()

    def query_with_result(self):
        # execução com retorno
        try:
            self.cursor.execute(self.query)
        except:
            raise Exception("Fail to Execute Database Query")
        else:
            return self.cursor.fetchall()