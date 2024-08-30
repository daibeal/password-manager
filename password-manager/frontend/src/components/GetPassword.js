import React, { useState } from 'react';
import { getPassword } from '../api';

const GetPassword = () => {
  const [site, setSite] = useState('');
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [message, setMessage] = useState('');

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      const response = await getPassword(site, username);
      setPassword(response.data);
      setMessage('');
    } catch (error) {
      setMessage('Failed to get password');
      setPassword('');
    }
  };

  return (
    <div>
      <h2>Get Password</h2>
      <form onSubmit={handleSubmit}>
        <div>
          <label>Site:</label>
          <input type="text" value={site} onChange={(e) => setSite(e.target.value)} />
        </div>
        <div>
          <label>Username:</label>
          <input type="text" value={username} onChange={(e) => setUsername(e.target.value)} />
        </div>
        <button type="submit">Get Password</button>
      </form>
      {password && <p>Password: {password}</p>}
      {message && <p>{message}</p>}
    </div>
  );
};

export default GetPassword;