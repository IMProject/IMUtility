#!/bin/bash

set -eu
set -o pipefail

HERE=$( (
    cd "$(dirname "$0")"
    echo "${PWD}"
))

usage() {
    echo "Usage: $0 ANALYSIS_KIND" >&2
    exit 2
}

[ $# -eq 1 ] || usage

analysis_ecl=${HERE}/analysis_$1.ecl
report_ecl=${HERE}/report_$1.ecl

# shellcheck source=./eclair_settings.sh
. "${HERE}/eclair_settings.sh"

rm -rf "${ECLAIR_OUTPUT_DIR}" "${ECLAIR_DATA_DIR}"
mkdir -p "${ECLAIR_OUTPUT_DIR}" "${ECLAIR_DATA_DIR}"

../clean.sh | tee "${ECLAIR_CLEAN_LOG}"
"${ECLAIR_PATH}eclair_env" "-eval_file='${analysis_ecl}'" -- ../build.sh | tee "${ECLAIR_BUILD_LOG}"

"${ECLAIR_PATH}eclair_report" "-eval_file='${report_ecl}'" > "${ECLAIR_REPORT_LOG}"
