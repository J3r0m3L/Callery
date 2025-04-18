import { useEffect, useState } from 'react';
import { StockAlgorithms } from '../agent';
import { Typography } from '@mui/material';


type StationaryTestDisplayProps = {
  tickers: string[];
};

export default function StationaryTestDisplay({ tickers }: StationaryTestDisplayProps) {
  const [tStats, setTStats] = useState<Number[]>([]);

  useEffect(() => {
    Promise.all(tickers.map((ticker) => StockAlgorithms.performDickyFullerTest(ticker, 1)))
      .then((responses) => {
        const tmpTStats: Number[] = [];
        responses.forEach((response) => {
          tmpTStats.push(response?.body?.tStat);
        });
        setTStats(tmpTStats);
      });
  }, [tickers]);

  if (!tickers.length) return null;
  return (
    <div>
      <Typography variant="h6">Augmented Dicky Fuller Test Statistics:</Typography>
      {
        tStats.map((tStat, i) => (
          <Typography key={i}>{`${tickers[i]}:${tStat}`}</Typography>
        ))
      }
    </div>
  );

}