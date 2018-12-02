class SQLManager(object):
    def __init__(self):
        self.query = ""

    def order_with_separator(self, array, bet="`", sep=","):
        """
        organiza os elementos do vetor separando-os por 'sep' e coloca envoltar de cada valor 'bet'.
        :param array:
        :return:
        """
        string = ""
        for i in range(len(array)):
            if i != len(array) - 1:
                string += bet + str(array[i]) + bet + sep + " "
            else:
                string += bet + str(array[i]) + bet
        return string

    def query_where(self, where):
        """
        Cria a query do where
        where: lista de tuplas com (colunx, = , value, next_comparator)
        retorna o query do where
        """
        where_part = "WHERE"

        # We go throw the where statement
        for data in where:
            # We add the data column
            where_part += " `" + data[0] + "`"

            # We add the comparison
            where_part += " " + data[1]

            # We add the value
            if data[2] == "NULL":
                where_part += " " + data[2]
            else:
                where_part += " '" + str(data[2]) + "'"

            # Then we add link between statement
            where_part += " " + data[3]

        # We return the query
        return where_part

    def query_insert(self, table, columns, values):
        """
        adiciona uma linha em uma tabela
        table = nome da tabela
        columns = lista com nome das colunas em ordem
        values = lista com os valores novos das respectivas colunas
        """
        # First we add the insert into statement
        self.query = "INSERT INTO `" + table + "`"

        # Then we go throw each column and add the column name
        self.query += "(" + self.order_with_separator(columns) + ")"

        # Then we go throw the values and add then
        self.query += " VALUES (" + self.order_with_separator(values, bet="'") + ")"

    def query_update(self, table, columns, values, where):
        """
        atualiza uma tabela
        columns = lista com nome das colunas em ordem
        values = lista com os valores novos das respectivas colunas
        where = lista com as tuplas de where's
        :return:
        """
        # We create the new query
        self.query = "UPDATE `" + table + "`"

        # We connect the columns and the values into one list
        concat = ["`" + columns[i] + "`='" + str(values[i]) + "'" for i in range(len(columns))]

        # Then we add to the query this values
        self.query += " SET " + self.order_with_separator(concat, bet="")

        # Finally we add the where
        self.query += " " + self.query_where(where)

    def query_delete(self, table, where):
        """
        table = nome da tabela
        where = lista com as tuplas de where's
        """
        self.query = ""
        # Start the new query
        self.query += "DELETE FROM `" + table + "`"

        # Add the where statement
        self.query += " " + self.query_where(where)

    def query_select(self, table, columns, where=None, order=None, asc=True):
        """
        Create the select query
        table = nome da tabela
        columns = colunas a serem selecionadas
        where = lista com as tuplas de where's
        order: nome da coluna que deve ser ordenada com 'desc'
        desc: ordem alfabetica de organizacao
        """
        # We start the query as select
        self.query = "SELECT"

        # Then we should check the columns to see what we should run
        if columns == "*":
            self.query += " *"
        else:
            # If it is a list we add each column to the query
            self.query += " " + self.order_with_separator(columns)

        # Then we add the statement from table
        self.query += " FROM `" + table + "`"

        # If the where is not none we add the where query
        if where is not None:
            self.query += " " + self.query_where(where)

        # If the order is not empty we add the order
        if order is not None:
            self.query += "ORDER BY " + order

            # If the desc is true
            if asc:
                self.query += " ASC"
            else:
                self.query += " DESC"

    def query_columns(self, table):
        # Coloca em query o nome das colunas da tabela
        self.query = "DESCRIBE `" + table + "`"
