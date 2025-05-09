import { Routes, Route, Link as RouterLink } from 'react-router-dom';
import Home from './Home';
import Calculator from './Calculator';
import Chat from './Chat';
import Container from '@mui/material/Container';
import AppBar from '@mui/material/AppBar';
import Toolbar from '@mui/material/Toolbar';
import Button from '@mui/material/Button';

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
            <Button color="inherit" component={RouterLink} to="/chat">
              Chat
            </Button>
          </Toolbar>
        </AppBar>
        
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/calculator" element={<Calculator />} />
          <Route path="/chat" element={<Chat />} />
        </Routes>
      </Container>
    </>
  );
}
