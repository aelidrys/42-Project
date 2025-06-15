FROM nginx:alpine


RUN mkdir /etc/nginx/ssl
RUN apk update && apk add openssl
RUN openssl req -x509 -nodes -out /etc/nginx/ssl/trans.crt -keyout /etc/nginx/ssl/trans.key \
    -subj "/C=MR/ST=none/L=benguerir/O=UM6P/OU=1337/CN=abouassi.42.fr/UID=abouassi" 

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]