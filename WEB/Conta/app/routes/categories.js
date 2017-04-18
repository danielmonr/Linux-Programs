var express = require('express');
var router = express.Router();

var controller = require('../controllers/categories');

router.get('/',function(req, res, next){
	controller.show(req, res, next);
});

router.get('/new', function(req, res, next){
	res.render('newcategory');
});

router.post('/new', function(req, res, next){
	controller.create(req, res, next);
});

module.exports = router;