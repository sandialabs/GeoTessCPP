#!/bin/bash

GEOTESS_ROOT=`pwd`

# discover the operating system: either SunOS, Linux or Darwin
OS=`uname -s`

echo
echo "recommended environment variables for $OS:"
echo

if [ "$OS" = "Darwin" ]; then
  echo "export GEOTESS_ROOT=$GEOTESS_ROOT"
  echo "export DYLD_LIBRARY_PATH=\${DYLD_LIBRARY_PATH}:\${GEOTESS_ROOT}/GeoTessCPP/lib"
  echo "export DYLD_LIBRARY_PATH=\${DYLD_LIBRARY_PATH}:\${GEOTESS_ROOT}/GeoTessCShell/lib"
#  echo "export DYLD_LIBRARY_PATH=\${DYLD_LIBRARY_PATH}:\${GEOTESS_ROOT}/GeoTessFShell/lib"
  echo "export PATH=\${GEOTESS_ROOT}/GeoTessCPPExamples/bin:\$PATH"
  echo "export PATH=\${GEOTESS_ROOT}/GeoTessCExamples/bin:\$PATH"
#  echo "export PATH=\${GEOTESS_ROOT}/GeoTessFExamples/bin:\$PATH"
else
  echo "setenv GEOTESS_ROOT $GEOTESS_ROOT"
  echo "setenv LD_LIBRARY_PATH \"\$LD_LIBRARY_PATH\":\$GEOTESS_ROOT/GeoTessCPP/lib"
  echo "setenv LD_LIBRARY_PATH \"\$LD_LIBRARY_PATH\":\$GEOTESS_ROOT/GeoTessCShell/lib"
#  echo "setenv LD_LIBRARY_PATH \"\$LD_LIBRARY_PATH\":\$GEOTESS_ROOT/GeoTessFShell/lib"
  echo "set path = ( \${GEOTESS_ROOT}/GeoTessCPPExamples/bin \$path )"
  echo "set path = ( \${GEOTESS_ROOT}/GeoTessCExamples/bin \$path )"
#  echo "set path = ( \${GEOTESS_ROOT}/GeoTessFExamples/bin \$path )"
fi
echo
