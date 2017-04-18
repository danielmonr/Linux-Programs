var accounts = require('../models/categories');

module.exports.show = function(req, res, next){
	var categ;
	accounts.getAll(function(err, response){
		if(err){
			console.log('QUERY attempt failed.');
			return res.end();
		}
		else if(response.status.localeCompare('ERROR') == 0){
			console.log('No categories');
		}
		else{
			categ = response.data;
		}
		//console.log('categ:');
		//console.log(categ);
		return res.render('categories', {categories: categ});
	});
}

module.exports.create = function(req, res, next){
	accounts.new(req.body.name, req.body.priority, function(err, response){
		if(err){
			console.log('QUERY attempt failed.');
			return res.end();
		}
		else{
			return res.redirect('/categories');
		}
	});
}