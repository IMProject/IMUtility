-enable=MC3R1.D4.4
-enable=MC3.R1.1
-enable=MC3R1.R10.1
-enable=MC3R1.R10.4

#-eval_file=gcc-x86_64-7.5.0.ecl

#-config=MC3R1.D4.9,macros+={hide, ^REFLECT_DATA$}
#-config=MC3R1.D4.9,macros+={hide, ^REFLECT_REMAINDER$}

#-file_tag+={api:public,"^src/crc\\.h$"}
#-public_files+=api:public
#-config=MC3R1.R8.7,+declarations={hide,"^reflect\\(.*$"}

#-config=MC3R1.R15.5,reports+={hide,"all_area(context(^main\\(.*$))"}

#-config=MC3R1.R21.6,reports+={hide,"all_area(all_loc(^src/main\\.c$))"}

-default_call_properties+="pointee_read(1..=never)"
-default_call_properties+="pointee_write(1..=always)"
-default_call_properties+="taken()"
