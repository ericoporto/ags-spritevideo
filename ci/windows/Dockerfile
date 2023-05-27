# base will already have Chocolatey installed
FROM ericoporto/min-ags-dev-env:1.0.0

# if no temp folder exists by default, create it
RUN IF exist %TEMP%\nul ( echo %TEMP% ) ELSE ( mkdir %TEMP% )

# Windows 10.0.10240 SDK (but only install the .NET 4.6 SDK)
RUN pushd %TEMP% && \
  curl -fLO https://download.microsoft.com/download/E/1/F/E1F1E61E-F3C6-4420-A916-FB7C47FBC89E/standalonesdk/sdksetup.exe && \
  start /wait sdksetup /ceip off /features OptionID.NetFxSoftwareDevelopmentKit /quiet /norestart && \
  popd && \
  mkdir empty && \
  robocopy empty %TEMP% /MIR > nul & \
  rd /s /q empty

ARG NUGET_VERSION=5.7.0
RUN cinst nuget.commandline --version %NUGET_VERSION% -y && \
  mkdir empty && \
  robocopy empty %TEMP% /MIR > nul & \
  rd /s /q empty

RUN pushd %TEMP% && \
  mkdir Lib\Xiph && \
  pushd Lib\Xiph && \
  nuget install ericoporto.xiph-for-ags -Version 2022.12.23 && \
  popd && \
  popd && \
  mkdir Lib\Xiph && \
  mkdir Lib\Xiph\include && \
  mkdir Lib\Xiph\include\ogg && \
  pushd Lib\Xiph\include\ogg && \
  robocopy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\include\ogg . /s /e > nul & \
  popd && \
  mkdir Lib\Xiph\include\vorbis && \
  pushd Lib\Xiph\include\vorbis && \
  robocopy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\include\vorbis . /s /e > nul & \
  popd && \
  mkdir Lib\Xiph\include\theora && \
  pushd Lib\Xiph\include\theora && \
  robocopy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\include\theora . /s /e > nul & \
  popd && \
  mkdir Lib\Xiph\x86 && \
  pushd Lib\Xiph\x86 && \
  copy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\lib\x86\libogg_static.lib libogg_static.lib && \
  copy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\lib\x86\libtheora_static.lib libtheora_static.lib && \
  copy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\lib\x86\libvorbis_static.lib libvorbis_static.lib && \
  copy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\lib\x86\libvorbisfile_static.lib libvorbisfile_static.lib && \
  popd && \
  mkdir Lib\Xiph\x64 && \
  pushd Lib\Xiph\x64 && \
  copy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\lib\x64\libogg_static.lib libogg_static.lib && \
  copy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\lib\x64\libtheora_static.lib libtheora_static.lib && \
  copy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\lib\x64\libvorbis_static.lib libvorbis_static.lib && \
  copy %TEMP%\Lib\Xiph\ericoporto.xiph-for-ags.2022.12.23\native\lib\x64\libvorbisfile_static.lib libvorbisfile_static.lib && \
  popd && \
  rd /s /q %TEMP%\Lib
    
# Build and install zlib
ARG ZLIB_VERSION=1.2.13
RUN mkdir Lib\zlib && \
  curl -fLSs "https://github.com/madler/zlib/releases/download/v%ZLIB_VERSION%/zlib-%ZLIB_VERSION%.tar.gz" | tar -f - -xvzC Lib\zlib --strip-components 1 && \
  pushd Lib\zlib\contrib\vstudio\vc14 && \
  "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86 && \
  msbuild zlibvc.sln /p:PlatformToolset=v140 /p:Configuration=Release /p:Platform=Win32 /maxcpucount /nologo && \
  popd && \
  mkdir Lib\zlib\lib && \
  mkdir Lib\zlib\lib\x86 && \
  copy Lib\zlib\contrib\vstudio\vc14\x86\ZlibStatRelease\zlibstat.lib Lib\zlib\lib\x86

COPY zlib.props Lib\zlib.props

# Build and install libpng
ARG LIBPNG_VERSION=1.6.39
RUN mkdir Lib\libpng && \
  curl -fLSs "https://github.com/glennrp/libpng/archive/refs/tags/v%LIBPNG_VERSION%.tar.gz" | tar -f - -xvzC Lib\libpng --strip-components 1 && \
  copy Lib\zlib.props Lib\libpng\projects\vstudio\zlib.props && \
  pushd Lib\libpng\projects\vstudio && \
  "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86 && \
  msbuild vstudio.sln /p:PlatformToolset=v140 /p:Configuration=Release /p:Platform=Win32 /maxcpucount /nologo && \
  popd && \
  rm Lib\zlib.props && \
  mkdir Lib\libpng\lib && \
  mkdir Lib\libpng\lib\x86 && \
  copy Lib\libpng\projects\vstudio\Release\libpng16.lib Lib\libpng\lib\x86


