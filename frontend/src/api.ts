import axios from "axios";

const API_URL = import.meta.env.VITE_API_URL || "http://localhost:8080";

export const getMAAccount = () => axios.get(`${API_URL}/api/ma/account`).then(r => r.data);
export const getRSIAccount = () => axios.get(`${API_URL}/api/rsi/account`).then(r => r.data);
export const getMAPositions = () => axios.get(`${API_URL}/api/ma/positions`).then(r => r.data);
export const getRSIPositions = () => axios.get(`${API_URL}/api/rsi/positions`).then(r => r.data);
export const getMAOrders = () => axios.get(`${API_URL}/api/ma/orders`).then(r => r.data);
export const getRSIOrders = () => axios.get(`${API_URL}/api/rsi/orders`).then(r => r.data);
export const getClock = () => axios.get(`${API_URL}/api/clock`).then(r => r.data);
