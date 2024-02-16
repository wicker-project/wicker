FROM redhat/ubi8:8.6-990
RUN mkdir -p /repos
EXPOSE 9808

RUN yum install cmake
RUN yum install clang