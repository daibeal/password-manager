import React, { useState } from 'react';
import { updatePassword } from '../api';
import { TextField, Button, Typography, Box } from '@mui/material';

const UpdatePassword = () => {
  const [site, setSite] = useState('');
  const [username, setUsername] = useState('');
  const [newPassword, setNewPassword] = useState('');
  const [message, setMessage] = useState('');

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      await updatePassword(site, username, newPassword);
      setMessage('Password updated successfully');
    } catch (error) {
      setMessage('Failed to update password');
    }
  };

  return (
    <Box>
      <Typography variant="h4" component="h1" gutterBottom>
        Update Password
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
          label="New Password"
          type="password"
          value={newPassword}
          onChange={(e) => setNewPassword(e.target.value)}
          fullWidth
          margin="normal"
        />
        <Button type="submit" variant="contained" color="primary" fullWidth>
          Update Password
        </Button>
      </form>
      {message && <Typography variant="body1" color="error">{message}</Typography>}
    </Box>
  );
};

export default UpdatePassword;