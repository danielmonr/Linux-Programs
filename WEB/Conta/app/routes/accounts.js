var express = require('express');
var router = express.Router();

var controller = require('../controllers/accounts');

router.get('/',function(req, res, next){
	controller.show(req, res, next);
	//res.render('accounts');
});

router.get('/new', function(req, res, next){
	controller.showNew(req, res, next);
});

router.post('/new', function(req, res, next){
	//console.log("CREATING ACCOUNT");
	controller.create(req, res, next);
});

module.exports = router;
