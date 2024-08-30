import React, { useState } from 'react';
import { addPassword } from '../api';

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
    <div>
      <h2>Add Password</h2>
      <form onSubmit={handleSubmit}>
        <div>
          <label>Site:</label>
          <input type="text" value={site} onChange={(e) => setSite(e.target.value)} />
        </div>
        <div>
          <label>Username:</label>
          <input type="text" value={username} onChange={(e) => setUsername(e.target.value)} />
        </div>
        <div>
          <label>Password:</label>
          <input type="password" value={password} onChange={(e) => setPassword(e.target.value)} />
        </div>
        <button type="submit">Add Password</button>
      </form>
      {message && <p>{message}</p>}
    </div>
  );
};

export default AddPassword;