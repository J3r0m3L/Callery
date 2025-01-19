import { useEffect } from 'react';
import { AppBar, Drawer, Typography, Toolbar } from '@mui/material';
import { useTheme } from '@mui/material/styles';
import GitHubIcon from '@mui/icons-material/GitHub';
import AppleIcon from '@mui/icons-material/Apple';
import { StockAggregatesStore } from '../agent';


export default function PairDashboard() {
  const theme = useTheme();

  useEffect(() => {
    StockAggregatesStore.getTickers()
      .then((response: any) => {
        console.log('response', response);
      });
  }, []);



  return (
    <div>
      <AppBar position="fixed" sx={{ zIndex: (theme) => theme.zIndex.drawer + 1 }}>
        <Toolbar variant="dense" sx={{ display: 'flex', justifyContent: 'space-between' }}>
          <div style={{ display: 'flex', alignItems: 'center' }}>
            <AppleIcon sx={{ color: theme.palette.success.main }} />
            <Typography variant="h5">The Callery Pear</Typography>
          </div>
          <GitHubIcon />
        </Toolbar>
      </AppBar>
      <Drawer
                variant="permanent"
                anchor="left"
                PaperProps={{
                    sx: { width: "50px" }
                }}
            >
                <div style={{ height: '50px' }}/>
                <div>Hello Everyone!</div>
            </Drawer>
            <div style={{ background: 'blue', marginLeft: '50px', marginTop: '50px' }}>
            <h1>Hello World! 2</h1>
            </div>
        </div>
    );
}