var db = require('../config/db');

exports.getAll = function(id, callback){
	db.get().query('SELECT * FROM entry_lines where id_a='+id+';', function(err, result){
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
	db.get().query('SELECT * FROM entry_lines where id='+id+';', function (err, result){
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

exports.create = function(concept,value, date, flags, account,callback){
	//console.log('INSERT INTO entry_lines (concept, value, date, flags, id_a) VALUES (\"'+concept+'\",'+value+',\"'+date+'\",'+flags+', '+account+');');
	db.get().query('INSERT INTO entry_lines (concept, value, date, flags, id_a) VALUES (\"'+concept+'\",'+value+',\"'+date+'\",'+flags+', '+account+');', function(err, result){
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