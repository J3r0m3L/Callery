const request = require('superagent');

const baseURL = 'http://0.0.0.0:8081';

class BaseRequest {
    service: string;

    constructor(service: string) {
        this.service = service;
    }

    get(url: string) {
        return request.get(`${baseURL}/${this.service}/${url}`)
        // .set("Access-Control-Allow-Origin", "*");
    }

    post(url: string, body: object) {
        return request.post(`${baseURL}/${this.service}/${url}`).send(body).set('Content-Type', 'application/json');
    }
}

class StockAggregatesStoreApi {
    baseRequest: BaseRequest = new BaseRequest("stockAggregatesStore");

    queryStockAggregatesTable(query: object) {
        return this.baseRequest.post('query', query);
    }

    getTickers() {
        return this.baseRequest.get('tickers');
    }
}

export const StockAggregatesStore = new StockAggregatesStoreApi();
