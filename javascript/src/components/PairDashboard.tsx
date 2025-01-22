import { useState } from 'react';
import { AppBar, Drawer, Typography, Toolbar, Link } from '@mui/material';
import { useTheme } from '@mui/material/styles';
import GitHubIcon from '@mui/icons-material/GitHub';
import AppleIcon from '@mui/icons-material/Apple';
// import { StockAggregatesStore } from '../agent';
import TickerSelector from './TickerSelector';


export default function PairDashboard() {
  const theme = useTheme();
  const [selectedTickers, setSelectedTickers] = useState<string[]>([]);


  console.log('selectedTickers', selectedTickers);

  return (
    <div>
      <AppBar position="fixed" sx={{ zIndex: (theme) => theme.zIndex.drawer + 1 }}>
        <Toolbar variant="dense" sx={{ display: 'flex', justifyContent: 'space-between' }}>
          <div style={{ display: 'flex', alignItems: 'center' }}>
            <AppleIcon sx={{ color: theme.palette.success.main }} />
            <Typography variant="h4">The Callery Pear</Typography>
          </div>
          <Link target="_blank" href="https://github.com/J3r0m3L/Callery">
          <GitHubIcon />
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
            <div style={{ background: 'blue', marginLeft: '50px', marginTop: '50px' }}>
            <h1>Hello World! 2</h1>
            </div>
        </div>
    );
}