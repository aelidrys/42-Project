#!/bin/sh
cd /var/www/wordpress
while ! mariadb -h mariadb -u  aelidrys -p$SQL_PASSWORD ;do
	echo "waiting..."
	sleep 2
done
echo "User \"aelidrys\" conected succsefll.."

sed -i 's|listen = /run/php/php7.4-fpm.sock|listen = wordpress:9000|' /etc/php/7.4/fpm/pool.d/www.conf

wp config create	--allow-root \
		--dbname=$SQL_DATABASE \
		--dbuser=$SQL_USER \
		--dbpass=$SQL_PASSWORD \
		--dbhost=mariadb:3306 \
        --path='/var/www/wordpress'

wp core install --allow-root \
		--url=${DOMAIN_NAME} --title=${WP_TITLE} \
		--admin_user=${WP_USER} --admin_password=${WP_PASSWD} \
		--admin_email=${WP_EMAIL} --skip-email

wp user create $WP_USER2 $WP_EMIL2 --role=${USER_ROLE} --user_pass=${WP_PASSWD2} --allow-root

chmod 777 -R /var/www/wordpress/wp-content/uploads

php-fpm7.4 -F
