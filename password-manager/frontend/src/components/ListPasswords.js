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
        const passwordsText = response.data;
        const passwordsArray = parsePasswords(passwordsText);
        setPasswords(passwordsArray);
        setMessage('');
      } catch (error) {
        setMessage('Failed to list passwords');
      }
    };

    fetchPasswords();
  }, []);

  const parsePasswords = (text) => {
    const lines = text.split('\n');
    return lines.map(line => {
      const [sitePart, usernamePart, passwordPart] = line.split(', ');
      const site = sitePart.split(': ')[1];
      const username = usernamePart.split(': ')[1];
      const password = passwordPart.split(': ')[1];
      return { site, username, password };
    });
  };

  return (
    <Box>
      <Typography variant="h4" component="h1" gutterBottom>
        List Passwords
      </Typography>
      {message && <Typography variant="body1" color="error">{message}</Typography>}
      <List>
        {passwords.map((password, index) => (
          <ListItem key={index}>
            <ListItemText
              primary={`Site: ${password.site}`}
              secondary={`Username: ${password.username}, Password: ${password.password}`}
            />
          </ListItem>
        ))}
      </List>
    </Box>
  );
};

export default ListPasswords;