var accounts = require('../models/accounts');
var categories = require('../models/categories');

module.exports.show = function(req, res, next){
	var accs;
	accounts.getAll(req.session.id, function(err, response){
		if(err){
			console.log('QUERY attempt failed.');
			return res.end();
		}
		else if(response.status.localeCompare('ERROR') == 0){
			console.log('No accounts');
		}
		else{
			accs = response.data;
		}
		//console.log('accs:');
		//console.log(accs);
		return res.render('accounts', {accounts: accs});
	});
}

module.exports.create = function(req, res, next){
	accounts.new(req.body.name, req.body.category, req.session.id, function(err, response){
		if(err){
			console.log('QUERY attempt failed.');
			return res.end();
		}
		else{
			return res.redirect('/accounts');
		}
	});
}

module.exports.showNew = function(req, res, next){
	var category;
	categories.getAll(function(err, response){
		if(err){
			console.log('QUERY attempt failed.');
		}
		else{
			category = response.data;
			res.render('newaccount', {categories: category});
			//return res.redirect('/accounts');
		}
	});
}