const express = require("express");
const bodyParser = require('body-parser');
const request = require('request');


const app = express();

// parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: false }))

// parse application/json
app.use(bodyParser.json())

app.get("/", (req, res) => {
  res.send("Express on Vercel");
});

app.post("/", (req, res) => {
  const { uri } = req.body;
  request({ uri: uri, followRedirect: false }, function (err, httpResponse) {
      res.send(httpResponse.headers.location);
    }
  );
});

app.listen(5000, () => {
  console.log("Running on port 5000.");
});

// Export the Express API
module.exports = app;