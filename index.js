var request = require('request');

var uri = 'http://bit.ly/2fR0xVj';
request(
  {
    uri: uri,
    followRedirect: false,
  },
  function (err, httpResponse) {
    if (err) {
      return console.error(err);
    }
    console.log(httpResponse.headers.location || uri);
  }
);
