var users = require('../models/users');

module.exports.login = function(req, res, next){
	var user;
	users.login(req.body.username, req.body.password, function(err, response){
		if(err){
			console.log('Login attempt failed.');
			return res.end();
		}
		else if(response.status.localeCompare('ERROR') == 0){
			console.log('Login attempt failed - WRONG CREDENTIALS.');
			return res.end();
		}
		else{
			//console.log(response.data.id);
			req.session.id = response.data.id;
			req.session.username = response.data.username;
		}

		return res.redirect('/home');

	});
}

module.exports.signin = function(req, res, next){
	users.newUser(req.body.username, req.body.password, function(err, response){
		if(err){
			console.log('Sign in attempt failed.');
			//return res.end();
		}
	});
	return res.redirect('/login');
}