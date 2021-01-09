#ifndef __CTL_MEM_H__
#define __CTL_MEM_H__

#define CTLMEM_FREE_BUF_AND_NULL_PTR(p) \
   do { \
      if ((p) != NULL) {free((p)); (p) = NULL;}   \
   } while (0)


#define CTLMEM_REPLACE_STRING(p, s) \
   do {\
      if ((p) != NULL) {free((p));} \
      (p) = strdup((s)); \
   } while (0)
   
#endif
