# start stockAggregatesStore
STOCK_AGGREGATES_STORE="stock-aggregates-store"
STOCK_AGGREGATES_STORE_CONTAINER="stock-aggregates-store-container"

docker stop "$STOCK_AGGREGATES_STORE_CONTAINER" 2>/dev/null || true
docker rm "$STOCK_AGGREGATES_STORE_CONTAINER" 2>/dev/null || true

docker rmi "$STOCK_AGGREGATES_STORE" 2>/dev/null || true

docker build -t "$STOCK_AGGREGATES_STORE" -f stockAggregatesStore/Dockerfile .
docker run --name "$STOCK_AGGREGATES_STORE_CONTAINER" -p 8080:8080 -d "$STOCK_AGGREGATES_STORE" 
docker logs -f "$STOCK_AGGREGATES_STORE_CONTAINER"