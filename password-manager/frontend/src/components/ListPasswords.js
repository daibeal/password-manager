import React, { useState, useEffect } from 'react';
import { listPasswords } from '../api';
import { Typography, Box, List, ListItem, ListItemText } from '@mui/material';

const ListPasswords = () => {
  const [passwords, setPasswords] = useState([]);
  const [message, setMessage] = useState('');

  useEffect(() => {
    const fetchPasswords = async () => {
      try {
        const response = await listPasswords();
        setPasswords(response.data);
        setMessage('');
      } catch (error) {
        setMessage('Failed to list passwords');
      }
    };

    fetchPasswords();
  }, []);

  return (
    <Box>
      <Typography variant="h4" component="h1" gutterBottom>
        List Passwords
      </Typography>
      {message && <Typography variant="body1" color="error">{message}</Typography>}
      <List>
        {passwords.map((password, index) => (
          <ListItem key={index}>
            <ListItemText primary={password} />
          </ListItem>
        ))}
      </List>
    </Box>
  );
};

export default ListPasswords;