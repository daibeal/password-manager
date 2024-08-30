import axios from 'axios';

const API_BASE_URL = 'http://localhost:8080';

export const addPassword = (site, username, password) => {
  return axios.post(`${API_BASE_URL}/add_password`, { site, username, password });
};

export const getPassword = (site, username) => {
  return axios.get(`${API_BASE_URL}/get_password`, { params: { site, username } });
};

export const updatePassword = (site, username, newPassword) => {
  return axios.put(`${API_BASE_URL}/update_password`, { site, username, newPassword });
};

export const deletePassword = (site, username) => {
  return axios.delete(`${API_BASE_URL}/delete_password`, { params: { site, username } });
};

export const listPasswords = () => {
  return axios.get(`${API_BASE_URL}/list_passwords`);
};