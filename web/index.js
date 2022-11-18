const express = require("express");
var request = require('request');


const app = express();

app.get("/", (req, res) => {
  res.send("Express on Vercel");
});

app.post("/", (req, res) => {
  const { uri } = req;
  return res.send(req);
  
});

app.listen(5000, () => {
  console.log("Running on port 5000.");
});

// Export the Express API
module.exports = app;