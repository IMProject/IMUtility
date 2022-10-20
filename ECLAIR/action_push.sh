#!/bin/sh

set -eu

usage() {
    echo "Usage: $0 WTOKEN ANALYSIS_OUTPUT_DIR COMMIT_ID" >&2
    exit 2
}

[ $# -eq 3 ] || usage

wtoken=$1
analysisOutputDir=$2
commitId=$3

# Load settings and helpers
. "$(dirname "$0")/action.helpers"
. "$(dirname "$0")/action.settings"

curl -sS "${eclairReportUrlPrefix}/ext/update_push" \
    -F "wtoken=${wtoken}" \
    -F "artifactsDir=${artifactsDir}" \
    -F "subDir=${subDir}" \
    -F "jobId=${jobId}" \
    -F "jobHeadline=${jobHeadline}" \
    -F "commitId=${commitId}" \
    -F "badgeLabel=${badgeLabel}" \
    -F "db=@${analysisOutputDir}/PROJECT.ecd" \
    >"${updateLog}"
ex=0
grep -Fq "unfixedReports: " "${updateLog}" || ex=$?
maybe_log_file_exit PUBLISH_RESULT "Publishing results" "${updateLog}" "${ex}"

summary

case ${ci} in
github)
    ex=0
    gh api \
        --method POST \
        "/repos/${repository}/commits/${commitId}/comments" \
        -F "body=@${summaryTxt}" \
        --silent >"${commentLog}" 2>&1 || ex=$?
    maybe_log_file_exit ADD_COMMENT "Adding comment" "${commentLog}" "${ex}"
    ;;
gitlab)
    curl -sS --request POST \
        "${gitlabApiUrl}/projects/${CI_PROJECT_ID}/repository/commits/${CI_COMMIT_SHA}/comments" \
        -H "PRIVATE-TOKEN: ${gitlabBotToken}" \
        -F "note=<${summaryTxt}" >"${commentLog}"
    ex=0
    grep -Fq "Unfixed reports: " "${commentLog}" || ex=$?
    maybe_log_file_exit ADD_COMMENT "Adding comment" "${commentLog}" "${ex}"
    ;;
*) ;;
esac
