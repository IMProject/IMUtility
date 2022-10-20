#!/bin/sh

set -eu

case "${ECLAIR_PATH=/opt/bugseng/eclair/bin/}" in
*/ | "") ;;
*)
    ECLAIR_PATH=${ECLAIR_PATH}/
    ;;
esac

export ECLAIR_PATH

TOP=${HERE%/*}
export ECLAIR_PROJECT_NAME="${TOP##*/}"
export ECLAIR_PROJECT_ROOT="${TOP}"

export ECLAIR_OUTPUT_DIR="${TOP}/ECLAIR_out"
export ECLAIR_DATA_DIR="${HERE}/.data"
export ECLAIR_WORKSPACE="${ECLAIR_DATA_DIR}/eclair_workspace"

# Set the variable for the ECLAIR project database file.
export ECLAIR_PROJECT_ECD="${ECLAIR_OUTPUT_DIR}/PROJECT.ecd"

# Set the variable for the clean log file.
ECLAIR_CLEAN_LOG=${ECLAIR_OUTPUT_DIR}/CLEAN.log

# Set the variable for the build log file.
ECLAIR_BUILD_LOG=${ECLAIR_OUTPUT_DIR}/BUILD.log

# NEEDED: set the variable for the ECLAIR analysis log absolute file path.
ECLAIR_ANALYSIS_LOG=${ECLAIR_OUTPUT_DIR}/ANALYSIS.log

# Set the variable for the ECLAIR report log file.
ECLAIR_REPORT_LOG=${ECLAIR_OUTPUT_DIR}/REPORT.log

export ECLAIR_REPORTS_SARIF="${ECLAIR_OUTPUT_DIR}/reports.sarif"

export ECLAIR_DIAGNOSTICS_OUTPUT="${ECLAIR_ANALYSIS_LOG}"

export CC_ALIASES="gcc"
#export AS_ALIASES="as"
#export AR_ALIASES="ar"
#export LD_ALIASES="ld"
