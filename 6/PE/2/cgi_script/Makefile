all:
	g++ -O2 -s main.cpp -o railroads.cgi -lcgicc -lpqxx
	rm -rf /var/www/railroad/*
	cp *.cgi /var/www/railroad
	cp index.html style.css script.js /var/www/railroad
clean:
	rm -rf *.cgi