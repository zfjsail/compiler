#ifndef __DEBUG_H__
#define __DEBUG_H__

extern int enable_debug;
#define Log(format,...)\
	(enable_debug ? \
	 fprintf(stdout,"\33[1;34m%s,%s,%d:" format "\33[0m\n", \
		 __FILE__,__func__,__LINE__,## __VA_ARGS__), \
	 fflush(stdout) \
	 : (void)0)


#endif
