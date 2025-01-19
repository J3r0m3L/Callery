import PairDashboard from './components/PairDashboard';
import CssBaseline from '@mui/material/CssBaseline';
import { ThemeProvider } from '@mui/material/styles';
import { theme } from './theme';

export default function App() {
  return (
    <ThemeProvider theme={theme}>
      <CssBaseline />
      <PairDashboard />;
    </ThemeProvider>
  );
}