import React, { useEffect, useState } from 'react';
import { TextField, List, ListItemButton, ListItemText, InputAdornment } from '@mui/material';
import SearchIcon from '@mui/icons-material/Search';
import { StockAggregatesStore } from '../agent';

type TickerSelectorProps = {
  setSelectedTickers: React.Dispatch<React.SetStateAction<string[]>>;
};

export default function TickerSelector({ setSelectedTickers }: TickerSelectorProps) {
  const [tickers, setTickers] = useState<string[]>([]);
  const [filtrate, setFiltrate] = useState<string[]>([]);
  const [chosenTickers, setChosenTickers] = useState<string[]>([]);
  const [search, setSearch] = useState<string>('');

  useEffect(() => {
    StockAggregatesStore.getTickers()
      .then((response: any) => {
        const tmpTickers = response.body?.tickers;
        tmpTickers.sort((a: string, b: string) => a.localeCompare(b));
        setTickers(tmpTickers);
      });
  }, []);

  useEffect(() => {
    if (!tickers.length) return;
    if (!search) {
      setFiltrate([...tickers]);
    }
    const tmpFiltrate = [...tickers];
    setFiltrate(tmpFiltrate.filter((ticker: string) => (ticker.toLowerCase().includes(search.toLowerCase()))));
  }, [search, tickers])

  const addTicker = (ticker: string) => {
    let tmpChosenTickers: string[] = [...chosenTickers];
    if (tmpChosenTickers.includes(ticker)) {
      tmpChosenTickers = tmpChosenTickers.filter((t: string) => t !== ticker);
    } else {
      tmpChosenTickers.push(ticker);
    }

    // for now only two tickers at a time
    if (tmpChosenTickers.length > 2) tmpChosenTickers.shift();
    setChosenTickers(tmpChosenTickers);
    if (!setSelectedTickers) return;
    setSelectedTickers(tmpChosenTickers);
  };

  const tickersList = filtrate.map((ticker, i) => (
    <ListItemButton 
      key={i} 
      onClick={() => addTicker(ticker)}
      selected={chosenTickers.includes(ticker)}
    >
      <ListItemText primary={ticker} />
    </ListItemButton>
  ));

  return (
    <div>
      <TextField 
        onChange={(e) => setSearch(e.target.value)}
        value={search}
        variant="standard"
        slotProps = {{
          input: {
            startAdornment: (
              <InputAdornment position="start">
                <SearchIcon />
              </InputAdornment>
            )
          }
        }}
      />
      <List
        sx={{ 
          height: '300px',
          overflow: 'auto',
        }}
      >
        { tickersList }
      </List>
    </div>
  );
}