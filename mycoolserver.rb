require 'sinatra'
 get '/cmd' do
 `./coffinctl #{params.keys.first}` 
end
