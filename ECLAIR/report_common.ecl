# eclair_report

quiet()

setq(data_dir,getenv("ECLAIR_DATA_DIR"))
setq(output_dir,getenv("ECLAIR_OUTPUT_DIR"))
setq(ecd_file,getenv("ECLAIR_PROJECT_ECD"))
setq(sarif_file,getenv("ECLAIR_REPORTS_SARIF"))

create_db(ecd_file)
loading()
strings_map("load_ecb",500,"",".+\\.ecb",0,setq(ecb,join_paths(data_dir,$0)),load(ecb))
strings_map("load_ecb",500,"",".*",0)
map_strings("load_ecb", dir_entries(data_dir))
loaded()

#reports
reports_sarif(sarif_file)
