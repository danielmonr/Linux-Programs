var db = require('../config/db');

exports.login = function(username, passowrd, callback){
	db.get().query('SELECT * FROM users where username=\"'+username+'\" AND password=\"'+passowrd+'\";', function(err, result){
		var response ={status:''};
		if(err){
			return callback(err);
		}
		if(result && result.length > 0){
			response.status = "SUCCESS";
			response.data = result[0];
		}
		else{
			response.status = "ERROR";
		}
		//console.log(response);
		return callback(null, response);
	});
}

exports.newUser = function(username, password, callback){
	db.get().query('INSERT INTO users (username, password) VALUES (\"'+username+'\", \"'+password+'\");', function(err, result){
		var response ={status:''};
		if(err){
			return callback(err);
		}
		else{
			response.status = "SUCCESS";
		}
		//console.log(response);
		return callback(null, response);
	});
}