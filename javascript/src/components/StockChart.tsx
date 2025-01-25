import React, { useEffect, useState } from 'react';
import { LineChart, Line, XAxis, YAxis, ResponsiveContainer, Legend } from 'recharts';
import { StockAggregatesStore } from '../agent';

type StockChartProps = {
  tickers: string[];
};

export default function StockChart({ tickers }: StockChartProps) {
  // todo: need to define via msg object in typedef
  const [stockPrices, setStockPrices] = useState<any[]>([]);

  useEffect(() => {
    Promise.all(tickers.map((ticker) => StockAggregatesStore.queryStockAggregatesTable({ ticker })))
      .then((responses) => {
        const timestampToTicker = [new Map(), new Map()];
        const timestamps: any = new Set();

        responses.forEach((response, i) => {
          const highs = new Map();
          response?.body?.msgs.forEach((msg: any) => {
            highs.set(msg.timestamp, msg.high);
            timestamps.add(msg.timestamp) 
          });
          timestampToTicker[i] = highs;
        });

        const orderedTimestamps: string[] = Array.from(timestamps);
        orderedTimestamps.sort((a: string, b: string) => a.localeCompare(b));

        setStockPrices(orderedTimestamps.map((ts) => {
          const date = new Date(parseInt(ts, 10));
          const dataPoint: any = {
            date: `${date.getMonth()}/${date.getDate()}/${date.getFullYear()}`,
          };
          if (tickers.length >= 1) dataPoint[tickers[0]] = timestampToTicker[0].has(ts) ? timestampToTicker[0].get(ts) : null;
          if (tickers.length >= 2) dataPoint[tickers[1]] = timestampToTicker[1].has(ts) ? timestampToTicker[1].get(ts) : null;
          return dataPoint;
        }));
      });
  }, [tickers]);

  return (
    <ResponsiveContainer width="100%" height={300}>
      <LineChart data={Array.from(stockPrices) }>
        <XAxis dataKey="date" />
        <YAxis />
        { tickers.length >= 1 ? <Legend /> : null }
        <Line type="monotone" dataKey={tickers[0]} stroke="#fdd835" dot={false} />
        <Line type="monotone" dataKey={tickers[1]} stroke="#26c6da" dot={false} />
      </LineChart>
    </ResponsiveContainer>
  );
}