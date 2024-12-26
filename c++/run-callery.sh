# start stockAggregatesStore
STOCK_AGGREGATES_STORE="stock-aggregates-store"
STOCK_AGGREGATES_STORE_CONTAINER="stock-aggregates-store-container"

docker stop "$STOCK_AGGREGRATES_STORE_CONTAINER" 2>/dev/null || true
docker rm "$STOCK_AGGREGATES_STORE_CONTAINER" 2>/dev/null || true

docker rmi "$STOCK_AGGREGATES_STORE" 2>/dev/null || true

docker build -t "$STOCK_AGGREGATES_STORE" -f stockAggregatesStore/Dockerfile .
docker run --name "$STOCK_AGGREGATES_STORE_CONTAINER" -d "$STOCK_AGGREGATES_STORE" 
