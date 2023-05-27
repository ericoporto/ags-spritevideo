ARG FROM_DEBIAN=debian:latest
ARG FROM_PLATFORM=$BUILDPLATFORM
FROM --platform=$FROM_PLATFORM $FROM_DEBIAN

# Take default debconf options
ENV DEBIAN_FRONTEND noninteractive

RUN echo "deb [trusted=yes] http://archive.debian.org/debian jessie main non-free contrib" > /etc/apt/sources.list && \
    echo 'deb-src [trusted=yes] http://archive.debian.org/debian/ jessie main non-free contrib'  >> /etc/apt/sources.list && \
    echo 'deb [trusted=yes] http://archive.debian.org/debian-security/ jessie/updates main non-free contrib'  >> /etc/apt/sources.list

# Configure apt defaults
ARG APT_CONF_LOCAL=99local
RUN mkdir -p /etc/apt/apt.conf.d && \
  printf 'APT::Get::Assume-Yes "true";\n\
APT::Get::Install-Recommends "false";\n\
APT::Get::Install-Suggests "false";\n' > /etc/apt/apt.conf.d/$APT_CONF_LOCAL

# Upgrade existing packages
RUN apt-get update && apt-get upgrade

# Get curl and ssl for cmake fetches
RUN apt-get install curl libcurl4-openssl-dev libssl-dev

# Get build dependencies
RUN apt-get install \
  build-essential \
  debhelper \
  autoconf \
  dh-autoreconf \
  git \
  libogg-dev \
  libtheora-dev \
  libvorbis-dev \
  zlib1g-dev \
  pkg-config

# Get SDL2 build dependencies
RUN apt-get install \
  libasound2-dev \
  libdbus-1-dev \
  libegl1-mesa-dev \
  libgl1-mesa-dev \
  libgles2-mesa-dev \
  libglu1-mesa-dev \
  libibus-1.0-dev \
  libpulse-dev \
  libsndio-dev \
  libudev-dev \
  libwayland-dev \
  libx11-dev \
  libxcursor-dev \
  libxext-dev \
  libxi-dev \
  libxinerama-dev \
  libxkbcommon-dev \
  libxrandr-dev \
  libxss-dev \
  libxt-dev \
  libxv-dev \
  libxxf86vm-dev \
  libwayland-dev \
  libxkbcommon-dev 
  
# Build and install zlib
ARG ZLIB_VERSION=1.2.13
RUN curl -fLsS "https://github.com/madler/zlib/releases/download/v${ZLIB_VERSION}/zlib-${ZLIB_VERSION}.tar.gz" --output /tmp/zlib-${ZLIB_VERSION}.tar.gz && \
  tar --file=/tmp/zlib-${ZLIB_VERSION}.tar.gz -xzC /tmp && \
  cd /tmp/zlib-${ZLIB_VERSION} && \
  ./configure --prefix=/opt && \
  make && \
  make install && \
  rm -r /tmp/zlib-${ZLIB_VERSION} && \
  rm /tmp/zlib-${ZLIB_VERSION}.tar.gz

# Build and install libpng
ARG LIBPNG_VERSION=1.6.39
RUN curl -fLsS "https://github.com/glennrp/libpng/archive/refs/tags/v${LIBPNG_VERSION}.tar.gz" --output /tmp/libpng-${LIBPNG_VERSION}.tar.gz && \
  tar --file=/tmp/libpng-${LIBPNG_VERSION}.tar.gz -xzC /tmp && \
  cd /tmp/libpng-${LIBPNG_VERSION} && \
  ./configure && \
  make && \
  make install && \
  rm -r /tmp/libpng-${LIBPNG_VERSION} && \
  rm /tmp/libpng-${LIBPNG_VERSION}.tar.gz

# Build newer libogg
ARG LIBOGG_VERSION=1.3.5
RUN curl -fLsS "https://github.com/xiph/ogg/releases/download/v${LIBOGG_VERSION}/libogg-${LIBOGG_VERSION}.tar.xz" --output /tmp/libogg-${LIBOGG_VERSION}.tar.xz && \
  tar --file=/tmp/libogg-${LIBOGG_VERSION}.tar.xz -xJC /tmp && \
  cd /tmp/libogg-${LIBOGG_VERSION} && \
  ./configure --prefix=/opt && \
  make && \
  make install && \
  rm -r /tmp/libogg-${LIBOGG_VERSION} && \
  rm /tmp/libogg-${LIBOGG_VERSION}.tar.xz

# Build newer libvorbis
ARG LIBVORBIS_VERSION=1.3.7
RUN curl -fLsS "https://github.com/xiph/vorbis/releases/download/v${LIBVORBIS_VERSION}/libvorbis-${LIBVORBIS_VERSION}.tar.gz" --output /tmp/libvorbis-${LIBVORBIS_VERSION}.tar.gz && \
  tar --file=/tmp/libvorbis-${LIBVORBIS_VERSION}.tar.gz -xzC /tmp && \
  cd /tmp/libvorbis-${LIBVORBIS_VERSION} && \
  ./configure --disable-examples --disable-oggtest --prefix=/opt && \
  make && \
  make install && \
  rm -r /tmp/libvorbis-${LIBVORBIS_VERSION} && \
  rm /tmp/libvorbis-${LIBVORBIS_VERSION}.tar.gz 
  
# Build newer libtheora - note that encoding support is disabled AND it's directory uses GH repo name instead
ARG LIBTHEORA_VERSION=1.1.1
RUN curl -fLsS "https://github.com/xiph/theora/archive/refs/tags/v${LIBTHEORA_VERSION}.tar.gz" --output /tmp/libtheora-${LIBTHEORA_VERSION}.tar.gz && \
  tar --file=/tmp/libtheora-${LIBTHEORA_VERSION}.tar.gz -xzC /tmp && \
  cd /tmp/theora-${LIBTHEORA_VERSION} && \
  ./autogen.sh --disable-encode --disable-examples --disable-oggtest --prefix=/opt && \
  make && \
  make install && \
  rm -r /tmp/theora-${LIBTHEORA_VERSION} && \
  rm /tmp/libtheora-${LIBTHEORA_VERSION}.tar.gz 
  

RUN ldconfig -v