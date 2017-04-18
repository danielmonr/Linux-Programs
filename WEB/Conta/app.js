var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var cookieSession = require('cookie-session');
var bodyParser = require('body-parser');
var db = require('./app/config/db');
var handlebars = require('express-handlebars').create({
  defaultLayout: 'main',
  layoutsDir: path.join(__dirname, 'app', 'views', 'layouts')
});

db.connect(function (err){
  console.log('Connecting to DB ...');
  if(err){
    console.log("unable to connect.");
    process.exit(1);
  }
  console.log("connection successful!");
});

var index = require('./app/routes/index');
var users = require('./app/routes/users');
var accounts = require('./app/routes/accounts');
var entry_lines = require('./app/routes/entry_lines');
var categories = require('./app/routes/categories');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'app', 'views'));
app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');

// uncomment after placing your favicon in /public
//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(cookieSession({
  name: 'session',
  keys: ['key1']
}));
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', index);
app.use('/users', users);
app.use('/accounts', accounts);
app.use('/entries', entry_lines);
app.use('/categories', categories);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  res.render('404');
});


// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('500', {errmessage: err.message});
});

module.exports = app;
