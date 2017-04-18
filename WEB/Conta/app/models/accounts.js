var db = require('../config/db');

exports.getAll = function(id, callback){
	db.get().query('SELECT a.id as id, a.name as name, c.name as category, c.priority as priority FROM accounts as a cross join category as c where a.category=c.id AND a.id_u='+id+';', function(err, result){
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

exports.getOne = function(id, callback){
	db.get().query('SELECT * FROM accounts where id='+id+';', function (err, result){
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

exports.new = function(name, category, user, callback){
	db.get().query('INSERT INTO accounts (name, category, id_u) VALUES (\"'+name+'\",'+category+','+user+');', function(err, response){
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