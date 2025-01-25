import PairDashboard from './components/PairDashboard';
import CssBaseline from '@mui/material/CssBaseline';
import { ThemeProvider } from '@mui/material/styles';
import { GlobalStyles } from '@mui/system';
import { theme } from './theme';

export default function App() {
  return (
    <ThemeProvider theme={theme}>
      <CssBaseline />
      <GlobalStyles
        styles={{
          '::-webkit-scrollbar': {
            width: '7px',
          },
          '::-webkit-scrollbar-track': {
            background: 'transparent',
          },
          '::-webkit-scrollbar-thumb': {
            background: '#888',
            borderRadius: '6px',
          },
          '::-webkit-scrollbar-thumb:hover': {
            background: '#555',
          },
        }}
      />
      <PairDashboard />;
    </ThemeProvider>
  );
}