import { Routes, Route, Link as RouterLink } from 'react-router-dom';
import Home from './Home';
import Calculator from './Calculator';
import { AppBar, Button, Container, Toolbar } from '@mui/material';

export default function App() {
  return (
    <>
      <Container maxWidth="md">
        <AppBar position="static">
          <Toolbar>
            <Button color="inherit" component={RouterLink} to="/">
              Home
            </Button>
            <Button color="inherit" component={RouterLink} to="/calculator">
              Calculator
            </Button>
          </Toolbar>
        </AppBar>
        
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/calculator" element={<Calculator />} />
        </Routes>
      </Container>
    </>
  );
}
