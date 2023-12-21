// server.js

const express = require('express');
const bodyParser = require('body-parser');
const mqtt = require('mqtt');
const cors = require('cors')

const app = express();
const port = 3000 || process.env.PORT;

app.use(cors())
// Create an MQTT client
const mqttClient = mqtt.connect('mqtt://broker.hivemq.com');

// Middleware to parse JSON in request body
app.use(bodyParser.json());

// Route to receive message from the React app
app.post('/send-message', (req, res) => {
    const dataFromReact = req.body;

    // Publish the received data to MQTT
    const message = JSON.stringify(dataFromReact);
  // Publish the message to the MQTT broker
  mqttClient.publish('Sami',message, (err) => {
    if (err) {
      console.error('Error publishing message to MQTT:', err);
      return res.status(500).json({ error: 'Internal Server Error' });
    }

    console.log('Message published to MQTT:', message);
    res.json({ success: true });
  });
});

// Start the Express server
app.listen(port, () => {
  console.log(`Server is running on ${port}`);
});
