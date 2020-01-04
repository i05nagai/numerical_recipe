FROM ubuntu:16.04

#
# run on the top of repository
#
COPY ci /tmp/ci


RUN \
    apt-get update \
    && /tmp/ci/linux/install_bazel.sh \
    && /tmp/ci/linux/install_buildifier.sh \
    && /tmp/ci/linux/install_clang_format.sh \
    && /tmp/ci/linux/install_gcc.sh \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /tmp/ci

#
# swig
#
ENV SWIG_VERSION=4.0.1
RUN \
    apt-get update \
    # Install Java.
    && apt-get install -y \
        g++ \
        libpcre3  \
        curl \
        build-essential \
        libpcre3-dev \
        software-properties-common \
    && add-apt-repository -y ppa:deadsnakes/ppa \
    && apt-get update

RUN \
    curl \
        -L https://downloads.sourceforge.net/swig/swig-${SWIG_VERSION}.tar.gz \
        -o /tmp/swig-${SWIG_VERSION}.tar.gz \
    && cd /tmp \
    && tar xzf swig-${SWIG_VERSION}.tar.gz

RUN \
    cd /tmp/swig-${SWIG_VERSION} \
    && ./configure --prefix=/usr --without-maximum-compile-warnings \
    && make \
    && make install \
    && install -v -m755 -d /usr/share/doc/swig-4.0.1 \
    && cp -v -R Doc/* /usr/share/doc/swig-4.0.1


#
# python3
#
RUN \
    apt-get install -y \
        software-properties-common \
    && add-apt-repository -y ppa:deadsnakes/ppa \
    && apt-get update \
    && apt-get install -y \
        python3.6 \
        python3.6-dev \
    && apt-get purge -y python3 \
    && apt-get -y autoremove \
    && ln -s /usr/bin/python3.6 /usr/bin/python3

RUN \
    curl https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py \
    && python3 /tmp/get-pip.py \
    && pip3 install pipenv

ENV \
    LC_ALL=C.UTF-8 \
    LANG=C.UTF-8

ENV \
  CXX="g++-4.9" \
  CC="gcc-4.9"
