FROM ubuntu:16.04
MAINTAINER i05nagai

RUN \
    apt-get update \
    && apt-get install -y \
        python3 \
        curl \
    # pip
    && curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py \
    && python3 get-pip.py \
    && apt-get install -y \
        graphviz \
        doxygen \
        patch \
    && pip install \
        sphinx==1.8.1 \
        breathe==4.10.0 \
        sphinx_rtd_theme \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /usr/share/man/* \
    && rm -rf /usr/share/info/* \
    && rm -rf /var/cache/man/* \
    && rm -rf /var/cache/apt/archives/* \
    # Clean up tmp directory
    && rm -rf /tmp/*
