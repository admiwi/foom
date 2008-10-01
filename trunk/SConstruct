foom_src = [ "build/"+f.name for f in  Glob("src/foom*.c")]
VariantDir('build','src', duplicate=0)
foom_bin = Program("foom", foom_src, CFLAGS=["-Wall"], CPPPATH=['include'])
