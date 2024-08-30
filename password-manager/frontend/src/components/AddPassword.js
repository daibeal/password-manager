import React, { useState } from 'react';
import { addPassword } from '../api';
import { TextField, Button, Typography, Box } from '@mui/material';

const AddPassword = () => {
  const [site, setSite] = useState('');
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [message, setMessage] = useState('');

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      await addPassword(site, username, password);
      setMessage('Password added successfully');
    } catch (error) {
      setMessage('Failed to add password');
    }
  };

  return (
    <Box>
      <Typography variant="h4" component="h1" gutterBottom>
        Add Password
      </Typography>
      <form onSubmit={handleSubmit}>
        <TextField
          label="Site"
          value={site}
          onChange={(e) => setSite(e.target.value)}
          fullWidth
          margin="normal"
        />
        <TextField
          label="Username"
          value={username}
          onChange={(e) => setUsername(e.target.value)}
          fullWidth
          margin="normal"
        />
        <TextField
          label="Password"
          type="password"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          fullWidth
          margin="normal"
        />
        <Button type="submit" variant="contained" color="primary" fullWidth>
          Add Password
        </Button>
      </form>
      {message && <Typography variant="body1" color="error">{message}</Typography>}
    </Box>
  );
};

export default AddPassword;