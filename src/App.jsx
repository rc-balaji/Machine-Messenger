
import React, { useState } from 'react';
import axios from 'axios';
import './App.css';

const App = () => {
  const [message, setMessage] = useState('');

  const sendMessage = async () => {
    try {
      await axios.post('https://machine-server.onrender.com/send-message', { message });
      console.log('Message sent successfully!');
      setMessage("")
    } catch (error) {
      console.error('Error sending message:', error.message);
    }
  };

  return (
    <div className="app-container">
      <header>
        <h1> Machine Messanger</h1>
        <p style={{
          margin:0,
          marginLeft:'130px'
        }} >-- RC Balaji</p>
      </header>
      <main>
        <input
          type="text"
          value={message}
          onChange={(e) => setMessage(e.target.value)}
          placeholder="Enter your message..."
        />
        <button onClick={sendMessage}>Send Message</button>
      </main>
    </div>
  );
};

export default App;
