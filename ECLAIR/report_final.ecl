# eclair_report

-eval_file=report_common.ecl

# Full output in pure text format.
full_txt(join_paths(output_dir,"txt"))
# Output metrics for use with spreadsheet applications (if enabled).
metrics_tab(join_paths(output_dir,"metrics"))
# Output reports for use with spreadsheet applications
reports_tab(join_paths(output_dir,"reports"))

# Show only first area in reports
first_area()
# Full output in ODT format.
full_odt(join_paths(output_dir,"odt"))
# Full output in ODT format.
full_doc(join_paths(output_dir,"doc"))
