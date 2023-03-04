-file_tag+={GCC9,"^/usr/bin/x86_64-linux-gnu-gcc-9$"}

-doc="See Section 4.1 (page 443) of gcc.pdf."
-config=STD.diagidnt,behavior={c99, GCC9, "specified"}

-doc="See Section 4.4 (page 444) of gcc.pdf and Section 3.1.2 (page 11) of x86_64-abi-0.99.pdf."
-config=STD.bytebits,behavior={c99, GCC9, "8"}

-doc="See Section 4.4 (page 444) of gcc.pdf and the documentation of -fexec-charset=charset and -finput-charset=charset (page 206) in the same manual."
-config=STD.charsmem,behavior={c99, GCC9, "ascii"}

-doc="See Section 4.4 (page 444) of gcc.pdf and the documentation of -fexec-charset=charset (page 206) in the same manual."
-config=STD.execvals,behavior={c99, GCC9, "specified"}

-doc="See Section 4.4 (page 444) of gcc.pdf and the documentation of -fexec-charset=charset and -finput-charset=charset (page 206) of the same manual."
-config=STD.charsmap,behavior={c99, GCC9, "specified"}

-doc="See Section 4.4 (page 444) of gcc.pdf and the documentation of -fexec-charset=charset and -finput-charset=charset (page 206) in the same manual."
-config=STD.charsmem,behavior={c99, GCC9, "ascii"}

-doc="See Section 4.5 (page 445) of gcc.pdf."
-config=STD.signdint,behavior={c99, GCC9, "specified"}

-doc="See Section 4.15 (page 450) of gcc.pdf and Section 3.1.2 (page 11 and following) of x86_64-abi-0.99.pdf."
-config=STD.objbytes,behavior={c99, GCC9, "specified"}

-doc_begin="See Section 2 (page 7 and following) of cpp.pdf."
-config=STD.inclangl,behavior={c99, GCC9, "specified"}
-config=STD.inclfile,behavior={c99, GCC9, "specified"}
-config=STD.inclhead,behavior={c99, GCC9, "specified"}
-doc_end

-doc="See Section 3 (page 13 and following) of cpp.pdf."
-config=STD.stdmacro,behavior={c99, GCC9, "specified"}

-doc="See Section 25.7 (page 784 and following of libc.pdf."
-config=STD.exitstat,behavior={c99, GCC9, "specified"}
