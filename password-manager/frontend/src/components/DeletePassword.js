import React, { useState } from 'react';
import { deletePassword } from '../api';

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
    <div>
      <h2>Delete Password</h2>
      <form onSubmit={handleSubmit}>
        <div>
          <label>Site:</label>
          <input type="text" value={site} onChange={(e) => setSite(e.target.value)} />
        </div>
        <div>
          <label>Username:</label>
          <input type="text" value={username} onChange={(e) => setUsername(e.target.value)} />
        </div>
        <button type="submit">Delete Password</button>
      </form>
      {message && <p>{message}</p>}
    </div>
  );
};

export default DeletePassword;