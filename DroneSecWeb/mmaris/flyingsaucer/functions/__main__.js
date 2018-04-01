const lib = require('lib')({token: 'zYT2ndkPoRfBBawF31AWs6DxjBB4swFS1AZ-lCtY9E0JMk8mWW0CRdLenoJd0RjP'});
const sms = lib.messagebird.sms['@0.1.3'];
/**
* A basic Hello World function
* @param {array} recipients Phone number
* @param {string} body Message body
* @returns {any}
*/
module.exports = (recipients, body, context, callback) => {
  for(let i = 0; i<recipients.length; i++) {
    sms.create({
      recipient: recipients[i],
      body
    }, function(err, result) {
      if (err) {
        return callback(err);
      }
      return callback(null, JSON.stringify(result));
    });
  }
};
