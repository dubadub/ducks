require 'sinatra'; get '/cmd' { `./coffinctl #{params.keys.first}` }
