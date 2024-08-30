import React from 'react';
import { BrowserRouter as Router, Route, Routes, Link } from 'react-router-dom';
import { AppBar, Toolbar, Typography, Button, Container, Box } from '@mui/material';
import AddPassword from './components/AddPassword';
import GetPassword from './components/GetPassword';
import UpdatePassword from './components/UpdatePassword';
import DeletePassword from './components/DeletePassword';
import ListPasswords from './components/ListPasswords';

const App = () => {
  return (
    <Router>
      <AppBar position="static">
        <Toolbar>
          <Typography variant="h6" component="div" sx={{ flexGrow: 1 }}>
            Password Manager
          </Typography>
          <Button color="inherit" component={Link} to="/add">Add Password</Button>
          <Button color="inherit" component={Link} to="/get">Get Password</Button>
          <Button color="inherit" component={Link} to="/update">Update Password</Button>
          <Button color="inherit" component={Link} to="/delete">Delete Password</Button>
          <Button color="inherit" component={Link} to="/list">List Passwords</Button>
        </Toolbar>
      </AppBar>
      <Container>
        <Box my={4}>
          <Routes>
            <Route path="/add" element={<AddPassword />} />
            <Route path="/get" element={<GetPassword />} />
            <Route path="/update" element={<UpdatePassword />} />
            <Route path="/delete" element={<DeletePassword />} />
            <Route path="/list" element={<ListPasswords />} />
          </Routes>
        </Box>
      </Container>
    </Router>
  );
};

export default App;