import React, { useState } from 'react';
import { getPassword } from '../api';
import { TextField, Button, Typography, Box } from '@mui/material';

const GetPassword = () => {
  const [site, setSite] = useState('');
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [message, setMessage] = useState('');

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      const response = await getPassword(site, username);
      setPassword(response.data.password);
      setMessage('');
    } catch (error) {
      setMessage('Failed to get password');
      setPassword('');
    }
  };

  return (
    <Box>
      <Typography variant="h4" component="h1" gutterBottom>
        Get Password
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
        <Button type="submit" variant="contained" color="primary" fullWidth>
          Get Password
        </Button>
      </form>
      {password && <Typography variant="body1">Password: {password}</Typography>}
      {message && <Typography variant="body1" color="error">{message}</Typography>}
    </Box>
  );
};

export default GetPassword;