var express = require('express');
var router = express.Router();
// Controller
var controller = require('../controllers/index');

/* GET home page. */
router.get('/', function(req, res, next){
  if(req.session.id){
    res.redirect('/home');
  }
  else{
    res.redirect('/login');
  }
});
router.get('/home', function(req, res, next){
  res.render('home');
});

router.get('/login', function(req, res, next) {
  res.render('login');
});

router.post('/login', function(req, res, next){
  controller.login(req, res, next);
});

router.get('/logout', function(req, res, next){
  req.session = null;
  return res.redirect('/login');
});

router.get('/signin', function(req, res, next){
  res.render('signin');
});

router.post('/signin', function(req, res, next){
  controller.signin(req, res, next);
});

module.exports = router;
