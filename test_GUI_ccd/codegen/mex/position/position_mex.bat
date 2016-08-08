@echo off
set MATLAB=C:\PROGRA~1\MATLAB\MATLAB~1\R2015a
set MATLAB_ARCH=win64
set MATLAB_BIN="C:\Program Files\MATLAB\MATLAB Production Server\R2015a\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=position_mex
set MEX_NAME=position_mex
set MEX_EXT=.mexw64
call "C:\PROGRA~1\MATLAB\MATLAB~1\R2015a\sys\lcc64\lcc64\mex\lcc64opts.bat"
echo # Make settings for position > position_mex.mki
echo COMPILER=%COMPILER%>> position_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> position_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> position_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> position_mex.mki
echo LINKER=%LINKER%>> position_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> position_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> position_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> position_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> position_mex.mki
echo BORLAND=%BORLAND%>> position_mex.mki
echo OMPFLAGS= >> position_mex.mki
echo OMPLINKFLAGS= >> position_mex.mki
echo EMC_COMPILER=lcc64>> position_mex.mki
echo EMC_CONFIG=optim>> position_mex.mki
"C:\Program Files\MATLAB\MATLAB Production Server\R2015a\bin\win64\gmake" -B -f position_mex.mk
