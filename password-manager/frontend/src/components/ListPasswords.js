import React, { useState, useEffect } from 'react';
import { listPasswords } from '../api';

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
    <div>
      <h2>List Passwords</h2>
      {message && <p>{message}</p>}
      <ul>
        {passwords.map((password, index) => (
          <li key={index}>{password}</li>
        ))}
      </ul>
    </div>
  );
};

export default ListPasswords;