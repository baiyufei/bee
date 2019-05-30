From centos:7
LABEL MAINTAINER=baiyufei@outlook.com

run yum install -y autoconf automake bzip2 bzip2-devel cmake freetype-devel gcc gcc-c++ git libtool make mercurial pkgconfig zlib-devel curl

RUN mkdir /root/ffmpeg_sources && mkdir /root/ffmpeg_build

WORKDIR /root/ffmpeg_sources
RUN \ 
curl -O -L https://www.nasm.us/pub/nasm/releasebuilds/2.14.02/nasm-2.14.02.tar.bz2 && \
tar xjvf nasm-2.14.02.tar.bz2 &&\
cd nasm-2.14.02 &&\
./autogen.sh && \
./configure --prefix="$HOME/ffmpeg_build" --bindir="$HOME/bin" && \
make && \
make install

WORKDIR /root/ffmpeg_sources
RUN \ 
curl -O -L https://www.tortall.net/projects/yasm/releases/yasm-1.3.0.tar.gz && \
tar xzvf yasm-1.3.0.tar.gz && \
cd yasm-1.3.0 && \
./configure --prefix="$HOME/ffmpeg_build" --bindir="$HOME/bin" && \
make && \
make install

WORKDIR /root/ffmpeg_sources
ENV PATH "$PATH:/root/bin"
RUN \ 
git clone --depth 1 https://code.videolan.org/videolan/x264.git && \
cd x264 && \
PKG_CONFIG_PATH="$HOME/ffmpeg_build/lib/pkgconfig" ./configure --prefix="$HOME/ffmpeg_build" --bindir="$HOME/bin" --enable-static && \
make && \
make install

WORKDIR /root/ffmpeg_sources
RUN \ 
hg clone https://bitbucket.org/multicoreware/x265   && \
cd ~/ffmpeg_sources/x265/build/linux && \
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX="$HOME/ffmpeg_build" -DENABLE_SHARED:bool=off ../../source && \
make && \
make install

WORKDIR /root/ffmpeg_sources
RUN \ 
git clone --depth 1 https://github.com/mstorsjo/fdk-aac && \
cd fdk-aac && \
autoreconf -fiv && \
./configure --prefix="$HOME/ffmpeg_build" --disable-shared && \
make && \
make install

WORKDIR /root/ffmpeg_sources
RUN \ 
curl -O -L https://ffmpeg.org/releases/ffmpeg-snapshot.tar.bz2 && \
tar xjvf ffmpeg-snapshot.tar.bz2 && \
cd ffmpeg && \
PATH="$HOME/bin:$PATH" PKG_CONFIG_PATH="$HOME/ffmpeg_build/lib/pkgconfig" ./configure \
  --prefix="$HOME/ffmpeg_build" \
  --pkg-config-flags="--static" \
  --extra-cflags="-I$HOME/ffmpeg_build/include" \
  --extra-ldflags="-L$HOME/ffmpeg_build/lib" \
  --extra-libs=-lpthread \
  --extra-libs=-lm \
  --enable-gpl \
  --enable-libfdk_aac \
  --enable-libx264 \
  --enable-libx265 \
  --enable-nonfree && \
make -j4 && \
make install
