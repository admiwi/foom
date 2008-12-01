import subprocess
foom_src = [ "build/"+f.name for f in  Glob("src/foom*.c")]
VariantDir('build','src', duplicate=0)
foom_bin = Program("foom", foom_src, CFLAGS=["-ggdb","-Wall","-O2"], CPPPATH=['include'])
test = Alias('test', [foom_bin], foom_bin[0].abspath +" test/hello.fm")
AlwaysBuild(test)
