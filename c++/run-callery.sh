NETWORK="callery-network"
# docker network prune --filter name="$NETWORK" --force
# for now start services in specific order since that ties to network
docker network create --subnet="172.20.0.0/16" "$NETWORK" 2>/dev/null || true

if [ "$#" -eq 0 ]; then
    echo "Please start services one at a time."
    exit 1
fi

if [ "$1" = "sas-only" ] || [ -z "$1" ]; then # start this service 1st
    STOCK_AGGREGATES_STORE="stock-aggregates-store"
    STOCK_AGGREGATES_STORE_CONTAINER="stock-aggregates-store-container"

    docker stop "$STOCK_AGGREGATES_STORE_CONTAINER" 2>/dev/null || true
    docker rm "$STOCK_AGGREGATES_STORE_CONTAINER" 2>/dev/null || true

    docker rmi "$STOCK_AGGREGATES_STORE" 2>/dev/null || true

    docker build -t "$STOCK_AGGREGATES_STORE" -f stockAggregatesStore/Dockerfile .
    docker run --name "$STOCK_AGGREGATES_STORE_CONTAINER" --network "$NETWORK" -p 8080:8080 -d "$STOCK_AGGREGATES_STORE" 
    # --ip 172.20.0.2/16
    docker logs -f "$STOCK_AGGREGATES_STORE_CONTAINER"
fi

if [ "$1" = "lb-only" ] || [ -z "$1" ]; then # start this service last
    LOAD_BALANCER="load-balancer"
    LOAD_BALANCER_CONTAINER="load-balancer-container"

    docker stop "$LOAD_BALANCER_CONTAINER" 2>/dev/null || true
    docker rm "$LOAD_BALANCER_CONTAINER" 2>/dev/null || true

    docker rmi "$LOAD_BALANCER" 2>/dev/null || true

    docker build -t "$LOAD_BALANCER" -f loadBalancer/Dockerfile .
    docker run --name "$LOAD_BALANCER_CONTAINER" --network "$NETWORK" -p 8081:8081 -d "$LOAD_BALANCER"
    # --ip 172.20.0.4/16 
    docker logs -f "$LOAD_BALANCER_CONTAINER"
fi

if [ "$1" = "sa-only" ] || [ -z "$1" ]; then # start this service 2nd
    STOCK_ALGORITHMS="stock-algorithms"
    STOCK_ALGORITHMS_CONTAINER="stock-algorithms-container"

    docker stop "$STOCK_ALGORITHMS_CONTAINER" 2>/dev/null || true
    docker rm "$STOCK_ALGORITHMS_CONTAINER" 2>/dev/null || true

    docker rmi "$STOCK_ALGORITHMS" 2>/dev/null || true

    docker build -t "$STOCK_ALGORITHMS" -f stockAlgorithms/Dockerfile .
    docker run --name "$STOCK_ALGORITHMS_CONTAINER" --network "$NETWORK" -p 8082:8082 -d "$STOCK_ALGORITHMS"
    # --ip 172.20.0.3/16 
    docker logs -f "$STOCK_ALGORITHMS_CONTAINER"
fi



# output the ip addresses to a file that can be read into Main.cpp of loadBalancer:
# `docker network inspect callery-network > output.txt`