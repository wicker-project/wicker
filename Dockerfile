FROM redhat/ubi8:8.6-990
RUN mkdir -p /repos
EXPOSE 9808

#upgrade repos
RUN yum upgrade -y
RUN dnf upgrade -y

#install developer tool stuffs
RUN yum install git -y
RUN yum install cmake -y
RUN yum install clang -y
RUN yum install llvm-toolset -y
RUN yum install gcc -y

#install catch 2 from source
RUN cd /tmp; git clone https://github.com/catchorg/Catch2.git; cd Catch2; cmake -Bbuild -H. -DBUILD_TESTING=OFF; cmake --build build/ --target install
RUN subscription-manager repos --enable codeready-builder-for-rhel-8-$(arch)-rpms -y; dnf install https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm -y
