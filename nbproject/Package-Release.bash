#!/bin/bash -x

#
# Generated - do not edit!
#

# Macros
TOP=`pwd`
PLATFORM=MinGW-Windows
TMPDIR=build/Release/${PLATFORM}/tmp-packaging
TMPDIRNAME=tmp-packaging
OUTPUT_PATH=dist/Release/${PLATFORM}/foom
OUTPUT_BASENAME=foom
PACKAGE_TOP_DIR=foom/

# Functions
function checkReturnCode
{
    rc=$?
    if [ $rc != 0 ]
    then
        exit $rc
    fi
}
function makeDirectory
# $1 directory path
# $2 permission (optional)
{
    mkdir -p "$1"
    checkReturnCode
    if [ "$2" != "" ]
    then
      chmod $2 "$1"
      checkReturnCode
    fi
}
function copyFileToTmpDir
# $1 from-file path
# $2 to-file path
# $3 permission
{
    cp "$1" "$2"
    checkReturnCode
    if [ "$3" != "" ]
    then
        chmod $3 "$2"
        checkReturnCode
    fi
}

# Setup
cd "${TOP}"
mkdir -p dist/Release/${PLATFORM}/package
rm -rf ${TMPDIR}
mkdir -p ${TMPDIR}

# Copy files and create directories and links
cd "${TOP}"
makeDirectory ${TMPDIR}/foom/bin
copyFileToTmpDir "${OUTPUT_PATH}.exe" "${TMPDIR}/${PACKAGE_TOP_DIR}bin/${OUTPUT_BASENAME}.exe" 0755


# Generate tar file
cd "${TOP}"
rm -f dist/Release/${PLATFORM}/package/foom.tar
cd ${TMPDIR}
tar -vcf ../../../../dist/Release/${PLATFORM}/package/foom.tar *
checkReturnCode

# Cleanup
cd "${TOP}"
rm -rf ${TMPDIR}