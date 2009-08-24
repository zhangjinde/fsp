#
# Scons compiler tester
#
# Version 1.10
# 24-Aug-2009
#

def checkForCCOption(conf,option):
   """Checks if CC compiler supports given command line option.

   Adds option to CCFLAGS option is supported by compiler.

   """
   conf.Message("Checking whether %s supports %s... " % (conf.env['CC'],option))
   lastCFLAGS=conf.env['CCFLAGS']
   conf.env.Append(CCFLAGS = option)
   rc = conf.TryCompile("""
void dummy(void);
void dummy(void) {}
""",'.c')
   if not rc:
       conf.env.Replace(CCFLAGS = lastCFLAGS)
   conf.Result(rc)
   return rc
