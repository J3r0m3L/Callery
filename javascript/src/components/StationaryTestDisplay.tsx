import { useEffect, useState } from 'react';
import { StockAggregatesStore, StockAlgorithms } from '../agent';
import { Typography } from '@mui/material';


type StationaryTestDisplayProps = {
  tickers: string[];
};

export default function StationaryTestDisplay({ tickers }: StationaryTestDisplayProps) {
  const [tStats, setTStats] = useState<Number[]>([]);

  useEffect(() => {
    Promise.all(tickers.map((ticker) => StockAggregatesStore.queryStockAggregatesTable({ ticker })))
      .then((stockPrices) => {
        Promise.all(stockPrices.map((sp) => StockAlgorithms.performDickyFullerTest(sp?.body?.msgs.map((msg: any) => msg.high), 1)))
          .then((responses) => {
            const tmpTStats: Number[] = [];
            responses.forEach((response) => {
              tmpTStats.push(response?.body?.tStat);
            });
            setTStats(tmpTStats);
          });
      });
  }, [tickers]);

  console.log('tStats', tStats);

  return (
    <div>
      <Typography>Augmented Dicky Fuller Test Statistics</Typography>
      {
        tStats.map((tStat, i) => (
          <Typography key={i}>{`${tickers[i]}: ${tStat}`}</Typography>
        ))
      }
    </div>
  );

}