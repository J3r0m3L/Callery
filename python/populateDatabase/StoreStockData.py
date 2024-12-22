import sqlite3
from SqliteQueries import SqliteQueries
from polygon import RESTClient # type: ignore
from dotenv import load_dotenv # type: ignore
import os
from tqdm import tqdm # type: ignore
from timeit import default_timer as timer

cyber_security_stocks = ["CRWD", "PANW", "ZS", "FTNT", "OKTA", "CYBR", "AKAM", "CHKP", "S", "GEN", 
                         "RPD", "QLYS", "ATEN", "DDOG", "NET", "SWI", "IBM", "VRNS", "TENB", "KEYS",
                         "CSCO", "AVGO", "DELL", "VMW"]

ai_stocks = ["NVDA", "AMD", "TSM", "SOUN", "PLTR", "GOOG", "SMCI", "ARM", "S", "AI", "MSFT", "IBM",
             "MU", "TSLA", "AAPL", "ADBE", "AMZN", "JPM", "BBAI", "SNOW", "VRT"]


def query_polygon_stock_api(ticker: str, from_="2020-01-01", to="2022-01-01") -> list:
    load_dotenv()
    api_key = os.getenv("POLYGON_IO_API_KEY")
    client = RESTClient(api_key=api_key)

    limit = 1000000000
    aggregates = []
    print(f"Retrieving stock aggregates for {ticker}")
    for agg in tqdm(client.list_aggs(ticker=ticker,
                                multiplier=1,
                                timespan="minute",
                                from_=from_,
                                to=to,
                                limit=1000000000)):
        aggregates.append(agg)
    
    if len(aggregates) == limit:
        raise Exception(f"Limit of {limit} was reached. Data was likely truncated.")
    return aggregates

def store_polygon_stock_data(ticker: str, aggregates: list) -> int:
    connection = sqlite3.connect("StockData.db")
    cursor = connection.cursor()

    table_name = "StockAggregates"
    cursor.execute(SqliteQueries.create_aggregate_table(table_name))
    cursor.execute(SqliteQueries.count_rows(table_name))
    initial_num_entries = cursor.fetchone()[0]

    print(f"Storing stock aggregates for {ticker}")
    for agg in tqdm(aggregates):
        cursor.execute(SqliteQueries.store_aggregate_info(table_name=table_name,
                                                          ticker=ticker,
                                                          timestamp=agg.timestamp,
                                                          close=agg.close,
                                                          high=agg.high,
                                                          low=agg.low,
                                                          transactions=agg.transactions,
                                                          open=agg.open,
                                                          volume=agg.volume,
                                                          vwap=agg.vwap))
        
    cursor.execute(SqliteQueries.count_rows(table_name))
    final_num_entries = cursor.fetchone()[0]
    num_entries_stored = final_num_entries - initial_num_entries

    connection.commit()
    cursor.close()
    connection.close()

    if num_entries_stored != len(aggregates):
        raise Exception(f"Incorrect number of entries saved: {num_entries_stored}. Expected: {len(aggregates)}")
    return num_entries_stored        

if __name__ == "__main__":
    start = timer()
    stocks = ai_stocks + list(set(cyber_security_stocks) - set(ai_stocks))

    for stock in stocks:
        aggregates = query_polygon_stock_api(stock)
        store_polygon_stock_data(stock, aggregates)
    print(f"Elapsed Time: {timer() - start}")