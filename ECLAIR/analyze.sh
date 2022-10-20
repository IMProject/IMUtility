#!/bin/bash

set -eu
set -o pipefail

HERE=$( (
    cd "$(dirname "$0")"
    echo "${PWD}"
))

# shellcheck source=./eclair_settings.sh
. "${HERE}/eclair_settings.sh"

rm -rf "${ECLAIR_OUTPUT_DIR}" "${ECLAIR_DATA_DIR}"
mkdir -p "${ECLAIR_OUTPUT_DIR}" "${ECLAIR_DATA_DIR}"

../clean.sh | tee "${ECLAIR_CLEAN_LOG}"
"${ECLAIR_PATH}eclair_env" "-eval_file='${HERE}/analysis.ecl'" -- ../build.sh | tee "${ECLAIR_BUILD_LOG}"

"${ECLAIR_PATH}eclair_report" "-eval_file='${HERE}/report.ecl'" > "${ECLAIR_REPORT_LOG}"
