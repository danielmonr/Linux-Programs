var express = require('express');
var bodyParser = require('body-parser');
var router = express.Router();

var index = require('../controllers/index');

router.get('/login', function(req, res, next){
	console.log("############## Login - router");
	index.login(req, res, next);
});

module.exports = router;