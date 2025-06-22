#
# To build and run:
#     docker build --tag buildandrunonalpine .
#     docker run --interactive --tty --rm --publish 8080:8080 buildandrunonalpine
#
# Then from another terminal:
#     curl http://localhost:8080
#

FROM alpine:latest

RUN apk add build-base

COPY makefile .
COPY webserver.c .

RUN make

ENTRYPOINT ["./webserver"]
