var db = require('../config/db');

exports.getAll = function(callback){
	db.get().query('SELECT * FROM category;',function(err, result){
		var response ={status:''};
		if(err){
			return callback(err);
		}
		if(result && result.length > 0){
			response.status = "SUCCESS";
			response.data = result;
		}
		else{
			response.status = "ERROR";
		}
		//console.log(response);
		return callback(null, response);
	});
}

exports.new = function(name, priority, callback){
	db.get().query('INSERT INTO category (name, priority) VALUES ('+name+', '+priority+');', function(err, result){
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