'''
Predefined Sqlite3 statements for storing stock data.
'''

class SqliteQueries:

    @staticmethod
    def create_aggregate_table(table_name: str) -> str:
        return f''' 
            CREATE TABLE IF NOT EXISTS {table_name} (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                ticker CHAR(4) NOT NULL CHECK(length(ticker) <= 4),
                timestamp LONG NOT NULL,
                close FLOAT NOT NULL,
                high FLOAT NOT NULL,
                low FLOAT NOT NULL,
                transactions INT NOT NULL,
                open FLOAT NOT NULL,
                volume FLOAT NOT NULL,
                vwap FLOAT NOT NULL
            ) '''


    @staticmethod
    def show_tables() -> str:
        return "SELECT name FROM sqlite_master WHERE type='table'"
    
    @staticmethod
    def drop_table(table_name: str) -> str:
        return f"DROP TABLE {table_name}"

    @staticmethod
    def store_aggregate_info(table_name: str,
                             ticker: str,
                             timestamp: int,
                             close: float,
                             high: float,
                             low: float,
                             transactions: float,
                             open: float,
                             volume: float,
                             vwap: float) -> str:
        return f'''
            INSERT INTO {table_name} (
                ticker,
                timestamp,
                close,
                high,
                low,
                transactions,
                open,
                volume,
                vwap
            ) VALUES (
                '{ticker}', 
                {timestamp}, 
                {close},
                {high},
                {low},
                {transactions},
                {open},
                {volume},
                {vwap}
            ) '''
    
    @staticmethod
    def count_rows(table_name: str) -> str:
        return f"SELECT COUNT(*) FROM {table_name}"  