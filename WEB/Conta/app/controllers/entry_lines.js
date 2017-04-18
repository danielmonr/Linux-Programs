var entry_lines = require('../models/entry_lines');
var accounts = require('../models/accounts');

module.exports.auth = function(req, res, next){
	accounts.getOne(req.params.account, function(err, response){
		if(err){
			console.log("No such account!");
			res.redirect('/');
		}
		else if(response.status.localeCompare('ERROR') == 0){
			console.log("No such account!");
			res.redirect('/');
		}
		else{
			if(response.data.id_u != req.session.id){
				console.log("Hack attempt!!");
				res.redirect('/');
			}
			else{
				next();
			}
		}
	});
}

module.exports.show = function(req, res, next){
	var entries;
	var a_name;
	entry_lines.getAll(req.params.account, function(err, response){
		if(err){
			console.log('QUERY attempt failed.');
			//return res.end();
		}
		else if(response.status.localeCompare('ERROR') == 0){
			console.log('No entries');
		}
		else{
			entries = response.data;
		}
		accounts.getOne(req.params.account, function(err, response){
			if(err){
				console.log('QUERY attempt failed.');
				//return res.end();
			}
			else if(response.status.localeCompare('ERROR') == 0){
				console.log('No account');
			}
			else{
				a_name = response.data.name;
				//console.log(a_name);
			}
			//console.log('##################entries:');
			//console.log(a_name);
			return res.render('entries', {name: a_name, entries: entries, account: req.params.account});
		});
	});
}

module.exports.create = function(req, res, next){
	entry_lines.create(req.body.concept, req.body.value, req.body.date, req.body.flags, req.body.account, function(err, response){
		if(err){
			console.log('QUERY attempt failed.');
			//return res.end();
		}
		else{
			return res.redirect('/entries/'+req.body.account);
		}
	});
}