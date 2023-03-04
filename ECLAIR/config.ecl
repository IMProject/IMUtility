-enable=MC3R1

-eval_file=gcc-x86_64-9.5.0.ecl

-doc="Sources in the test suite are not under MISRA compliance."
-file_tag+={external,"^Tests/.*$"}

-comment_selector={cppcheck_suppress_comment, "^// cppcheck-suppress.*$"}

-doc="cppcheck deviation comments should not be considered."
-config=MC3R1.D4.4,+ignored_comments="cppcheck_suppress_comment"

-doc="For documentation reasons, URLs in comments are allowed to contain //."
-config=MC3R1.R3.1,comments={url_in_comment,"!^.*(/\*|[^:]//).*$" }
