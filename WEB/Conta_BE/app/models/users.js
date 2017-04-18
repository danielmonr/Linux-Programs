var db = require('../config/db');

exports.getUserL = function(username, password, callback){
	console.log("############# login model");
	db.get().query('SELECT * FROM users WHERE username=\'' + username + '\' AND password=\'' + password + '\';', function (err, rows){
		var response = {status: ''};
		if(err){
			console.log('callback:err');
			return callback(err);
		}
		if(rows && rows.length == 1){
			console.log('login query success');
			response.status = "SUCCESS";
			response.user = rows[0];
		}
		else{
			console.log('user not found');
			response.status = "ERROR";
		}
		return callback(null, response);
	});
}