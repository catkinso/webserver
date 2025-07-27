#
# To build and run:
#     docker build --tag buildandrunonalpine .
#     docker run --interactive --tty --rm --publish 8080:8080 buildandrunonalpine
#
# Then from another terminal:
#     curl http://localhost:8080
#
# In the case of a build error comment out the make and entrypoint, run the docker
# build command again and run bash as the entrypoint from the command line. Then
# from bash make can be run and the files can be edited with vim to aid in
# troubleshooting:
#      docker run --interactive --tty --rm --entrypoint bash buildandrunonalpine
#

FROM alpine:latest

RUN apk add build-base bash vim

COPY makefile .
COPY *.c .
COPY *.h .
COPY *.html .

RUN make

ENTRYPOINT ["./webserver"]
