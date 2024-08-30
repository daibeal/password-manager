import React from 'react';
import { BrowserRouter as Router, Route, Routes, Link } from 'react-router-dom';
import AddPassword from './components/AddPassword';
import GetPassword from './components/GetPassword';
import UpdatePassword from './components/UpdatePassword';
import DeletePassword from './components/DeletePassword';
import ListPasswords from './components/ListPasswords';

const App = () => {
  return (
    <Router>
      <div>
        <nav>
          <ul>
            <li><Link to="/add">Add Password</Link></li>
            <li><Link to="/get">Get Password</Link></li>
            <li><Link to="/update">Update Password</Link></li>
            <li><Link to="/delete">Delete Password</Link></li>
            <li><Link to="/list">List Passwords</Link></li>
          </ul>
        </nav>
        <Routes>
          <Route path="/add" element={<AddPassword />} />
          <Route path="/get" element={<GetPassword />} />
          <Route path="/update" element={<UpdatePassword />} />
          <Route path="/delete" element={<DeletePassword />} />
          <Route path="/list" element={<ListPasswords />} />
        </Routes>
      </div>
    </Router>
  );
};

export default App;