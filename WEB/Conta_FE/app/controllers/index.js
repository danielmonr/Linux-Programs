var users = require('../models/users');

module.exports.login = function(req, res, next){
	console.log("############### login controller");
	users.getUserL('danielmonr', '123', function(err, response){
		if(err){
			console.log('error en el login');
		}
		else if(response.status.localeCompare('ERROR') == 0){
			console.log('USER NOT FOUND');
			//return res.send('{}');
			res.json(response);
		}
		else{
			res.json(response);
		}
	});
}