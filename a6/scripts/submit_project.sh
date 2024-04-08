#!/bin/bash
# This script submits an acceptable .cc file of your project into Marmoset.

# check that we are in the scripts directory
if [ ! -f helper/colors.sh ] 
then
    echo "please cd to the scripts directory"
    echo "this script is intended to be run from the scripts directory"
    exit 1
fi
# in the scripts directory: proceed


source helper/colors.sh

if [ "$#" -lt 1 ]; then
    echo -e "${RED}Run the script as follows:"
    echo -e "\t./submit_project.sh <PROJECT_NUMBER>${NC}"
    exit 1
fi

# are we on the CS student server?
if [ ! -f /u/cs_build/bin/marmoset_submit ] ; then
    echo "ERROR: could not find marmoset_submit" 
    echo "QUERY: what machine is this script running on?"
    echo "INFO:  this script is running on a machine named: " `uname -n`
    exit 1
fi

ASSIGNMENT=a6
QUESTION=$1
PROJ_NAME=${ASSIGNMENT}p${QUESTION}
DIR_NAME=${PROJ_NAME%?}
FNAME=${DIR_NAME}.cc
TYPE=${QUESTION: -1}

if [ ${TYPE} == "c" ]; then
    FNAME=${DIR_NAME}.cc
elif [ ${TYPE} == "t" ]; then
    FNAME=${DIR_NAME}Test.cc
else
    echo -e "Unknown project: ${QUESTION}"
    exit 1
fi

cd ..

# if [ $? -ne 0 ]; then
#     echo -e "Unable to find the project directory: ${DIR_NAME}"
#     exit 1
# fi

echo
echo Submitting to Marmoset!
echo
# t project: submit InputFiles
if [ ${TYPE} == "t" ]; then
    if [ ${QUESTION} == "3t" ]; then
        /u/cs_build/bin/marmoset_submit cs138 ${PROJ_NAME} ${FNAME} InputFiles/*.txt
    else
        /u/cs_build/bin/marmoset_submit cs138 ${PROJ_NAME} ${FNAME} ${DIR_NAME}.h InputFiles/*.txt
    fi
else
    if [ ${QUESTION} == "3c" ]; then
        /u/cs_build/bin/marmoset_submit cs138 ${PROJ_NAME} ${FNAME}
    else
        /u/cs_build/bin/marmoset_submit cs138 ${PROJ_NAME} ${FNAME} ${DIR_NAME}.h
    fi
fi