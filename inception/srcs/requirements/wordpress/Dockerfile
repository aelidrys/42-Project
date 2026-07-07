# base image
FROM debian:11

# install wordpress
RUN apt-get update -y && apt-get upgrade -y
RUN apt-get -y install wget
RUN apt-get update -y && apt-get install -y php7.4 php7.4-fpm php7.4-mysql mariadb-client
RUN wget https://fr.wordpress.org/wordpress-6.0-fr_FR.tar.gz -P /var/www
RUN cd /var/www && tar -xzf wordpress-6.0-fr_FR.tar.gz && rm wordpress-6.0-fr_FR.tar.gz

# istall wp-cli
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod 777 wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp
RUN mkdir /run/php


COPY ./script.sh .
RUN chmod +x script.sh

EXPOSE 9000

CMD [ "./script.sh"]