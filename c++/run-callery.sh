# start stockAggregatesStore
docker build -t stock-aggregates-store -f stockAggregatesStore/Dockerfile .
docker run stock-aggregates-store 
