var express = require('express');
var router = express.Router();

var controller = require('../controllers/entry_lines');

router.post('/new', function(req, res, next){
	controller.create(req, res, next);
});

router.use('/:account', function(req, res, next){
	controller.auth(req, res, next);
});

router.get('/:account/new', function(req, res, next){
	res.render('newentry', {account: req.params.account});
});

router.get('/:account', function(req, res, next){
	controller.show(req, res, next);
	//res.render('entries', {name: "singular"});
});

module.exports = router;