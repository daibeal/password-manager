import React, { useState } from 'react';
import { deletePassword } from '../api';
import { TextField, Button, Typography, Box } from '@mui/material';

const DeletePassword = () => {
  const [site, setSite] = useState('');
  const [username, setUsername] = useState('');
  const [message, setMessage] = useState('');

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      await deletePassword(site, username);
      setMessage('Password deleted successfully');
    } catch (error) {
      setMessage('Failed to delete password');
    }
  };

  return (
    <Box>
      <Typography variant="h4" component="h1" gutterBottom>
        Delete Password
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
          Delete Password
        </Button>
      </form>
      {message && <Typography variant="body1" color="error">{message}</Typography>}
    </Box>
  );
};

export default DeletePassword;