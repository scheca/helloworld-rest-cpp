FROM debian:bullseye-slim

EXPOSE 8080

COPY build/dist/bin/server .

CMD [ "sh", "-c", "/server" ]
