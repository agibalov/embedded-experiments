import { Routes, Route, Link as RouterLink } from 'react-router-dom';
import { Box, HStack, Button, VStack } from '@chakra-ui/react';
import Home from './pages/Home';
import Calculator from './pages/Calculator';

function App() {
  return (
    <VStack>
      <Box p={3}>
        <HStack>
          <RouterLink to="/">          
            <Button>Home</Button>
          </RouterLink>
          <RouterLink to="/calculator">          
            <Button>Calculator</Button>
          </RouterLink>
        </HStack>  
      </Box>
      <Box>
        <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/calculator" element={<Calculator />} />
          </Routes>
      </Box>
    </VStack>
  );
}

export default App;