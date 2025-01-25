import { useState } from 'react';
import { AppBar, Drawer, Typography, Toolbar, Link } from '@mui/material';
import { useTheme } from '@mui/material/styles';
import GitHubIcon from '@mui/icons-material/GitHub';
import TickerSelector from './TickerSelector';
import StockChart from './StockChart';
import StationaryTestDisplay from './StationaryTestDisplay';
import Pear2 from '../assets/images/Pear2.png';


export default function PairDashboard() {
  const theme = useTheme();
  const [selectedTickers, setSelectedTickers] = useState<string[]>([]);

  return (
    <div>
      <AppBar position="fixed" sx={{ zIndex: (theme) => theme.zIndex.drawer + 1 }}>
        <Toolbar variant="dense" sx={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
          <div style={{ display: 'flex', alignItems: 'center' }}>
              <img src={Pear2} style={{ width: 50, height: 50 }} />
            <Typography variant="h4">The Callery Pear</Typography>
          </div>
          <Link target="_blank" href="https://github.com/J3r0m3L/Callery">
            <GitHubIcon sx={{ color: theme.palette.grey[50] }}/>
          </Link>
        </Toolbar>
      </AppBar>
      <Drawer
        variant="permanent"
        anchor="left"
        PaperProps={{
          sx: { width: "200px", marginTop: '50px' }
        }}
      >
        <TickerSelector setSelectedTickers={setSelectedTickers}/>
      </Drawer>
      <div style={{ marginLeft: '200px', marginTop: '50px', padding: '10px 10px 0px 10px' }}>
        <StockChart tickers={selectedTickers} /> 
      </div>
      <div style={{ marginLeft: '200px', padding: '10px' }}>
        <StationaryTestDisplay tickers={selectedTickers} />
      </div>
    </div>
  );
}